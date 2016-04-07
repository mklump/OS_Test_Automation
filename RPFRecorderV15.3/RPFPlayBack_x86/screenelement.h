#include "RPFPlaybackNameSpace.h"
#include "commctrl.h"

#pragma warning (disable : 4311)
#pragma warning (disable : 4312)
#pragma warning (disable : 4995)
#pragma warning (disable : 4996)

using namespace RPFPlayback;

class ScreenElement;

#pragma region RuntimeId

class RuntimeId
{
private:
    int *_pnIds;
    int _cArraySize;

public: 
    RuntimeId(int *pnIds, int cArraySize)
    {
        _pnIds = pnIds;
        _cArraySize = cArraySize;
    }

    virtual ~RuntimeId()
    {
        if(_cArraySize && _pnIds)
        {
            delete _pnIds;
            _pnIds = NULL;
            _cArraySize = 0;
        }
    }

    int GetIdAtIndex(int i)
    {
        if(i < _cArraySize)
        {
            return _pnIds[i];
        }
        else
        {
            return 0xFFFFFFFF;
        }
    }

};

#pragma endregion RuntimeId

#pragma region ScreenElementCollection declaration

class ScreenElementCollection
{
private:
    static const int ELEMENTS_EXPAND = 10;
    HDPA _internalCollection;

public:

    ScreenElementCollection();
    virtual ~ScreenElementCollection();

    int Count();
    bool Add(ScreenElement* screenElement);
    void DeleteByIndex(int index);
    void Clean();
    ScreenElement* operator[](int i);

};

#pragma endregion ScreenElementCollection declaration

#pragma region ScreenElement

class ScreenElement
{

private:
    BSTR m_Name;
    BSTR m_ClassName;
    BSTR m_RoleText;
    BSTR m_Value;
    BSTR m_State;
    BSTR m_Description;
    HWND m_Hwnd;
    RuntimeId* m_pRuntimeId;

private:
    IScreenElement* m_ScreenElementInternal;

    // This method will return the IAccessible description of the ScreenElement;
    // If the description cannot be obtained, E_FAIL will be returned,
    // and pbstrDescription will set to NULL
    // The caller needs to free the returned string using ::SysFreeString()
    HRESULT get_Description(BSTR *pbstrDescription)
    {
        IAccessible* pAcc = NULL;
        VARIANT childID;
        HRESULT hr = E_FAIL;

        if (NULL != pbstrDescription)
        {
            *pbstrDescription = NULL;
            pAcc = this->get_Accessible();
            if (NULL != pAcc)
            {
                childID = this->get_ChildId();
                hr = pAcc->get_accDescription(childID, pbstrDescription);
                if ( (hr != S_OK) || (NULL == *pbstrDescription) )
                {
                    *pbstrDescription = NULL;
                    hr = E_FAIL;
                }
                
                VariantClear(&childID);
                pAcc->Release();
            }
        }
     
        return hr;
    }

    void Clean()
    {
        if (m_Name != NULL)
        {
            SysFreeString(m_Name);
            m_Name = NULL;
        }

        if (m_ClassName != NULL)
        {
            SysFreeString(m_ClassName);
            m_ClassName = NULL;
        }

        if (m_RoleText != NULL)
        {
            SysFreeString(m_RoleText);
            m_RoleText = NULL;
        }

        if (m_Value != NULL)
        {
            SysFreeString(m_Value);
            m_Value = NULL;
        }

        if (m_State != NULL)
        {
            SysFreeString(m_State);
            m_State = NULL;
        }

        if (m_Description != NULL)
        {
            SysFreeString(m_Description);
            m_Description = NULL;
        }

        if(m_pRuntimeId != NULL)
        {
            delete m_pRuntimeId;
            m_pRuntimeId = NULL;
        }
    }

    ScreenElementCollection* FindAllDescendantsInternal(int nMaxDepth, wchar_t* pszQueryId, va_list arguments)
    {
        HRESULT hr = S_OK;
        SAFEARRAY *saDescendants = NULL;
        int nTotalResourceKeys;
        VARIANT varResKeys;
        wchar_t (*pszAllResourceKeys)[MAX_RES_KEY_LENGTH];

        RPFPlayback::ComposeQueryId(pszQueryId, arguments, &nTotalResourceKeys, &pszAllResourceKeys);

        if (nTotalResourceKeys > 0)
        {
            if (SUCCEEDED(ComposeSafeArray(&varResKeys, &pszAllResourceKeys, nTotalResourceKeys)))
            {
                hr = m_ScreenElementInternal->FindAllDescendants(CComBSTR(pszQueryId), &varResKeys, nTotalResourceKeys, nMaxDepth, &saDescendants);

                // Free BSTRs allocated in ComposeSafeArray and delete safearray
                FreeSafeArray(&varResKeys);
            }
        }
        else
        {
            VariantInit(&varResKeys);
            hr = m_ScreenElementInternal->FindAllDescendants(CComBSTR(pszQueryId), &varResKeys, 0, nMaxDepth, &saDescendants);
        }

        delete [] pszAllResourceKeys;

        if (saDescendants == NULL)
        {
            SetLastError(ERROR_NOT_FOUND);
            return new ScreenElementCollection();
        }

        if (hr != S_OK)
        {
            // Destroy safearray.  This will call Release for each screenElement whose RefCounf was incremented by QueryInterface
            SafeArrayDestroy(saDescendants);
            SetLastError(ERROR_NOT_FOUND);
            return new ScreenElementCollection();
        }

        // Compose array of found descendants
        IScreenElement* pScreenElementInterface;
        ScreenElement* pScreenElement;
        ScreenElementCollection* pFoundElements = new ScreenElementCollection();

        if (pFoundElements == NULL)
        {
            LogInformation(L"[WARNING] Internal failure in wrapper: Not enough memory for the ScreenElementCollection\r\n", FALSE);
            // Destroy safearray.  This will call Release for each screenElement whose RefCounf was incremented by QueryInterface
            SafeArrayDestroy(saDescendants);
            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            return new ScreenElementCollection();
        }

        VARIANT *var;
        if (S_OK != SafeArrayAccessData(saDescendants, (void **)&var))
        {
            LogInformation(L"[WARNING] Internal failure in wrapper: Could not access data in SafeArray\r\n", FALSE);
            // Destroy safearray.  This will call Release for each screenElement whose RefCounf was incremented by QueryInterface
            SafeArrayDestroy(saDescendants);
            SetLastError(ERROR_ACCESS_DENIED);
            return pFoundElements;
        }

        int nTotalFoundDescendants = saDescendants->rgsabound[0].cElements;

        for (int i = 0; i < nTotalFoundDescendants; i++)
        {
            var[i].pdispVal->QueryInterface(__uuidof(IScreenElement), (void**) &pScreenElementInterface);

            // Create ScreenElement
            pScreenElement = new ScreenElement(pScreenElementInterface);

            if (pScreenElement == NULL)
            {
                LogInformation(L"[WARNING] Internal failure in wrapper: Not enough memory for new ScreenElement in collection\r\n", FALSE);
                continue;
            }

            // Add to the collection
            pFoundElements->Add(pScreenElement);
        }

        // Unlock the array
        SafeArrayUnaccessData(saDescendants);

        // Destroy safearray.  This will call Release for each screenElement whose RefCounf was incremented by QueryInterface
        SafeArrayDestroy(saDescendants);

        SetLastError(ERROR_SUCCESS);
        return pFoundElements;
    }

public:

    #pragma region Constructors, Destructors and Copy

    // Default constructor
    ScreenElement()
    {
        m_ScreenElementInternal = NULL;
    }

    // Constructor
    ScreenElement(IScreenElement* screenElement)
    {
        m_Name = m_ClassName = m_RoleText = m_Value = m_State = m_Description = NULL;
        m_pRuntimeId = NULL;
        m_Hwnd = NULL;
        m_ScreenElementInternal = screenElement;
    }

    // Destructor
    virtual ~ScreenElement()
    {
        m_ScreenElementInternal->Release();
        Clean();
    }

    ScreenElement* Copy()
    {
        if (m_ScreenElementInternal != NULL)
        {
            m_ScreenElementInternal->AddRef();
            return new ScreenElement(m_ScreenElementInternal);
        }
        else
        {
            return NULL;
        }
    }

    IScreenElement* ScreenElement::get_IScreenElement() { return m_ScreenElementInternal;} 

#pragma endregion Constructors, Destructors and Copy

    #pragma region Search

public:

    static ScreenElement* FromWinEvent()
    {
        IScreenElement* pScreenElement;

        if (S_OK != RPFPlayback::ScreenElementFromWinEvent(&pScreenElement))
        {
            return NULL;
        }
        else
        {
            return new ScreenElement(pScreenElement);
        }
    }

    static ScreenElement* FromPoint(int x, int y)
    {
        IScreenElement* pScreenElement;

        if (S_OK != RPFPlayback::ScreenElementFromPoint(x, y, &pScreenElement))
        {
            return NULL;
        }
        else
        {
            return new ScreenElement(pScreenElement);
        }
    }

    static ScreenElement* FromWindow(HWND hWnd)
    {
        IScreenElement* pScreenElement;

        if (S_OK != RPFPlayback::ScreenElementFromWindow(hWnd, &pScreenElement))
        {
            return NULL;
        }
        else
        {
            return new ScreenElement(pScreenElement);
        }
    }

    static ScreenElement* FromAccessibleObject(IAccessible *pAcc, VARIANT ChildId)
    {
        IScreenElement* pScreenElement;

        if (S_OK != RPFPlayback::ScreenElementFromAccessibleObject(pAcc, ChildId, &pScreenElement))
        {
            return NULL;
        }
        else
        {
            return new ScreenElement(pScreenElement);
        }
    }

    static ScreenElement* FromHTMLElement(IHTMLElement* pIHTMLElement)
    {
        IScreenElement* pScreenElement;

        if (S_OK != RPFPlayback::ScreenElementFromHTMLElement(pIHTMLElement, &pScreenElement))
        {
            return NULL;
        }
        else
        {
            return new ScreenElement(pScreenElement);
        }
    }

    static ScreenElement* FromPartialQueryId(wchar_t* pszQueryId, ... )
    {
        IScreenElement* pScreenElement;

        // Initialize variable arguments.
        va_list arguments;
        va_start( arguments, pszQueryId);     

        if (S_OK != RPFPlayback::FromPartialQueryId(NULL, &pScreenElement, pszQueryId, arguments))
        {
            return NULL;
        }
        else
        {
            return new ScreenElement(pScreenElement);
        }
    }

    ScreenElement* FindByPartialQueryId(wchar_t* pszQueryId, ...)
    {
        HRESULT hr = S_OK;
        int nTotalResourceKeys;
        VARIANT varResKeys;
        wchar_t (*pszAllResourceKeys)[MAX_RES_KEY_LENGTH];
        IScreenElement* pScreenElement = NULL;

        // Initialize variable arguments.
        va_list arguments;
        va_start( arguments, pszQueryId);  

        RPFPlayback::ComposeQueryId(pszQueryId, arguments, &nTotalResourceKeys, &pszAllResourceKeys);

        if (nTotalResourceKeys > 0)
        {
            if (SUCCEEDED(ComposeSafeArray(&varResKeys, &pszAllResourceKeys, nTotalResourceKeys)))
            {
                hr = m_ScreenElementInternal->FindScreenElementEx(CComBSTR(pszQueryId), &varResKeys, nTotalResourceKeys, &pScreenElement);

                // Free BSTRs allocated in ComposeSafeArray and delete safearray
                FreeSafeArray(&varResKeys);
            }
        }
        else
        {
            VariantInit(&varResKeys);
            hr = m_ScreenElementInternal->FindScreenElementEx(CComBSTR(pszQueryId), &varResKeys, 0, &pScreenElement);
        }

        delete [] pszAllResourceKeys;

        if (hr != S_OK || pScreenElement == NULL)
        {
            return NULL;
        }
        else
        {
            return new ScreenElement(pScreenElement);
        }
    }

    ScreenElementCollection* FindAllDescendants(wchar_t* pszQueryId, ... )
    {
        // Initialize variable arguments.
        va_list arguments;
        va_start(arguments, pszQueryId);  

        return FindAllDescendantsInternal(ALL_DESCENDANTS, pszQueryId, arguments);
    }

    ScreenElementCollection* FindAllDescendants(int nMaxDepth, wchar_t* pszQueryId, ... )
    {
        // Initialize variable arguments.
        va_list arguments;
        va_start(arguments, pszQueryId);  

        return FindAllDescendantsInternal(nMaxDepth, pszQueryId, arguments);
    }

    #pragma endregion Search

    #pragma region Primitives

    HRESULT LeftButtonClick(INT x, INT y)
    {
        return m_ScreenElementInternal->LeftButtonClick(x, y);
    }

    HRESULT LeftButtonClick(INT x, INT y, BOOL fEnsureVisible, wchar_t* bstrKeyModifiers)
    {
        return m_ScreenElementInternal->LeftButtonClick(x, y, fEnsureVisible, CComBSTR(bstrKeyModifiers));
    }

    HRESULT DoubleClick(INT x, INT y)
    {
        return m_ScreenElementInternal->DoubleClick(x, y);
    }

    HRESULT DoubleClick(INT x, INT y, BOOL fEnsureVisible, wchar_t* bstrKeyModifiers)
    {
        return m_ScreenElementInternal->DoubleClick(x, y, fEnsureVisible, bstrKeyModifiers);
    }

    HRESULT RightButtonClick(INT x, INT y)
    {
        return m_ScreenElementInternal->RightButtonClick(x, y);
    }

    HRESULT RightButtonClick(int x, int y, BOOL fEnsureVisible, wchar_t* bstrKeyModifiers)
    {
        return m_ScreenElementInternal->RightButtonClick(x, y, fEnsureVisible, CComBSTR(bstrKeyModifiers));
    }

    HRESULT Expand()
    {
        return m_ScreenElementInternal->Expand(ECF_USE_TVM_EXPAND | ECF_USE_DOUBLECLICK | ECF_USE_NUMPAD | ECF_USE_ENTER);
    }

    HRESULT Expand(int nExpandCollapseFlag)
    {
        return m_ScreenElementInternal->Expand(nExpandCollapseFlag);
    }

    HRESULT Check(BOOL fSetIndeterminate, BOOL fVerifyFinalState = TRUE)
    {
        return m_ScreenElementInternal->Check(fSetIndeterminate, fVerifyFinalState);
    }

    HRESULT Check()
    {
        return m_ScreenElementInternal->Check(FALSE, TRUE);
    }

    HRESULT Collapse()
    {
        return m_ScreenElementInternal->Collapse(ECF_USE_TVM_EXPAND | ECF_USE_DOUBLECLICK | ECF_USE_NUMPAD | ECF_USE_ENTER);
    }

    HRESULT Collapse(int nExpandCollapseFlag)
    {
        return m_ScreenElementInternal->Collapse(nExpandCollapseFlag);
    }

    HRESULT EnsureVisible(int nEnsureVisibleFlag = EVF_BY_SCROLLING, int x = -1, int y = -1, IScrollerCallback* pScrollerCallback = NULL, int nScrollFlag = SF_SCROLL_BAR | SF_WHEEL, int nMaximumContainers = 2)
    {
        return m_ScreenElementInternal->EnsureVisible(nEnsureVisibleFlag, x, y, pScrollerCallback, nScrollFlag, nMaximumContainers);
    }

    HRESULT Select()
    {
        return m_ScreenElementInternal->Select();
    }

    HRESULT Select(int nSelectionFlag)
    {
        return m_ScreenElementInternal->Select(nSelectionFlag);
    }

    HRESULT SendKeys(wchar_t* keys, INT nKeyboardAction = HIT)
    {
        return m_ScreenElementInternal->SendKeys(CComBSTR(keys), nKeyboardAction);
    }

    HRESULT SetValueAsComboBox(wchar_t* newValue, INT nSetValueAsComboBoxFlag = CF_USE_SET_AS_EDIT | CF_USE_SELECT)
    {
        return m_ScreenElementInternal->SetValueAsComboBox(CComBSTR(newValue), nSetValueAsComboBoxFlag);
    }

    HRESULT SetValueAsEditBox(wchar_t* newValue, INT nSetValueAsEditBoxFlag = EF_DELETE_CONTENT | EF_USE_SENDKEYS)
    {
        return m_ScreenElementInternal->SetValueAsEditBox(CComBSTR(newValue), nSetValueAsEditBoxFlag);
    }

    HRESULT SetValueAsSlider(wchar_t* newValue, int nOrientation = DF_AUTO) // defaultvalue DF_AUTO - Playback should define the orientation itself
    {
        return m_ScreenElementInternal->SetValueAsSlider(CComBSTR(newValue), nOrientation);
    }

    HRESULT StartDragging(INT x, INT y, int nDraggingButton = LEFT_BUTTON)
    {
        return m_ScreenElementInternal->StartDragging(x, y, nDraggingButton, NULL, true);
    }

    HRESULT StartDragging(INT x, INT y, int nDraggingButton, wchar_t* pszKeyModifiers, BOOL fEnsureVisible = TRUE)
    {
        return m_ScreenElementInternal->StartDragging(x, y, nDraggingButton, CComBSTR(pszKeyModifiers), fEnsureVisible);
    }

    HRESULT StopDragging (INT x, INT y, int nSpeedPixelPerSecond = 50)
    {
        return m_ScreenElementInternal->StopDragging(x, y, nSpeedPixelPerSecond);
    }

    HRESULT MoveMouse(INT x, INT y, BOOL fEnsureVisible = TRUE, INT nSpeedPixelPerSecond = 50)
    {
        return m_ScreenElementInternal->MoveMouse(x, y, fEnsureVisible, nSpeedPixelPerSecond);
    }

    HRESULT MouseWheel(INT nDelta)
    {
        return m_ScreenElementInternal->MouseWheel(nDelta, NULL);
    }

    HRESULT MouseWheel(INT nDelta, wchar_t* pszKeyModifiers)
    {
        return m_ScreenElementInternal->MouseWheel(nDelta, CComBSTR(pszKeyModifiers));
    }

    HRESULT Uncheck(BOOL fVerifyFinalState = TRUE)
    {
        return m_ScreenElementInternal->Uncheck(fVerifyFinalState);
    }

    HRESULT WaitForReady()
    {
        return m_ScreenElementInternal->WaitForReady();
    }

    HRESULT BringUp()
    {
        return m_ScreenElementInternal->BringUp();
    }

    HRESULT VerifyScreenElement(wchar_t* bstrState, wchar_t* bstrValue)
    {
        return m_ScreenElementInternal->VerifyScreenElement(CComBSTR(bstrState), CComBSTR(bstrValue));
    }

    HRESULT WaitForGone(INT nTimeOut, INT nElapse)
    {
        return m_ScreenElementInternal->WaitForGone(nTimeOut, nElapse);
    }

    HRESULT GetClickablePoint(int *x, int *y)
    {
        return m_ScreenElementInternal->GetClickablePoint(x, y);
    }

    HRESULT IsTextTruncated(BOOL* pfIsTruncated, int* nNumSymbolsFit)
    {
        return m_ScreenElementInternal->IsTextTruncated(pfIsTruncated, nNumSymbolsFit);
    }

    HRESULT GetColors(COLORREF* pColorRefText, COLORREF* pColorRefBackGround)
    {
        return m_ScreenElementInternal->GetColors((int*)pColorRefText, (int*)pColorRefBackGround);
    }

    HRESULT GetBoundingRectangle(int *pnLeft, int *pnTop, int *pnWidth, int *pnHeight)
    {
        return m_ScreenElementInternal->GetBoundingRectangle(pnLeft, pnTop, pnWidth, pnHeight);
    }

    HRESULT Equals(ScreenElement* pScreenElement, BOOL* pfEquals)
    {
        return m_ScreenElementInternal->Equals(pScreenElement->get_IScreenElement(), pfEquals);
    }

    HRESULT GetPlaybackFlag(int nPlaybackFlag, VARIANT * pvarPlaybackFlagValue)
    {
        return m_ScreenElementInternal->GetPlaybackFlag(nPlaybackFlag, pvarPlaybackFlagValue);
    }

    HRESULT SetPlaybackFlag(int nPlaybackFlag, VARIANT varPlaybackFlagValue)
    {
        return m_ScreenElementInternal->SetPlaybackFlag(nPlaybackFlag, varPlaybackFlagValue);
    }

    bool MatchesQueryId(BSTR bstrQueryId)
    {
        BOOL fMatches = false;

        m_ScreenElementInternal->MatchesQueryId(bstrQueryId, &fMatches);

        return (fMatches) ? true : false;
    }

    #pragma endregion Primitives

    #pragma region Properties

    HWND get_hWnd()
    {
        INT64 nHwnd;
        if(S_OK == m_ScreenElementInternal->get_hWnd(&nHwnd))
        {
            m_Hwnd = (HWND) nHwnd;
            return m_Hwnd;
        }
        else
        {
            return NULL;
        }
    }

    IAccessible* get_Accessible()
    {
        IAccessible* pAcc;
        VARIANT varDisp;

        if(S_OK == m_ScreenElementInternal->get_Accessible(&varDisp) && varDisp.vt == VT_DISPATCH && varDisp.pdispVal != NULL)
        {
            if(S_OK != varDisp.pdispVal->QueryInterface(__uuidof(IAccessible), (void**)&pAcc))
            {
                pAcc = NULL;
            }
        }

        if(varDisp.pdispVal) 
        {
            varDisp.pdispVal->Release();
        }

        return pAcc;
    }

    VARIANT get_ChildId()
    {
        VARIANT childId;
        m_ScreenElementInternal->get_ChildId(&childId);
        return childId;
    }

    RECT get_BoundingRect()
    {
        RECT rect = {0, 0, 0, 0 };
        long xLeft,  yTop,  cxWidth,  cyHeight;
        IAccessible* pAcc;

        if (NULL != (pAcc = get_Accessible()))
        {
            if (S_OK == pAcc->accLocation(&xLeft,  &yTop,  &cxWidth,  &cyHeight,  get_ChildId()))
            {
                rect.left = xLeft;
                rect.top = yTop;
                rect.right = xLeft + cxWidth;
                rect.bottom = yTop + cyHeight;
            }

            pAcc->Release();
        }

        return rect;
    }

    ScreenElement* get_Parent()
    {
        IScreenElement* pScreenElement;

        if (S_OK != m_ScreenElementInternal->get_Parent(&pScreenElement))
        {
            return NULL;
        }
        else
        {
            return new ScreenElement(pScreenElement);
        }
    }

    IHTMLElement* get_HTMLElement()
    {
        IHTMLElement* pIHTMLElement;

        if(S_OK == (m_ScreenElementInternal->get_HTMLElement(&pIHTMLElement)))
        {
            return pIHTMLElement;
        }
        else
        {
            return NULL;
        }
    }

    int get_AccTechnology()
    {
        int nAccTechnology;

        if(S_OK == (m_ScreenElementInternal->get_AccTechnology(&nAccTechnology)))
        {
            return nAccTechnology;
        }
        else
        {
            return -1;
        }
    }

    wchar_t* get_Name()
    {
        if (m_Name != NULL)
        {
            SysFreeString(m_Name);
        }

        if (S_OK == m_ScreenElementInternal->get_Name(&m_Name)) 
        {
            return m_Name;
        }
        else
        {
            m_Name = NULL;
            return NULL;
        }
    }

    wchar_t* get_ClassName()
    {
        if (m_ClassName != NULL)
        {
            SysFreeString(m_ClassName);
        }

        if (S_OK == m_ScreenElementInternal->get_ClassName(&m_ClassName)) 
        {
            return m_ClassName;
        }
        else
        {
            m_ClassName = NULL;
            return NULL;
        }
    }

    wchar_t* get_RoleText()
    {
        if (m_RoleText != NULL)
        {
            SysFreeString(m_RoleText);
        }

        if (S_OK == m_ScreenElementInternal->get_RoleText(&m_RoleText)) 
        {
            return m_RoleText;
        }
        else
        {
            m_RoleText = NULL;
            return NULL;
        }
    }

    wchar_t* get_Value()
    {
        if (m_Value != NULL)
        {
            SysFreeString(m_Value);
        }

        if (S_OK == m_ScreenElementInternal->get_Value(&m_Value)) 
        {
            return m_Value;
        }
        else
        {
            m_Value = NULL;
            return NULL;
        }
    }

    wchar_t* get_State()
    {
        if (m_State != NULL)
        {
            SysFreeString(m_State);
        }

        if (S_OK == m_ScreenElementInternal->get_State(&m_State)) 
        {
            return m_State;
        }
        else
        {
            m_State = NULL;
            return NULL;
        }
    }

    wchar_t* get_Description()
    {
        if (m_Description != NULL)
        {
            SysFreeString(m_Description);
        }

        if (S_OK == get_Description(&m_Description)) 
        {
            return m_Description;
        }
        else
        {
            m_Description = NULL;
            return L"";
        }
    }

    #pragma endregion Properties

};

#pragma endregion ScreenElement

#pragma region ScreenElementCollection implementation

inline ScreenElementCollection::ScreenElementCollection()
{
    _internalCollection = DPA_Create(ELEMENTS_EXPAND);
}

inline ScreenElementCollection::~ScreenElementCollection()
{
    Clean();

    if (_internalCollection != NULL)
    {
        DPA_Destroy(_internalCollection);
    }

    _internalCollection = NULL;
}

inline int ScreenElementCollection::Count() 
{
    if (_internalCollection != NULL)
    {
        // The first item in the struct of HDPA is the count.
        return (*(int *)(_internalCollection));
    }
    else
    {
        return 0;
    }
}

inline bool ScreenElementCollection::Add(ScreenElement* screenElement)
{
    if (_internalCollection != NULL)
    {
        if (-1 != DPA_InsertPtr(_internalCollection, Count(), screenElement))
        {
            return true;
        }
    }

    return false;
}

inline void ScreenElementCollection::DeleteByIndex(int index)
{
    ScreenElement *pScreenElement;

    if (index < Count())
    {
        pScreenElement = (ScreenElement*) DPA_GetPtr(_internalCollection, index);
        delete pScreenElement;
    }

    DPA_DeletePtr(_internalCollection, index);
}

inline void ScreenElementCollection::Clean()
{
    while(0 < Count())
    {
        DeleteByIndex(0);
    }

    DPA_DeleteAllPtrs(_internalCollection);
}

inline ScreenElement* ScreenElementCollection::operator[](int i)
{
    ScreenElement *pScreenElement = (ScreenElement*) DPA_GetPtr(_internalCollection, i);

    // Update HWND for the element in collection.  This is necessary since WFR.DLL is using HWND to make sure that the message was processed correctly
    // On the other hand if the flag FLAG_SEARCH_FIND_ALL (the same as attribute [FindAll]) is set, ElementFetcher doesn't update HWND 
    // since WindowFromAccessibleObject is a very expensive procedure and often it's unacceptable to call it for all elements in the collection
    if(pScreenElement != NULL)
    {
        pScreenElement->get_hWnd();
    }

    return pScreenElement;
}

#pragma endregion ScreenElementCollection implementation

#pragma warning (default : 4311)
#pragma warning (default : 4312)
#pragma warning (default : 4995)
#pragma warning (default : 4996)
