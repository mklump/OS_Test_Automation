#include "screenelement.h"				// RPF
#include "SKUDIFF_UTIL.h"                // SKU Header
#include "rpf_SKUDIFF.h"                // SKU Master header for RPF QueryIDs and ResKeys

//#include <windows.h>					// Common Windows types
//#include "LoggingFunctions.h"			// MASH
#include "LoggingFunctions.h"			// MASH


//#include "Winsatcominterfacei.h"		// Windows Experience Index
//#include "unknwn.h"						// For custom logger

namespace SKUDiff
{
	// "Control Panel Home" assumes a "link" role only if the Control Panel is opened in the "Classic" view.
	// If the Control Panel is already opened in the "Home" view then "Control Panel Home" assumes a "text" role.
	//
	// So set timeout to 10 seconds to quickly check if CPL is currently being opened in 
	// Classic (Control Panel Home role = link) or Classic (Control Panel Home role = text) view.
	// Save the original timeout so it can be set later.

	int GetControlPanelMode()
	{
		try
		{
			LOGLIBENTER;

			int originalTimeout = SetSearchTimeOut(5000);
			BOOL HomeView = FALSE;
			BOOL ClassicView = FALSE;

			ScreenElement* pScreenElement;

			if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(CPL_HOME_VIEW_LINK)))
			{	
				if (wcscmp(pScreenElement->get_RoleText(),L"text") == 0)
				{
					HomeView = TRUE;
				}
				delete pScreenElement;
			}
			else
			{
				LogTestInfoW(__FUNCTIONW__, L"Failed to get Role of Home View.");
			}
			if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(CPL_CLASSIC_VIEW_LINK)))
			{	
				if (wcscmp(pScreenElement->get_RoleText(),L"text") == 0)
				{
					ClassicView = TRUE;
				}
				delete pScreenElement;		}
			else
			{
				LogTestInfoW(__FUNCTIONW__, L"Failed to get Role of Classic View.");
			}

			SetSearchTimeOut(originalTimeout);

			if (ClassicView == HomeView)
			{
				LibraryLogInfoW(__FUNCTIONW__, L"Control Panel appears to be in an impossible state, this is a problem.");
				LOGLIBRETURN_int(CPL_IS_INVALID);
			}
			else
			{
				if (HomeView == TRUE)
				{
					LibraryLogInfoW(__FUNCTIONW__, L"Control Panel appears to be in Home View.");
					LOGLIBRETURN_int(CPL_IS_HOME);
				}
				if (ClassicView == TRUE)
				{
					LibraryLogInfoW(__FUNCTIONW__, L"Control Panel appears to be in Classic View.");
					LOGLIBRETURN_int(CPL_IS_CLASSIC);
				}
				LOGLIBRETURN_int(CPL_IS_INVALID);
			}
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s returning CPL_IS_INVALID due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_int(CPL_IS_INVALID);
		}
	}
	__checkReturn HRESULT SetControlPanelHomeView()
	{
		try
		{
			LOGLIBENTER;
			LibraryLogInfoW(__FUNCTIONW__, L"Setting Control Panel to Home View.");

			if (GetControlPanelMode() != CPL_IS_HOME)
			{
				int originalTimeout = SetSearchTimeOut(5000);

				if (FAILED(WOWFromPartialQueryId(CPL_HOME_VIEW_LINK)))
				{
					// role = text. control panel is already in home view. move on.
					LogTestInfoW(__FUNCTIONW__, L"Attempt to switch to Home View failed.");
					SetSearchTimeOut(originalTimeout);
					LOGLIBRETURN_HRESULT(E_FAIL);
				}
				else
				{
					if (FAILED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))))
					{
						LogTestInfoW(__FUNCTIONW__, L"Attempt to switch to Home View failed.");
						SetSearchTimeOut(originalTimeout);
						LOGLIBRETURN_HRESULT(E_FAIL);
					}

				}
				SetSearchTimeOut(originalTimeout);
			}
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	__checkReturn HRESULT SetControlPanelClassicView()
	{		
		try
		{
			LOGLIBENTER;

			LibraryLogInfoW(__FUNCTIONW__, L"Setting Control Panel to Classic View.");
			if (GetControlPanelMode() != CPL_IS_CLASSIC)
			{
				int originalTimeout = SetSearchTimeOut(5000);

				if (FAILED(FromPartialQueryId(CPL_CLASSIC_VIEW_LINK)))
				{
					// role = text. control panel is already in home view. move on.
					LogTestInfoW(__FUNCTIONW__, L"Attempt to switch to Classic View failed.");
					SetSearchTimeOut(originalTimeout);
					LOGLIBRETURN_HRESULT(E_FAIL);
				}
				else
				{
					if (FAILED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))))
					{
						LogTestInfoW(__FUNCTIONW__, L"Attempt to switch to Classic View failed.");
						SetSearchTimeOut(originalTimeout);
						LOGLIBRETURN_HRESULT(E_FAIL);
					}

				}
				SetSearchTimeOut(originalTimeout);
			}
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}


	HRESULT CloseControlPanel()
	{
		try
		{
			LOGLIBENTER;
			LOGLIBRETURN_HRESULT(LeftClickUntilGone(CPL_CLOSE_BTN));
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}

	}
	__checkReturn HRESULT OpenStartMenu()
	{	
		try
		{
			LOGLIBENTER;

			LibraryLogInfoW(__FUNCTIONW__, L"Open Start Menu.");
			BOOL StartOpen;
			ScreenElement* pScreenElement;
			//
			// Check if Start menu already open, if so, close it to return to a known state.
			//
			if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(START_BUTTON)))
			{	
				if (wcscmp(pScreenElement->get_State(),L"pressed") == 0)
				{
					LogTestInfoW(__FUNCTIONW__, L"Start Menu already open, closing to reset.");
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					Sleep(1000); // pause a second, so it doesn't become a double-click.
				}
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT)); // open the start menu for use.
				delete pScreenElement;
				LOGLIBRETURN_HRESULT(NOERROR);
			}
			else
			{
				LogTestInfoW(__FUNCTIONW__, L"Could not locate Start Button.");
				LOGLIBRETURN_HRESULT(E_FAIL);
			}
		}
		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	__checkReturn HRESULT OpenWelcomeCenter()
	{
		try
		{
			LOGLIBENTER;

			LibraryLogInfoW(__FUNCTIONW__, L"Open Welcome Center.");
			HRESULT hr = E_FAIL;
			if(SUCCEEDED(OpenStartMenu()))
			{
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_WELCOME_CENTER));
				if (SUCCEEDED(hr))
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					if (SUCCEEDED(hr))
					{
						LOGLIBRETURN_HRESULT(NOERROR);

					}
				}
			}
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	__checkReturn HRESULT OpenControlPanel()
	{
		try
		{
			LOGLIBENTER;

			LibraryLogInfoW(__FUNCTIONW__, L"Open Control Panel.");
			// if the Start Menu takes more than 5 seconds to open, you've got worse problems.
			int originalTimeout = SetSearchTimeOut(5000);
			int FindAttempts = 0;
			// Close any existing Control Panels
			CloseControlPanel();
			if (SUCCEEDED(OpenStartMenu()))
			{
				while (FindAttempts++ < 5)
				{
					if(WOWIsAvailable(1000, STARTMENU_CONTROL_PANEL))
					{
						if(SUCCEEDED(WOWFromPartialQueryId(STARTMENU_CONTROL_PANEL)))
						{
							break;
						}
					}
					if(WOWIsAvailable(1000, CLASSIC_STARTMENU_CONTROL_PANEL))
					{
						if(SUCCEEDED(WOWFromPartialQueryId(CLASSIC_STARTMENU_CONTROL_PANEL)))
						{
							break;
						}
					}
				}

				if (FAILED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))))
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to click Control Panel.");
					SetSearchTimeOut(originalTimeout);
					LOGLIBRETURN_HRESULT(E_FAIL);
				}
				LibraryLogInfoW(__FUNCTIONW__, L"Clicked Control Panel.");


			}
			else
			{
				LogTestInfoW(__FUNCTIONW__, L"Start Menu did not Open.");
				SetSearchTimeOut(originalTimeout);
				LOGLIBRETURN_HRESULT(E_FAIL);
			}
			SetSearchTimeOut(originalTimeout);
			LOGLIBRETURN_HRESULT(NOERROR);

		}
		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	__checkReturn HRESULT OpenControlPanelClassicView()
	{
		try
		{
			LOGLIBENTER;

			LibraryLogInfoW(__FUNCTIONW__, L"Open Control Panel Classic View.");
			if (SUCCEEDED(OpenControlPanel()))
			{
				if (SUCCEEDED(SetControlPanelClassicView()))
				{
					LOGLIBRETURN_HRESULT(NOERROR);
				}
			}
			LogTestInfoW(__FUNCTIONW__, L"SetControlPanelHomeView Failed");
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	__checkReturn HRESULT OpenControlPanelHomeView()
	{
		try
		{
			LOGLIBENTER;
			LibraryLogInfoW(__FUNCTIONW__, L"Open Control Panel Home View.");
			if (SUCCEEDED(OpenControlPanel()))
			{
				if (SUCCEEDED(SetControlPanelHomeView()))
				{
					LOGLIBRETURN_HRESULT(NOERROR);
				}
			}
			LogTestInfoW(__FUNCTIONW__, L"SetControlPanelHomeView Failed");
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	__checkReturn HRESULT OpenSpecificClassicControlPanel(__in wchar_t* Item)
	{
		try
		{
			LOGLIBENTER;
			LibraryLogInfoW(__FUNCTIONW__, L"Open Specific Classic Control Panel (obselete, try OpenSpecificControlPanel())");

			if(SUCCEEDED(OpenControlPanelClassicView()))
			{
				Snooze(1);
				//find the icon
				if (FAILED(LOG_FAILED_HR(WOWFromPartialQueryId(Item))))
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to locate Icon.");
					LOGLIBRETURN_HRESULT(E_FAIL);
				}

				//double click the icon
				if (FAILED(LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT))))
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to double click Icon.");
					LOGLIBRETURN_HRESULT(E_FAIL);
				}

			}
			else
			{
				LOGLIBRETURN_HRESULT(E_FAIL);
			}
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	__checkReturn HRESULT OpenSpecificHomeControlPanel(__in wchar_t* Section,__in wchar_t* Link)
	{
		try
		{
			LOGLIBENTER;

			LibraryLogInfoW(__FUNCTIONW__, L"Open Specific Home Control Panel (obselete, try OpenSpecificControlPanel())");

			if(SUCCEEDED(OpenControlPanelHomeView()))
			{
				int originalTimeout = SetSearchTimeOut(5000);

				Snooze(1);
				//find the section
				if (FAILED(LOG_FAILED_HR(WOWFromPartialQueryId(Section))))
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to locate Section.");
					SetSearchTimeOut(originalTimeout);
					LOGLIBRETURN_HRESULT(E_FAIL);
				}

				//click the section
				if (FAILED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))))
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to click Section.");
					SetSearchTimeOut(originalTimeout);
					LOGLIBRETURN_HRESULT(E_FAIL);
				}

				Snooze(1);
				//find the link
				if (FAILED(LOG_FAILED_HR(WOWFromPartialQueryId(Link))))
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to locate Link.");
					SetSearchTimeOut(originalTimeout);
					LOGLIBRETURN_HRESULT(E_FAIL);
				}

				//click the link
				if (FAILED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))))
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to click Link.");
					SetSearchTimeOut(originalTimeout);
					LOGLIBRETURN_HRESULT(E_FAIL);
				}

				SetSearchTimeOut(originalTimeout);
				LOGLIBRETURN_HRESULT(NOERROR);
			}
			else
			{
				LogTestInfoW(__FUNCTIONW__, L"OpenControlPanelHomeView() Failed.");
				LOGLIBRETURN_HRESULT(E_FAIL);
			}
		}
		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	__checkReturn HRESULT OpenSpecificControlPanel(__in PCWSTR pszQueryId, ...)
	{
		try
		{
			LOGLIBENTER;
			//#define CONTROLPANELHOMELINK  L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Name = 'CPCategoryPanel' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'link'"
			//#define CONTROLPANELCLASSICICON  L";Name => '{0}' && ClassName => 'CabinetWClass';ControlID = '1';Name = '{1}' && Role = 'list item'"
			// Initialize variable arguments.
			HRESULT hr = NOERROR;
			va_list arguments;
			va_start( arguments, pszQueryId);

			wchar_t* pszResKeyq;
			wchar_t* pszResKey0;
			wchar_t* pszResKey1;

			wchar_t GlobalizedQuery[2048];
			//PCWSTR pszQueryId2;
			LibraryLogInfoW(__FUNCTIONW__, L"Open Specific Control Panel.");

			// Determine if there are 1 or 2 Queries, by checking if the first query is for a CP icon.
			if( wcsncmp(CONTROLPANELCLASSICICON, pszQueryId, 1024))
			{
				if(FAILED(hr = OpenControlPanelHomeView()))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to open Home view.");
					LOGLIBRETURN_HRESULT(hr);
				}
				LibraryLogInfoW(__FUNCTIONW__, L"Control Panel - Home View");

				LibraryLogInfoW(__FUNCTIONW__, L"Control Panel - Opening Section");

				pszResKey0 = _wcsdup(va_arg( arguments, LPWSTR));
				pszResKey1 = _wcsdup(va_arg( arguments, LPWSTR));
				if (FAILED(hr = WOWGlobalizeQueryId(GlobalizedQuery, 2048, pszQueryId, pszResKey0, pszResKey1)))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to globalize Section.");
					LOGLIBRETURN_HRESULT(hr);
				}

				if (FAILED(LOG_FAILED_HR(hr = FromPartialQueryId(GlobalizedQuery))))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to locate Section.");
					LOGLIBRETURN_HRESULT(hr);
				}

				if (FAILED(LOG_FAILED_HR(hr = LeftButtonClick(CLICKABLE_POINT))))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to click Section.");
					LOGLIBRETURN_HRESULT(hr);
				}

				Snooze(1);
				LibraryLogInfoW(__FUNCTIONW__, L"Control Panel - Link");

				pszResKeyq = _wcsdup(va_arg( arguments, LPWSTR));
				pszResKey0 = _wcsdup(va_arg( arguments, LPWSTR));
				pszResKey1 = _wcsdup(va_arg( arguments, LPWSTR));
				if (FAILED(hr = WOWGlobalizeQueryId(GlobalizedQuery, 2048, pszResKeyq, pszResKey0, pszResKey1)))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to globalize Link.");
					LOGLIBRETURN_HRESULT(hr);
				}

				if (FAILED(hr = FromPartialQueryId(GlobalizedQuery)))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to locate Link.");
					LOGLIBRETURN_HRESULT(hr);
				}

				if (FAILED(hr = LeftButtonClick(CLICKABLE_POINT)))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to click Link.");
					LOGLIBRETURN_HRESULT(hr);
				}

			}
			else
			{
				if(FAILED(hr = OpenControlPanelClassicView()))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to open Classic view.");
					LOGLIBRETURN_HRESULT(hr);
				}
				LibraryLogInfoW(__FUNCTIONW__, L"Control Panel - Classic View");

				LibraryLogInfoW(__FUNCTIONW__, L"Control Panel - Icon");

				pszResKey0 = _wcsdup(va_arg( arguments, LPWSTR));
				pszResKey1 = _wcsdup(va_arg( arguments, LPWSTR));
				if (FAILED(hr = WOWGlobalizeQueryId(GlobalizedQuery, 2048, CONTROLPANELCLASSICICON, pszResKey0, pszResKey1)))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to globalize Icon.");
					LOGLIBRETURN_HRESULT(hr);
				}

				if (FAILED(hr = FromPartialQueryId(GlobalizedQuery)))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to locate Icon.");
					LOGLIBRETURN_HRESULT(hr);
				}

				if (FAILED(hr = LeftButtonClick(CLICKABLE_POINT)))
				{
					LogTestInfoW(__FUNCTIONW__, L"Control Panel - Failed to click Icon.");
					LOGLIBRETURN_HRESULT(hr);
				}

			}
			LOGLIBRETURN_HRESULT(NOERROR);
		}

		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}


	__checkReturn HRESULT OpenAllPrograms()
	{
		try
		{
			LOGLIBENTER;
			LibraryLogInfoW(__FUNCTIONW__, L"Opening 'All Programs'");
			HRESULT hr = OpenStartMenu();
			if (SUCCEEDED(hr))
			{
				hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
				if (SUCCEEDED(hr))  
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					if (SUCCEEDED(FromPartialQueryId(STARTMENU_ALLPROGRAMS)))  
					{

						hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					}
				}
			}
			LOGLIBRETURN_HRESULT(hr);

		}

		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}

	}

	// Used to ensure excess windows are not cluttering the test machine, used before and after tests.

	HRESULT LeftClickUntilGone(__in PCWSTR pszQueryId, ...)
	{
		try
		{
			LOGLIBENTER;
			LibraryLogInfoW(__FUNCTIONW__, L"Left Click Until Gone - %s", pszQueryId);
			int CloseAttempts = 0;
			// Initialize variable arguments.
			va_list arguments;
			va_start( arguments, pszQueryId);
			wchar_t GlobalizedQuery[2048];
			if (SUCCEEDED(WOWGlobalizeQueryIdInternal(GlobalizedQuery, 2048, pszQueryId, arguments)))//
			{
				if (IsAvailable(1000, GlobalizedQuery))
				{
					while (IsAvailable(1000, GlobalizedQuery) && CloseAttempts++ < 10)
					{
						FromPartialQueryId(GlobalizedQuery);
						LeftButtonClick(CLICKABLE_POINT);
						Snooze(1);
					}
					if (CloseAttempts > 9)
					{
						LogTestInfoW(__FUNCTIONW__, L"Too many close attempts for %s.", GlobalizedQuery);
						LOGLIBRETURN_HRESULT(E_FAIL);				
					}
				}
			}
			else
			{
				LogTestInfoW(__FUNCTIONW__, L"Could not Globalize %s.", pszQueryId);
			}
			LOGLIBRETURN_HRESULT(NOERROR);
		}

		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}

	}

	HRESULT MultiLeftClickUntilGone(__in unsigned int Count, ...)
	{
		try
		{
			LOGLIBENTER;

			LibraryLogInfoW(__FUNCTIONW__, L"Multi Left Click Until Gone - %d items", Count);
			if (Count > 10)
			{
				throw (L"More than 10 items is too many.");
			}

			wchar_t** GlobalizedQuerys = new wchar_t*[Count];

			wchar_t* pszBracketDigits = L"0123456789";
			wchar_t pszBracketTemplate[5];
			wchar_t pszOldComposedQuery[768];
			wchar_t pszNewComposedQuery[768];
			wchar_t* pszQueryID;
			wchar_t* pszResKey;
			wchar_t pszResKeyValue[128];


			//Pre-globalize all given Queries.
			// Initialize variable arguments.
			va_list arguments;
			va_start( arguments, Count);
			//if (SUCCEEDED(WOWGlobalizeQueryIdInternal(GlobalizedQuerys[Current], 2048, pszQueryId, arguments)))
			for (unsigned int j=0;j<Count;j++)
			{
				LibraryLogInfoW(__FUNCTIONW__, L"Globalizing Query %d.",j);
				GlobalizedQuerys[j] = new wchar_t[768];

				pszQueryID = _wcsdup(va_arg( arguments, LPWSTR));

				wcsncpy_s(pszOldComposedQuery, 768, pszQueryID, wcslen(pszQueryID));
				wcsncpy_s(pszNewComposedQuery, 768, pszQueryID, wcslen(pszQueryID));


				for(unsigned int i = 0;i<10;i++)
				{
					swprintf_s(pszBracketTemplate,5,L"{%c}",pszBracketDigits[i]);
					if(wcsstr(pszOldComposedQuery, pszBracketTemplate))
					{
						LibraryLogInfoW(__FUNCTIONW__, L"Extracting Resource %d.",i);
						pszResKey = _wcsdup(va_arg( arguments, LPWSTR));
						if (FAILED(WOWExtractResourceString(pszResKey,pszResKeyValue,128)))
						{
							LibraryLogInfoW(__FUNCTIONW__, L"Failed to extract a resource.");
							//LOGLIBEXIT;
							//for (unsigned int j=0;j<Count;j++)
							//{
							//	delete[] GlobalizedQuerys[j];
							//}
							//delete[] GlobalizedQuerys;
							//LOGLIBRETURN_HRESULT(E_FAIL);
							if(FAILED(wcsreplace(pszNewComposedQuery, 768, pszOldComposedQuery,pszBracketTemplate,L"Failed Resource Extraction")))
							{
								throw (L"wcsreplace() Failed!");
							}
						}
						if(FAILED(wcsreplace(pszNewComposedQuery, 768, pszOldComposedQuery,pszBracketTemplate,pszResKeyValue)))
						{
							throw (L"wcsreplace() Failed!");
						}
						////LogTestInfoW(__FUNCTIONW__,	L"New: [%s]", pszNewComposedQuery);
						wcsncpy_s(pszOldComposedQuery, 768, pszNewComposedQuery, wcslen(pszNewComposedQuery));
					}
					else 
					{
						i=10;
					}
				}
				wcsncpy_s(GlobalizedQuerys[j], 768, pszNewComposedQuery, wcslen(pszNewComposedQuery));
			}
			// Cycle through the pre-globalized queries, and click them. round-robin.

			int CloseAttempts = 0;
			int cFound = 10;
			while ((CloseAttempts++ < 10) && (cFound > 0))
			{
				cFound = 0;
				for (unsigned int j=0;j<Count;j++)
				{
					if (IsAvailable(1000, GlobalizedQuerys[j]))
					{
						cFound++;
						ScreenElement* se;
						se = ScreenElement::FromPartialQueryId(GlobalizedQuerys[j]);
						se->LeftButtonClick(CLICKABLE_POINT);//
						Snooze(1);
					}
				}
				LogTestInfoW(__FUNCTIONW__, L"Close Cycle %d found %d items.", CloseAttempts, cFound);

			}
			if (CloseAttempts > 9)
			{
				LogTestInfoW(__FUNCTIONW__, L"Too many close attempt cycles.");
			}
			for (unsigned int j=0;j<Count;j++)
			{
				delete[] GlobalizedQuerys[j];
			}

			delete[] GlobalizedQuerys;
			LOGLIBRETURN_HRESULT(NOERROR);
		}

		catch (...)
		{

			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}

	}
}
