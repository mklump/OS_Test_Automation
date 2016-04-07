//////////////////////////////////////////////////////////////
//                 
//  This file contains function to extract resources from XML based files.
//  For use in testing SKU Differentiation of Microsoft Windows
//	
//  Copyright (C) Microsoft Corporation, 2008. For internal use only.
//
//////////////////////////////////////////////////////////////

// a-jomul: Jan 2008, created file by forking from SKUDIFF_UTIL.cpp
//			Feb 2008, completed XML extraction functions.

#include "screenelement.h"				// RPF
#include "SKUDIFF_UTIL.h"
#include <shellapi.h>
#include <shlobj.h>
#include "rpf_SKUDIFF.h"
#include "LoggingFunctions.h"			// MASH

namespace SKUDiff
{
	/////////////////////////////////////////////////////////
	// Gets the system locale, by assuming the the first 'preferred' locale is the system locale.
	// No idea what may occur on a multi-locale system.
	/////////////////////////////////////////////////////////////

	__checkReturn HRESULT GetLocaleString(__out_ecount(6) PWSTR Language)
	{
		try
		{
			LOGLIBENTER;
			//TODO error checking
			DWORD NumLanguages = 1; // don't care
			DWORD LenLanguages = 64;
			wchar_t Languages[64];

			//Windows API

			if(GetSystemPreferredUILanguages(MUI_LANGUAGE_NAME,  &NumLanguages,  Languages,  &LenLanguages))
			{
				//LibraryLogInfoW(__FUNCTIONW__, L"Locale sizes: %d languages in %d characters",NumLanguages,LenLanguages);

				//Only return the primary language
				if(wcscpy_s(Language, 6, Languages))
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to Copy Locale information!");
				}
				LibraryLogInfoW(__FUNCTIONW__, L"Locale: %s",Language);
				LOGLIBRETURN_HRESULT(NOERROR);
			}
			LogTestInfoW(__FUNCTIONW__, L"Failed to get Locale information!");
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	////////////////////////////////////////////////////////////////////
	// Gets the path where Vista stores .MUM files by default.
	////////////////////////////////////////////////////////////////

	__checkReturn HRESULT GetWindowsServicingPackagesPath(__out_ecount(MAX_PATH) PWSTR Path)
	{
		try
		{
			LOGLIBENTER;
			wchar_t* pwszWindirPath; 
			SHGetKnownFolderPath(FOLDERID_Windows,0,NULL,&pwszWindirPath); // Windows API available in Vista+
			wcscpy_s(Path,MAX_PATH,pwszWindirPath);
			PathAppendW(Path, L"servicing\\packages\\"); // from SHLWAPI
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (...)
		{
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	////////////////////////////////////////////////////////////////////
	// Gets the folder under system32 that contains MUI files for the current locale.
	////////////////////////////////////////////////////////////////

	__checkReturn HRESULT GetWindowsSystem32LocalePath(__out_ecount(MAX_PATH) PWSTR Path)
	{
		try
		{
			LOGLIBENTER;
			wchar_t* pwszSystemPath; 
			wchar_t pwszLocale[64];

			//Get raw path string to system32
			//Windows API available in Vista+
			if(FAILED(SHGetKnownFolderPath(FOLDERID_System,0,NULL,&pwszSystemPath))) 
			{
				throw (L"Call to SHGetKnownFolderPath() Failed!");
			}

			//Get the current system Locale ("en-US" for example)
			if FAILED(GetLocaleString(pwszLocale))
			{
				throw (L"Call to GetLocaleString() Failed!");
			}

			//Copy the system path to the temp string
			if(0 != wcscpy_s(Path,MAX_PATH,pwszSystemPath))
			{
				throw (L"call to wcscpy_s() Failed!");
			}

			//add the locale folder name to the temp string
			//from Shlwapi.h
			if(TRUE != PathAppendW(Path, pwszLocale))
			{
				throw (L"Call to PathAppendW() Failed!");
			}

			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	/////////////////////////////////////////////////////////////////////
	// Creates a filespec appropriate for an optional component .MUM file
	// Needs to be given the component name, but automatically determines the locale.
	// Behavior if multiple locales are available is unknown.
	///////////////////////////////////////////////////////////////////

	__checkReturn HRESULT GetOCfilename(__in PCWSTR  Component, __out_ecount(cchFilename) PWSTR pszFilename, __in unsigned int cchFilename = MAX_PATH)
	{
		try
		{
			LOGLIBENTER;
			wchar_t pwszMUMFile[MAX_PATH];
			wchar_t pwszLocale[64];

			//LogTestInfoW(__FUNCTIONW__, L"Component: %s Locale: %s",Component, pwszLocale);

			if FAILED(GetWindowsServicingPackagesPath(pwszMUMFile))
			{
				throw (L"Call to GetWindowsServicingPackagesPath() Failed!");
			}
			//LogTestInfoW(__FUNCTIONW__, L"Path: %s",pwszMUMFile);

			if FAILED(GetLocaleString(pwszLocale))
			{
				throw (L"Call to GetLocaleString() Failed!");
			}

			// Build a wildcarded package name

			//before component
			if(0 != wcsncat_s(pwszMUMFile,cchFilename,L"Microsoft-Windows-", _TRUNCATE))
			{
				throw (L"first call to wcsncat_s() Failed!");
			}
			//component
			if(0 != wcsncat_s(pwszMUMFile,cchFilename,Component, _TRUNCATE))
			{
				throw (L"second call to wcsncat_s() Failed!");
			}
			//Between component and Locale
			if(0 != wcsncat_s(pwszMUMFile,cchFilename,L"-Package~*~",_TRUNCATE))
			{
				throw (L"third call to wcsncat_s() Failed!");
			}
			//System Locale
			if(0 != wcsncat_s(pwszMUMFile,cchFilename,pwszLocale,_TRUNCATE))
			{
				throw (L"fourth call to wcsncat_s() Failed!");
			} 
			//after Locale to end
			if(0 != wcsncat_s(pwszMUMFile,cchFilename,L"~*.mum",_TRUNCATE))
			{
				throw (L"fifth call to wcsncat_s() Failed!");
			}

			if(0 != wcscpy_s(pszFilename,cchFilename,pwszMUMFile))
			{
				throw (L"call to wcscpy_s() Failed!");
			}

			LibraryLogInfoW(__FUNCTIONW__, L"Looking for .MUM file with wildcarded name: %s",pwszMUMFile);

			LOGLIBRETURN_HRESULT(NOERROR);	
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	////////////////////////////////////////////////////////////////////
	// Copies an entire file into a wchar array, allocates the array itself.
	// Aborts if file larger than 300k, accepts wildcarded names, if
	// multiple files match the filespec, behavior is undefined.
	///////////////////////////////////////////////////////////////////

	__checkReturn HRESULT BufferFile(__in PCWSTR  Filename, __deref_inout PWSTR &wBuffer)
	{
		char* Buffer = NULL;
		HANDLE hFile = INVALID_HANDLE_VALUE;

		try
		{
			LOGLIBENTER;
			LibraryLogInfoW(__FUNCTIONW__, L"Attempting to buffer %s into a wide string.",Filename);

			DWORD MaxFileSize = 300000;
			DWORD BytesRead;
			DWORD wBufferSize;
			BOOL fReadFile;
			WIN32_FIND_DATAW fdFile;

			hFile = FindFirstFileW(Filename,&fdFile);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				throw (L"Could not find file matching filespec.");
			}

			if ((fdFile.nFileSizeLow > (MaxFileSize)) || (fdFile.nFileSizeHigh != 0))
			{
				throw (L"File is too big, not going to attempt read.");
			}

			Buffer = (char*)malloc(fdFile.nFileSizeLow+1);
			if (Buffer == NULL)
			{
				throw (L"Malloc of char[%d] for Buffer failed.");
			}

			hFile = CreateFileW(Filename,FILE_READ_DATA,FILE_SHARE_READ,  NULL,  OPEN_EXISTING,  FILE_FLAG_SEQUENTIAL_SCAN,NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				throw(L"Did not get a valid File Handle.");
			}
			if(0 == ReadFile(hFile,Buffer,fdFile.nFileSizeLow,&BytesRead,NULL))
			{
				throw (L"ReadFile Failed.");
			}


			//LibraryLogInfoW(__FUNCTIONW__, L"Read %d bytes", BytesRead);
			wBufferSize=MultiByteToWideChar(CP_UTF8,0,Buffer,BytesRead,(wchar_t*)Buffer,0);
			wBuffer = (wchar_t*)malloc((wBufferSize*sizeof(wchar_t))+1);
			if(wBuffer == NULL)
			{
				throw (L"Malloc of wBuffer failed.");
			}

			if(0 == MultiByteToWideChar(CP_UTF8,0,Buffer,BytesRead,wBuffer,wBufferSize))
			{
				throw (L"MultiByteToWideChar Failed");
			}

			LibraryLogInfoW(__FUNCTIONW__, L"Buffered wchar_t[%d]", wBufferSize);
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (wchar_t *ExceptionString)
		{
			if (hFile != INVALID_HANDLE_VALUE)
			{
				CloseHandle(hFile);
			}
			free(Buffer);
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			if (hFile != INVALID_HANDLE_VALUE)
			{
				CloseHandle(hFile);
			}
			free(Buffer);
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}

	}

	/////////////////////////////////////////////////////////////////
	// Gives a string that should match the opening tag format for an XML element
	// "<* "
	//////////////////////////////////////////////////////////////////

	__checkReturn HRESULT XMLOpenTag(__in PCWSTR TagName,__out_ecount(cchOpenTag) PWSTR  OpenTag, __in unsigned int cchOpenTag)
	{
		try
		{
			LOGLIBENTER;
			//LogTestInfoW(__FUNCTIONW__, L"Making open tag for element \"%s\" with a max length of %d.", TagName, cchOpenTag);

			if (cchOpenTag >= (wcslen(TagName)+2))
			{
				OpenTag[0]=L'<';
				wcsncpy_s(OpenTag+1,cchOpenTag-1,TagName,wcslen(TagName));
				OpenTag[wcslen(TagName)+1]=L' ';
				OpenTag[wcslen(TagName)+2]=NULL;

				//LogTestInfoW(__FUNCTIONW__, L"Generated open tag is \"%s\"", OpenTag);

				LOGLIBRETURN_HRESULT(NOERROR);
			}
		}
		catch (...)
		{
			//try fall through
		}
		LogTestInfoW(__FUNCTIONW__, L"Failed to generate XML open tag extractor code.");

		LOGLIBRETURN_HRESULT(E_FAIL);
	}

	__checkReturn HRESULT XMLOpenTagNoAttr(__in PCWSTR TagName,__out_ecount(cchOpenTag) PWSTR  OpenTag, __in unsigned int cchOpenTag)
	{
		try
		{
			LOGLIBENTER;
			//LogTestInfoW(__FUNCTIONW__, L"Making open tag for element \"%s\" with a max length of %d.", TagName, cchOpenTag);

			if (cchOpenTag >= (wcslen(TagName)+2))
			{
				OpenTag[0]=L'<';
				wcsncpy_s(OpenTag+1,cchOpenTag-1,TagName,wcslen(TagName));
				OpenTag[wcslen(TagName)+1]=L'>';
				OpenTag[wcslen(TagName)+2]=NULL;

				//LogTestInfoW(__FUNCTIONW__, L"Generated open tag is \"%s\"", OpenTag);

				LOGLIBRETURN_HRESULT(NOERROR);
			}
		}
		catch (...)
		{
			//try fall through
		}
		LogTestInfoW(__FUNCTIONW__, L"Failed to generate XML open tag extractor code.");

		LOGLIBRETURN_HRESULT(E_FAIL);
	}


	/////////////////////////////////////////////////////////////////
	// Gives a string that should match the closing tag format for an XML element
	// "</*>"
	//////////////////////////////////////////////////////////////////

	__checkReturn HRESULT XMLCloseTag(__in PCWSTR TagName,__out_ecount(cchCloseTag) PWSTR  CloseTag, __in unsigned int cchCloseTag)
	{
		try
		{
			LOGLIBENTER;
			//LogTestInfoW(__FUNCTIONW__, L"Making close tag for element \"%s\" with a max length of %d.", TagName, cchCloseTag);

			if (cchCloseTag >= (wcslen(TagName)+3))
			{
				CloseTag[0]=L'<';
				CloseTag[1]=L'/';
				wcsncpy_s(CloseTag+2,cchCloseTag-2,TagName,wcslen(TagName));
				CloseTag[wcslen(TagName)+2]=L'>';
				CloseTag[wcslen(TagName)+3]=NULL;
				//LogTestInfoW(__FUNCTIONW__, L"Generated close tag is \"%s\"", CloseTag);

				LOGLIBRETURN_HRESULT(NOERROR);
			}
		}
		catch (...)
		{
			//try fall through
		}
		LogTestInfoW(__FUNCTIONW__, L"Failed to generate XML open tag extractor code.");

		LOGLIBRETURN_HRESULT(E_FAIL);
	}

	/////////////////////////////////////////////////////////////////
	// Gives a string that should match an attribure label in an XML element
	// "*=""
	//////////////////////////////////////////////////////////////////

	__checkReturn HRESULT XMLAttributePrefix(__in PCWSTR AttributeName,__out_ecount(cchAttributePrefix) PWSTR AttributePrefix, __in unsigned int cchAttributePrefix)
	{
		try
		{
			LOGLIBENTER;
			if (cchAttributePrefix >= (wcslen(AttributeName)+3))
			{
				AttributePrefix[0]=L' ';
				wcsncpy_s(AttributePrefix+1,cchAttributePrefix-1,AttributeName,wcslen(AttributeName));
				AttributePrefix[wcslen(AttributeName)+1]=L'=';
				AttributePrefix[wcslen(AttributeName)+2]=L'\"';
				AttributePrefix[wcslen(AttributeName)+3]=NULL;
				LOGLIBRETURN_HRESULT(NOERROR);
			}
		}
		catch (...)
		{
			//try fall through
		}
		LogTestInfoW(__FUNCTIONW__, L"Failed to generate XML AttributePrefix extractor code.");

		LOGLIBRETURN_HRESULT(E_FAIL);
	}

	///////////////////////////////////////////////////////////////////////////////////
	// Given a span of memory, beginning at BufferOpen, and Ending with BufferClose
	//  (that is, not null terminated, nor specified)
	// And a tag name that is found within that span of memory. (Element)
	// Output pointers to:
	//		the opening "<" of the opening tag for the element. (TagOpen)
	//		the ending ">" of the opening tag for the element. (TagClose)
	//		the opening "<" of the closing tag for the element. (BodyClose)
	// If anything seems wrong, set all outputs to NULL, and return failure.
	///////////////////////////////////////////////////////////////////////////////////

	__checkReturn HRESULT XMLElementSpans(__in PCWSTR  BufferOpen,__in PCWSTR  BufferClose , __in PCWSTR  Element,
		__out PWSTR &TagOpen, __out PWSTR &TagClose, __out PWSTR &BodyClose)
	{
		try
		{
			LOGLIBENTER;
			//LibraryLogInfoW(__FUNCTIONW__, L"Looking for %s between BufferOpen:%x and BufferClose:%x",Element,BufferOpen, BufferClose);

			//LogTestInfoW(__FUNCTIONW__, L"BufferOpen:%x  BufferClose:%x",BufferOpen, BufferClose);
			wchar_t OpenTag[128];
			wchar_t OpenTagNoAttr[128];
			wchar_t CloseTag[128];

			if (FAILED(XMLOpenTag(Element, OpenTag, 128)))
			{
				throw (L"Call to XMLOpenTag() failed!");
			}
			if (FAILED(XMLOpenTagNoAttr(Element, OpenTagNoAttr, 128)))
			{
				throw (L"Call to XMLOpenTagNoAttr() failed!");
			}
			if (FAILED(XMLCloseTag(Element, CloseTag, 128)))
			{
				throw (L"Call to XMLCloseTag() failed!");
			}

			//LogTestInfoW(__FUNCTIONW__, L"OpenTag:[%s]",OpenTag);
			//LogTestInfoW(__FUNCTIONW__, L"OpenTagNoAttr:[%s]",OpenTagNoAttr);
			//LogTestInfoW(__FUNCTIONW__, L"CloseTag:[%s]",CloseTag);

			TagOpen = wcsstr(BufferOpen, OpenTag);
			//LogTestInfoW(__FUNCTIONW__, L"TagOpen:%x",TagOpen);
			if ((TagOpen < BufferOpen) || (TagOpen > BufferClose))
			{
				TagOpen = wcsstr(BufferOpen, OpenTagNoAttr);
				if ((TagOpen < BufferOpen) || (TagOpen > BufferClose))
				{
					TagOpen = TagClose = BodyClose = NULL;
					throw (L"Open Tag not found in range!");
				}
			}

			BodyClose = wcsstr(BufferOpen, CloseTag);
			//LogTestInfoW(__FUNCTIONW__, L"BodyClose:%x",BodyClose);
			if ((BodyClose < BufferOpen) || (BodyClose > BufferClose))
			{
				TagOpen = TagClose = BodyClose = NULL;
				throw (L"Close Tag not found in range!");
			}

			TagClose = wcsstr((wchar_t*)(TagOpen+1), L">");
			//LogTestInfoW(__FUNCTIONW__, L"TagClose:%x",TagClose);
			if ((TagClose < TagOpen) || (TagClose > BodyClose))
			{
				TagOpen = TagClose = BodyClose = NULL;
				throw (L"Tag not found in range!");
			}
			//LibraryLogInfoW(__FUNCTIONW__, L"TagOpen:%x TagClose:%x BodyClose:%x",TagOpen, TagClose, BodyClose);

			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}

	}

	__checkReturn HRESULT XMLAttributeValue(__in PCWSTR SegmentOpen,__in PCWSTR SegmentClose ,__in PCWSTR  Attribute, __out_ecount(cchResource) PWSTR  Resource, __in unsigned int cchResource)
	{
		try
		{
			LOGLIBENTER;

			//wchar_t Attributes[1024];
			wchar_t AttributePrefix[128];
			wchar_t * AttributeOpen = NULL;
			wchar_t * AttributeClose = NULL;

			//LibraryLogInfoW(__FUNCTIONW__, L"Extracting value of attribute %s", Attribute);

			//wcsncpy_s(Attributes,1024,SegmentOpen,(SegmentClose-SegmentOpen)-1);


			if (FAILED(XMLAttributePrefix(Attribute, AttributePrefix, 128)))
			{
				throw (L"Call to XMLAttributePrefix() failed!");
			}
			//LogTestInfoW(__FUNCTIONW__, L"AttributePrefix:\"%s\"",AttributePrefix);

			AttributeOpen = wcsstr(SegmentOpen, AttributePrefix)+wcslen(AttributePrefix);
			//LogTestInfoW(__FUNCTIONW__, L"AttributeOpen:%x",AttributeOpen);

			AttributeClose = wcsstr((wchar_t*)(AttributeOpen+1), L"\"");

			if ((AttributeOpen < SegmentOpen) || (AttributeClose > SegmentClose))
			{
				throw (L"Attribute not found in range!");
			}

			wcsncpy_s(Resource,cchResource,AttributeOpen,(AttributeClose-AttributeOpen));
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}

	}


	__checkReturn HRESULT ResourceFromBufferedXML( __out_ecount(cchResource) PWSTR  Resource, __in unsigned int cchResource, __in PWSTR Query, __in PWSTR SegmentOpen, __in PWSTR SegmentClose )

	{
		/////////////////////////////////////////////////////////////
		// First character used becomes the delimiter, just like RPF.
		// > indicates a search for an item with the body of the named tag.
		// < indicates a search within the attributes of the named tag.
		// = indicates the tag or attribute to return the value of.
		// : indicates that a tag has a specific attribute.


		try
		{
			LOGLIBENTER;
			PWSTR InitSegmentOpen = SegmentOpen;
			//PWSTR InitSegmentClose = SegmentClose;
			BOOL fDone = FALSE;
			//TODO: rename variables
			wchar_t* Discard = NULL;
			wchar_t* QD = NULL;
			wchar_t* QP = NULL;
			wchar_t* QE = NULL;
			wchar_t* QB = NULL;

			wchar_t* ptr1 = NULL;
			wchar_t* ptr2 = NULL;
			wchar_t* ptr3 = NULL;
			wchar_t* ptrA = NULL;


			//LogTestInfoW(__FUNCTIONW__, L"Delimiter %c",Query[0] );
			//QD = *Query;
			QP = Query+1;


			do
			{
				QE = StrChrW(QP+1,Query[0]);
				QB = StrChrW(QP+1,L':');
				wchar_t Tag[128];
				wchar_t Attr[128];

				if ((QB < QE) && (QB > QP))
				{

					if (0 != (wcsncpy_s(Tag,128,QP+1,(QB-QP)-1)))
					{
						throw (L"Call to wcsncpy_s() failed!");
					}

					//only the tag with the given attribute.
					if (0 != (wcsncpy_s(Attr,128,QB+1,(QE-QB)-1)))
					{
						throw (L"Call to wcsncpy_s() failed!");
					}

					LibraryLogInfoW(__FUNCTIONW__, L"Looking for Tag [%s] with Attribute %s in %d to %d",Tag, Attr, SegmentOpen-InitSegmentOpen, SegmentClose-InitSegmentOpen);
				}
				else
				{
					if (0 != (wcsncpy_s(Tag,128,QP+1,(QE-QP)-1)))
					{
						throw (L"Call to wcsncpy_s() failed!");
					}
					Attr[0] = L'\0';
					LibraryLogInfoW(__FUNCTIONW__, L"Looking for Tag [%s] in %d to %d",Tag,SegmentOpen-InitSegmentOpen, SegmentClose-InitSegmentOpen);
				}


				switch (QP[0])
				{
				case '>':
					//LogTestInfoW(__FUNCTIONW__, L"Greater");
					// We care about the body of the tag
					if (Attr[0] == L'\0')
					{
						//LogTestInfoW(__FUNCTIONW__, L"No Attr");
						if (FAILED(XMLElementSpans(SegmentOpen, SegmentClose, Tag, Discard,SegmentOpen,SegmentClose)))
						{
							throw (L"Call to XMLElementSpans() in case '>' with No Attr failed!");
						}

						QP=QE+1;
					}
					else
					{
						//LogTestInfoW(__FUNCTIONW__, L"Yes Attr");
						if (FAILED(XMLElementSpans(SegmentOpen, SegmentClose, Tag, ptr1,ptr2,ptr3)))
						{
							throw (L"Call to XMLElementSpans() in case '>' with Attr failed!");
						}

						ptrA = wcsstr(ptr1, Attr);
						if ((ptrA > ptr1) && (ptrA < ptr2))
						{
							//LogTestInfoW(__FUNCTIONW__, L"Attr is in");
							SegmentOpen = ptr2;
							SegmentClose = ptr3;
							QP=QE+1;
						}
						else
						{
							//LogTestInfoW(__FUNCTIONW__, L"Attr not in");
							SegmentOpen = ptr3;
						}
					}
					break;
				case '<':
					//LogTestInfoW(__FUNCTIONW__, L"Less");
					// We care about the attributes of the tag
					;
					if (FAILED(XMLElementSpans(SegmentOpen, SegmentClose, Tag ,SegmentOpen,SegmentClose, Discard)))
					{
						throw (L"Call to XMLElementSpans() in case '<' failed!");
					}

					QP=QE+1;
					break;
				case '=':
					//LogTestInfoW(__FUNCTIONW__, L"Equals");
					// We care about the value of an attrbiute

					if (FAILED(XMLAttributeValue(SegmentOpen, SegmentClose, Tag, Resource, cchResource)))
					{
						throw (L"XMLAttributeValue Failed");
					}


					fDone=TRUE;
					break;
				case '|':
					//LogTestInfoW(__FUNCTIONW__, L"Pipe");
					// We care about the contents of the tag
					//XMLAttributeValue(SegmentOpen, SegmentClose, Tag, Resource+3, cchResource-6);
					//LibraryLogInfoW(__FUNCTIONW__, L"Copying %d characters from %d to %d",SegmentClose-SegmentOpen, SegmentOpen, SegmentClose);
					if(wcsncpy_s(Resource,cchResource,SegmentOpen+1,(SegmentClose-SegmentOpen)-1) != 0)
					{
						throw (L"Error Copying resource.");
					}

					fDone=TRUE;
					break;
				default:
					throw (L"Error parsing XML Query");
				}
				//LibraryLogInfoW(__FUNCTIONW__, L"New Segment is %d to %d",SegmentOpen-InitSegmentOpen, SegmentClose-InitSegmentOpen);
				//LogTestInfoW(__FUNCTIONW__, L"New SegmentOpen:%x  SegmentClose:%x",SegmentOpen, SegmentClose);
			} while(fDone==FALSE);

			LogTestInfoW(__FUNCTIONW__, L"Resource appears to be [%s]",Resource);

			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}

	}
	__checkReturn HRESULT ResourceFromMUM(__in PCWSTR Component, __out_ecount(cchResource) PWSTR  Resource, __in unsigned int cchResource)
	{
		try
		{
			LOGLIBENTER;

			//wchar_t Filename[MAX_PATH];
			wchar_t pwszMUMFile[MAX_PATH];
			WIN32_FIND_DATAW X;
			wchar_t* wBuffer = NULL;
			//HANDLE Y;


			if (cchResource <=6)
			{
				LogTestInfoW(__FUNCTIONW__, L"cchResource under 7 characters is unusable, aborting.");
				LOGLIBRETURN_HRESULT(E_FAIL);
			}

			//precomputed reskeys begin and end with 3 hashes, L"###"
			//This is the beginning one.
			Resource[0] = '#';			Resource[1] = '#';			Resource[2] = '#';			Resource[3] = '\0';

			//GetWindowsServicingPackagesPath(pwszMUMFile);
			//GetOCfilename(Component, pwszMUMFile, MAX_PATH);
			if (FAILED(GetOCfilename(Component, pwszMUMFile, MAX_PATH)))
			{
				throw (L"GetOCfilename Failed");
			}
			///////////////////////
			// Turn the Wildcarded name into a specific name.
			///////////////////////

			if (FindFirstFileW(pwszMUMFile,&X) == INVALID_HANDLE_VALUE)
			{
				///////////////////////
				// Failure case
				///////////////////////

				LogTestInfoW(__FUNCTIONW__, L"Could not find MUM file.");
				wcsncat_s(Resource,cchResource,L"You need to check the return result from ResourceFromMUM(), because it just failed.",_TRUNCATE);
				wcsncat_s(Resource,cchResource,L"###",_TRUNCATE); //after Locale letter toend
				LOGLIBRETURN_HRESULT(E_FAIL);
			}

			if (FAILED(GetWindowsServicingPackagesPath(pwszMUMFile)))
			{
				throw (L"GetWindowsServicingPackagesPath Failed");
			}

			wcsncat_s(pwszMUMFile,MAX_PATH,X.cFileName, _TRUNCATE); //component
			LogTestInfoW(__FUNCTIONW__, L"MUM: %s (%d bytes)",pwszMUMFile,X.nFileSizeLow);

			//////////////////////
			// Read the specific file into ram
			///////////////////////

			if(SUCCEEDED(BufferFile(pwszMUMFile, wBuffer)))
			{
				//////////////////////
				//Extract the resource from the XML
				//////////////////////
				wchar_t* SegmentOpen = wBuffer;
				wchar_t* SegmentClose = wBuffer+wcslen(wBuffer);
				wchar_t Query[] = L";>assembly;>package;<update;=displayName;";

				if (FAILED(ResourceFromBufferedXML(Resource+3, cchResource-6,Query, SegmentOpen, SegmentClose )))
				{
					throw (L"Call to ResourceFromBufferedXML() failed!");
				}

				free(wBuffer);
			}
			else
			{
				///////////////////////
				// Failure case
				///////////////////////
				wcsncat_s(Resource,cchResource,L"You need to check the return result from ResourceFromMUM(), because it just failed.",_TRUNCATE);
				wcsncat_s(Resource,cchResource,L"###",_TRUNCATE); 
				LOGLIBRETURN_HRESULT(E_FAIL);
			}

			//precomputed reskeys begin and end with 3 hashes, L"###"
			//This is the ending one.
			wcsncat_s(Resource,cchResource,L"###",_TRUNCATE); 

			LOGLIBRETURN_HRESULT(NOERROR);	
		}

		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}

	}


	__checkReturn HRESULT ResourceFromMSC(__in PCWSTR Filename, __out_ecount(cchResource) PWSTR  Resource, __in unsigned int cchResource)
	{
		try
		{
			LOGLIBENTER;
			wchar_t pwszMSCFile[MAX_PATH];
			WIN32_FIND_DATAW X;
			wchar_t* wBuffer = NULL;
			//HANDLE Y;

			//precomputed reskeys begin and end with 3 hashes, L"###"
			//This is the beginning one.

			if (cchResource <=6)
			{
				LogTestInfoW(__FUNCTIONW__, L"cchResource under 7 characters is unusable, aborting.");
				return E_FAIL;
			}

			Resource[0] = '#'; Resource[1] = '#'; Resource[2] = '#'; Resource[3] = '\0';


			if (FAILED(GetWindowsSystem32LocalePath(pwszMSCFile)))
			{
				throw (L"WOWGlobalizeQueryId Failed");
			}


			wcsncat_s(pwszMSCFile,MAX_PATH,L"\\", _TRUNCATE);
			wcsncat_s(pwszMSCFile,MAX_PATH,Filename, _TRUNCATE);

			if (FindFirstFileW(pwszMSCFile,&X) == INVALID_HANDLE_VALUE)
			{
				LogTestInfoW(__FUNCTIONW__, L"Could not open MSC file.");
				wcsncat_s(Resource,cchResource,L"You need to check the return result from ResourceFromMSC(), because it just failed.",_TRUNCATE);
				wcsncat_s(Resource,cchResource,L"###",_TRUNCATE); //after Locale letter toend
				LOGLIBRETURN_HRESULT(E_FAIL);
			}

			LogTestInfoW(__FUNCTIONW__, L"MSC: %s (%d bytes)",pwszMSCFile,X.nFileSizeLow);

			if(SUCCEEDED(BufferFile(pwszMSCFile, wBuffer)))
			{
				wchar_t* SegmentOpen = wBuffer;
				wchar_t* SegmentClose = wBuffer+wcslen(wBuffer);
				wchar_t Query[] = L";>MMC_ConsoleFile;>StringTables;>StringTable;>Strings;>String:ID=\"1\";|;";
				//ResourceFromBufferedXML(Resource+3, cchResource-6,Query, SegmentOpen, SegmentClose );
				if (FAILED(ResourceFromBufferedXML(Resource+3, cchResource-6,Query, SegmentOpen, SegmentClose )))
				{
					throw (L"Call to ResourceFromBufferedXML() failed!");
				}

				free(wBuffer);
			}
			else
			{
				wcsncat_s(Resource,cchResource,L"You need to check the return result from ResourceFromMSC(), because it just failed.",_TRUNCATE);
				wcsncat_s(Resource,cchResource,L"###",_TRUNCATE); //after Locale letter toend
				LOGLIBRETURN_HRESULT(E_FAIL);
			}

			//precomputed reskeys begin and end with 3 hashes, L"###"
			//This is the ending one.
			wcsncat_s(Resource,cchResource,L"###",_TRUNCATE); //after Locale letter toend

			LOGLIBRETURN_HRESULT(NOERROR);	
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}


	__checkReturn HRESULT ResourceForDriveFromPath(__in PCWSTR pwszPath, __out_ecount(cchResource) PWSTR pwszResource, __in unsigned int cchResource)
	{
		try
		{
			LOGLIBENTER;
			// the pre-globalized resource for the displayed label of the drive a given path is on.
			//TODO: A >TON< of error checking.

			// These don't need to make it out.
			wchar_t pwszTemplate[1024];
			wchar_t* pwszRoot;
			wchar_t pwszRootLabel[MAX_PATH];

			if (cchResource <=6)
			{
				LogTestInfoW(__FUNCTIONW__, L"cchResource under 7 characters is unusable, aborting.");
				LOGLIBRETURN_HRESULT(E_FAIL);
			}

			//SHGetKnownFolderPath(FOLDERID_Public,0,NULL,&pwszPublicPath);
			pwszRoot = StrDupW(pwszPath); //// StrDupW() requires LocalFree() be called later
			//	LogTestInfoW(__FUNCTIONW__, L"'Public' path appears to be: %s", pwszPublicPath);
			PathStripToRootW(pwszRoot);
			//	LogTestInfoW(__FUNCTIONW__, L"Root of Public appears to be: %s", pwszRoot);
			GetVolumeInformationW(pwszRoot,  pwszRootLabel,  MAX_PATH,  NULL,  NULL,  NULL,  NULL,  NULL);
			//	LogTestInfoW(__FUNCTIONW__, L"Label of Root of Public appears to be: %s", pwszRootLabel);
			if (wcscmp(pwszRootLabel, L"") == 0) // drive is unlabeled
			{
				ExtractResourceString(resKeyDefaultLabel, pwszRootLabel, MAX_PATH);
			}
			//	LogTestInfoW(__FUNCTIONW__, L"Resource set to: %s", pwszRootLabel);
			if (FAILED(WOWGlobalizeQueryId(pwszTemplate, 1024, resKeyDriveTemplate)))
			{
				throw (L"WOWGlobalizeQueryId Failed");
			}
			//	LogTestInfoW(__FUNCTIONW__, L"Template: %s", pwszTemplate);

			// This could mess up if the first and second parameter swap positions in a localized build...
			// The wcsreplace function (currently in 'RPFWrapper.cpp') might do this better, or better yet something in shlwapi
			wchar_t* pwszFirstParam = wcsstr(pwszTemplate, L"%1!ls!");
			wchar_t* pwszSecondParam = wcsstr(pwszTemplate, L"%2!c!");

			wcscpy_s(pwszResource,cchResource,L"###");
			wcsncat_s(pwszResource,cchResource,pwszTemplate, pwszFirstParam - pwszTemplate); //beginning to drive label
			wcsncat_s(pwszResource,cchResource,pwszRootLabel,_TRUNCATE); //drive labe;
			wcsncat_s(pwszResource,cchResource,pwszFirstParam+6,pwszSecondParam-(pwszFirstParam+6)); //middle
			wcsncat_s(pwszResource,cchResource,pwszRoot,1); //drive letter, single character copied
			wcsncat_s(pwszResource,cchResource,pwszSecondParam+5,_TRUNCATE); //after drive letter toend
			wcsncat_s(pwszResource,cchResource,L"###",_TRUNCATE); //after drive letter toend
			LocalFree(pwszRoot); //// required from StrDupW()
			LogTestInfoW(__FUNCTIONW__, L"Drive Label: [%s]",pwszResource);
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}
}

