/***************************************************************
// Description: BVT - Logon screen branding verification entry
//					point for checking that the displayed Windows
//					Logo and SKU information is valid and correct.
// Created:     a-maklum
// Modified:	a-maklum (02/08/2008)
//				Created and implemented.
// Verify:      Pass test case if the detected SKU information
//				on the Logon screen correctly matches detected
				SKU information and cached SKU bitmap information.
****************************************************************/

#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"  
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;

namespace Branding_BVT
{
	static public LPWSTR processingSKU = NULL;

	// Helper function that accepts a cached libray and returns its bitmap image resource
	HRESULT LoadCachedLibrary(__in LPWSTR pwszFileName, __out LPVOID logonLogoBitMap)
	{
		HRSRC GDFResource;
		HGLOBAL hResource;
		LPCSTR multiByte[MAX_PATH],
			newName = NULL;
		size_t *numConverted[MAX_PATH];
		LPVOID pGDF;
		processingSKU = pwszFileName;
		if( 0 == wcscmp(pwszFileName, L"PRODUCT_ULTIMATE") )
		{
			pwszFileName = L".\\Logon_Logo_Cache\\ultimate\\basebrd.dll";
			newName = ".\\Logon_Logo_Cache\\ultimate\\basebrd.dll";
			LogTestInfoW(__FUNCTIONW__, L"Renaming ultimate\\basebrd.dat to %s.", pwszFileName);
			MoveFile(".\\Logon_Logo_Cache\\ultimate\\basebrd.dat", newName);
		}
		else if( 0 == wcscmp(pwszFileName, L"PRODUCT_BUSINESS") )
		{
			pwszFileName = L".\\Logon_Logo_Cache\\business\\basebrd.dll";
			newName = ".\\Logon_Logo_Cache\\business\\basebrd.dll";
			LogTestInfoW(__FUNCTIONW__, L"Renaming business\\basebrd.dat to %s.", pwszFileName);
			MoveFile(".\\Logon_Logo_Cache\\business\\basebrd.dat", newName);
		}
		else if( 0 == wcscmp(pwszFileName, L"PRODUCT_HOME_BASIC") )
		{
			pwszFileName = L".\\Logon_Logo_Cache\\homebasic\\basebrd.dll";
			newName = ".\\Logon_Logo_Cache\\homebasic\\basebrd.dll";
			LogTestInfoW(__FUNCTIONW__, L"Renaming homebasic\\basebrd.dat to %s.", pwszFileName);
			MoveFile(".\\Logon_Logo_Cache\\homebasic\\basebrd.dat", newName);
		}
		else if( 0 == wcscmp(pwszFileName, L"PRODUCT_HOME_PREMIUM") )
		{
			pwszFileName = L".\\Logon_Logo_Cache\\homepremium\\basebrd.dll";
			newName = ".\\Logon_Logo_Cache\\homepremium\\basebrd.dll";
			LogTestInfoW(__FUNCTIONW__, L"Renaming homepremium\\basebrd.dat to %s.", pwszFileName);
			MoveFile(".\\Logon_Logo_Cache\\homepremium\\basebrd.dat", newName);
		}
		else if( 0 == wcscmp(pwszFileName, L"PRODUCT_STARTER") )
		{
			pwszFileName = L".\\Logon_Logo_Cache\\starterfiles\\basebrd.dll";
			newName = ".\\Logon_Logo_Cache\\starterfiles\\basebrd.dll";
			LogTestInfoW(__FUNCTIONW__, L"Renaming starterfiles\\basebrd.dat to %s.", pwszFileName);
			MoveFile(".\\Logon_Logo_Cache\\starterfiles\\basebrd.dat", newName);
		}
		else if( 0 == wcscmp(pwszFileName, L"PRODUCT_ENTERPRISE") )
		{
			pwszFileName = L".\\Logon_Logo_Cache\\enterprise\\basebrd.dll";
			newName = ".\\Logon_Logo_Cache\\enterprise\\basebrd.dll";
			LogTestInfoW(__FUNCTIONW__, L"Renaming enterprise\\basebrd.dat to %s.", pwszFileName);
			MoveFile(".\\Logon_Logo_Cache\\enterprise\\basebrd.dat", newName);
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed because the specifice SKU is not supported by this test.");
			return E_FAIL;
		}
		LogTestInfoA(__FUNCTION__, "Calling character conversion function wcstombs_s((size_t*)numConverted, (char*)multiByte, (size_t)MAX_PATH, (const wchar_t*)expandedWinDir, _TRUNCATE)");
		wcstombs_s((size_t*)numConverted, (char*)multiByte, (size_t)MAX_PATH, (const wchar_t*)pwszFileName, _TRUNCATE);
		LogTestInfoA(__FUNCTION__, "Variable multibyte converted string is %s.", multiByte);
		LogTestInfoA(__FUNCTION__, "Number of converted characters are %u.", numConverted[0]);
		LogTestInfoW(__FUNCTIONW__, L"Calling LoadLibraryEx((LPCSTR)multiByte, NULL, LOAD_LIBRARY_AS_DATAFILE)");
		HMODULE CachedBaseBrandingLibrary = LoadLibraryEx((LPCSTR)multiByte, NULL, LOAD_LIBRARY_AS_DATAFILE);
		LogTestInfoW(__FUNCTIONW__, L"End calling LoadLibraryEx((LPCSTR)multiByte, NULL, LOAD_LIBRARY_AS_DATAFILE)");
		if( NULL == CachedBaseBrandingLibrary )
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to load library cache file <Mash_II>%s", pwszFileName);
			return E_FAIL;
		}
		GDFResource = FindResource(CachedBaseBrandingLibrary, (LPCSTR)101, RT_BITMAP);
		if (GDFResource == NULL)
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to find the required bitmap image resource in library CachedBaseBrandingLibrary.");
			return E_FAIL;
		}
		hResource = LoadResource(CachedBaseBrandingLibrary, GDFResource);
		if (hResource == NULL)
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to get the required hResource reference.");
			return E_FAIL;
		}
		pGDF = LockResource(hResource);
		if (pGDF == NULL)
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to get the required pGDF reference.");
			return E_FAIL;
		}
		logonLogoBitMap = pGDF;

		// Cleaning up local resources used by this helper function
		//delete GDFResource;
		//delete hResource;
		//delete multiByte;
		//delete numConverted;
		//delete pGDF;

		return NOERROR;
	} // End static public HBITMAP GetLogonLogoBitmap(LPWSTR lpszSkuName)
	
	// Helper function that returns the actual logon screen bitmap image as an
	// HBITMAP __out parameter, and success or failure as an HRESULT
	HRESULT ActualBrandingLoadBitmap(__out LPVOID logonLogoBitMap)
	{
		HRSRC GDFResource;
		HGLOBAL hResource;
		LPCSTR multiByte[MAX_PATH];
		size_t *numConverted[MAX_PATH];
		LPVOID pGDF;
		LPWSTR pwszFileName = L"\\Branding\\Basebrd\\basebrd.dll",
			expandedWinDir[MAX_PATH];
		LogTestInfoW(__FUNCTIONW__, L"Calling ExpandEnvironmentStringsW(L\"windir\", expandedWinDir, MAX_PATH)");
		DWORD numLetters = ExpandEnvironmentStringsW(L"%windir%", (LPWSTR)expandedWinDir, MAX_PATH);
		LogTestInfoW(__FUNCTIONW__, L"End calling ExpandEnvironmentStringsW(L\"windir\", expandedWinDir, MAX_PATH)");
		if( 0 == (int)numLetters )
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to expand environment variable %%windir%%");
			return E_FAIL;
		}
		wcscat_s((wchar_t*)expandedWinDir, MAX_PATH, pwszFileName);
		LogTestInfoW(__FUNCTIONW__, L"The expanded path is %s.", expandedWinDir);
		
		LogTestInfoA(__FUNCTION__, "Calling character conversion function wcstombs_s((size_t*)numConverted, (char*)multiByte, (size_t)MAX_PATH, (const wchar_t*)expandedWinDir, _TRUNCATE)");
		wcstombs_s((size_t*)numConverted, (char*)multiByte, (size_t)MAX_PATH, (const wchar_t*)expandedWinDir, _TRUNCATE);
		LogTestInfoA(__FUNCTION__, "Variable multibyte converted string is %s.", multiByte);
		LogTestInfoA(__FUNCTION__, "Number of converted characters are %u.", numConverted[0]);
		LogTestInfoW(__FUNCTIONW__, L"Calling LoadLibraryEx((LPCSTR)multiByte, NULL, LOAD_LIBRARY_AS_DATAFILE)");
		HMODULE ActualBaseBrandingLibrary = LoadLibraryEx((LPCSTR)multiByte, NULL, LOAD_LIBRARY_AS_DATAFILE);
		LogTestInfoW(__FUNCTIONW__, L"End calling LoadLibraryEx((LPCSTR)multiByte, NULL, LOAD_LIBRARY_AS_DATAFILE)");
		if( NULL == ActualBaseBrandingLibrary )
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to load library actual file %s", expandedWinDir);
			return E_FAIL;
		}
		GDFResource = FindResource(ActualBaseBrandingLibrary, (LPCSTR)101, RT_BITMAP);
		if (GDFResource == NULL)
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to find the required bitmap image resource in library ActualBaseBrandingLibrary.");
			return E_FAIL;
		}
		hResource = LoadResource(ActualBaseBrandingLibrary, GDFResource);
		if (hResource == NULL)
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to get the required hResource reference.");
			return E_FAIL;
		}
		pGDF = LockResource(hResource);
		if (pGDF == NULL)
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to get the required pGDF reference.");
			return E_FAIL;
		}
		logonLogoBitMap = pGDF;

		// Cleaning up local resources used by this helper function
		//delete GDFResource;
		//delete hResource;
		//delete multiByte;
		//delete numConverted;
		//delete pGDF;
		//delete pwszFileName;
		//delete expandedWinDir;

		return NOERROR;
	} // HRESULT ActualBrandingLoadBitmap(__out HBITMAP logonLogoBitMap)

	// Helper function that accepts a SKU name and gets an HBITMAP representing its branding logo
	// that is on the logon screen by loading the appropriate cached bitmap image.
	// The return value represents success of failure in the HBITMAP retrieval opperation.
	HRESULT GetCachedLogonLogoBitmap(__out LPVOID logonLogoCachedBitMap)
	{
		DWORD dwProductInfoType = 0;
		if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
		{
			switch (dwProductInfoType)
			{
			case PRODUCT_ULTIMATE:
				LogTestInfoW(__FUNCTIONW__, L"Windows Vista ULTIMATE branding bitmap image expected on Logon Screen.");
				if( !SUCCEEDED(LoadCachedLibrary(L"PRODUCT_ULTIMATE", logonLogoCachedBitMap)) )
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to load cached bitmap resource for PRODUCT_ULTIMATE.");
					return E_FAIL;
				}
				break;
			case PRODUCT_BUSINESS:
				LogTestInfoW(__FUNCTIONW__, L"Windows Vista BUSINESS branding bitmap image expected on Logon Screen.");
				if( !SUCCEEDED(LoadCachedLibrary(L"PRODUCT_BUSINESS", logonLogoCachedBitMap)) )
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to load cached bitmap resource for PRODUCT_BUSINESS.");
					return E_FAIL;
				}
				break;
			case PRODUCT_HOME_BASIC:
				LogTestInfoW(__FUNCTIONW__, L"Windows Vista HOME BASIC branding bitmap image expected on Logon Screen.");
				if( !SUCCEEDED(LoadCachedLibrary(L"PRODUCT_HOME_BASIC", logonLogoCachedBitMap)) )
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to load cached bitmap resource for PRODUCT_HOME_BASIC.");
					return E_FAIL;
				}
				break;
			case PRODUCT_HOME_PREMIUM:
				LogTestInfoW(__FUNCTIONW__, L"Windows Vista HOME PREMIUM branding bitmap image expected on Logon Screen.");
				if( !SUCCEEDED(LoadCachedLibrary(L"PRODUCT_HOME_PREMIUM", logonLogoCachedBitMap)) )
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to load cached bitmap resource for PRODUCT_HOME_PREMIUM.");
					return E_FAIL;
				}
				break;
			case PRODUCT_STARTER:
				LogTestInfoW(__FUNCTIONW__, L"Windows Vista STARTER branding bitmap image expected on Logon Screen.");
				if( !SUCCEEDED(LoadCachedLibrary(L"PRODUCT_STARTER", logonLogoCachedBitMap)) )
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to load cached bitmap resource for PRODUCT_STARTER.");
					return E_FAIL;
				}
				break;
			case PRODUCT_ENTERPRISE:
				LogTestInfoW(__FUNCTIONW__, L"Windows Vista ENTERPRISE branding bitmap image expected on Logon Screen.");
				if( !SUCCEEDED(LoadCachedLibrary(L"PRODUCT_ENTERPRISE", logonLogoCachedBitMap)) )
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to load cached bitmap resource for PRODUCT_ENTERPRISE.");\
					return E_FAIL;
				}
				break;
			default:
				LogTestInfoW(__FUNCTIONW__, L"Wrong branding or could not determine the SKU.");
				return E_FAIL;
			} // End switch (dwProductInfoType)
		} // End if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))

		// Cleaning up local resources used by this helper function
		//delete CachedBitmap;
		//delete dwProductInfoType;

		return NOERROR;
	} // End static public HBITMAP GetLogonLogoBitmap(LPWSTR lpszSkuName)

	// Help function checks to see if cache file needing renaming exists
	HRESULT CheckPathExists(LPCSTR szPath)
	{
		HRESULT hr = E_FAIL;
		// check if file exists
        WIN32_FIND_DATA fd;
        HANDLE hFind = FindFirstFile(szPath, &fd);
        if (hFind == INVALID_HANDLE_VALUE)
        {
			LogTestInfoA(__FUNCTION__, "Failed to find the path %s.", szPath);
			hr = E_FAIL;
        }
        else
        {
           LogTestInfoA(__FUNCTION__, "The path %s exists.", szPath);
           hr = NOERROR;
        }
		return hr;
	}

	// Helper function that detects and renames all required cached assembly files
	// from .dll file extentions back to .dat binary file extentions.
	HRESULT RenameCacheToDAT()
	{
		LPCSTR newName = NULL;
		DWORD dwProductInfoType = 0;
		if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
		{
			switch (dwProductInfoType)
			{
			case PRODUCT_ULTIMATE:
				newName = ".\\Logon_Logo_Cache\\ultimate\\basebrd.dat";
				if( !SUCCEEDED(CheckPathExists(".\\Logon_Logo_Cache\\ultimate\\basebrd.dll")) )
					return E_FAIL;
				LogTestInfoA(__FUNCTION__, "Renaming \\Logon_Logo_Cache\\ultimate\\basebrd.dll to %s.", newName);
				MoveFile(".\\Logon_Logo_Cache\\ultimate\\basebrd.dll", newName);
				break;
			case PRODUCT_BUSINESS:
				newName = ".\\Logon_Logo_Cache\\business\\basebrd.dat";
				if( !SUCCEEDED(CheckPathExists(".\\Logon_Logo_Cache\\business\\basebrd.dll")) )
					return E_FAIL;
				LogTestInfoA(__FUNCTION__, "Renaming \\Logon_Logo_Cache\\business\\basebrd.dll to %s.", newName);
				MoveFile(".\\Logon_Logo_Cache\\business\\basebrd.dll", newName);
				break;
			case PRODUCT_HOME_BASIC:
				newName = ".\\Logon_Logo_Cache\\homebasic\\basebrd.dat";
				if( !SUCCEEDED(CheckPathExists(".\\Logon_Logo_Cache\\homebasic\\basebrd.dll")) )
					return E_FAIL;
				LogTestInfoA(__FUNCTION__, "Renaming \\Logon_Logo_Cache\\homebasic\\basebrd.dll to %s.", newName);
				MoveFile(".\\Logon_Logo_Cache\\homebasic\\basebrd.dll", newName);
				break;
			case PRODUCT_HOME_PREMIUM:
				newName = ".\\Logon_Logo_Cache\\homepremium\\basebrd.dat";
				if( !SUCCEEDED(CheckPathExists(".\\Logon_Logo_Cache\\homepremium\\basebrd.dll")) )
					return E_FAIL;
				LogTestInfoA(__FUNCTION__, "Renaming \\Logon_Logo_Cache\\homepremium\\basebrd.dll to %s.", newName);
				MoveFile(".\\Logon_Logo_Cache\\homepremium\\basebrd.dll", newName);
				break;
			case PRODUCT_STARTER:
				newName = ".\\Logon_Logo_Cache\\starterfiles\\basebrd.dat";
				if( !SUCCEEDED(CheckPathExists(".\\Logon_Logo_Cache\\starterfiles\\basebrd.dll")) )
					return E_FAIL;
				LogTestInfoA(__FUNCTION__, "Renaming \\Logon_Logo_Cache\\starterfiles\\basebrd.dll to %s.", newName);
				MoveFile(".\\Logon_Logo_Cache\\starterfiles\\basebrd.dll", newName);
				break;
			case PRODUCT_ENTERPRISE:
				newName = ".\\Logon_Logo_Cache\\enterprise\\basebrd.dat";
				if( !SUCCEEDED(CheckPathExists(".\\Logon_Logo_Cache\\enterprise\\basebrd.dll")) )
					return E_FAIL;
				LogTestInfoA(__FUNCTION__, "Renaming \\Logon_Logo_Cache\\enterprise\\basebrd.dll to %s.", newName);
				MoveFile(".\\Logon_Logo_Cache\\enterprise\\basebrd.dll", newName);
				break;
			default:
				LogTestInfoW(__FUNCTIONW__, L"Failed because the specifice SKU is not supported by this test.");
				return E_FAIL;
			}
		}
		return CheckPathExists(newName);
	}

	//    
	//    VerifyLogonBranding_BVTEntryPoint 
	//  
	STDAPI VerifyLogonBranding_BVTEntryPoint(LPVOID pvReserved)
	{
		BOOL bfinalResult = FALSE;
		HRESULT hr = E_FAIL;
		LPVOID logonLogoCachedBitMap = NULL,
			logonLogoActualBitMap = NULL;
		LPWSTR pwszResultInfo = L"";
		LogTestBeginW(__FUNCTIONW__, L"Verifying Logon Screen Branding UI is differentiated correctly.");    
				
		// Used to pass flow of control to after the end of the while loop if a failue occurs using break statements.
		// This also allows the loop to be restarted with a continue statement if required.
		while( TRUE )
		{
			// Get the Cached Branding Logo for the Logon Screen bitmap
			LogTestInfoW(__FUNCTIONW__, L"Retrieving the actual logon logo bitmap image from %%windir%%\\Branding\\Basebrd\\basebrd.dll");
			hr = ActualBrandingLoadBitmap( &logonLogoActualBitMap );
			if( !SUCCEEDED(hr) )
			{
				pwszResultInfo = L"Failed to correctly load actual logon logo bitmap image.";
				break;
			}
			// Get the Actual Branding Logo for the Logon Screen bitmap
			LogTestInfoW(__FUNCTIONW__, L"Retrieving the cached logon logo bitmap image from .\\Logon_Logo_Cache\\*.");
			hr = GetCachedLogonLogoBitmap( &logonLogoCachedBitMap );
			if( !SUCCEEDED(hr) )
			{
				pwszResultInfo = L"Failed to correctly load cached logon logo bitmap image.";
				break;
			}
			// Compare the ACTUAL logon logo image to the CACHED logon logo image.
			LogTestInfoW(__FUNCTIONW__, L"Comparing the ACTUAL logon logo image to the CACHED logon logo image.");
			LONG actualSize = sizeof(logonLogoActualBitMap),
				cachedSize = sizeof(logonLogoCachedBitMap);
			// Please note that the required data structure type for further comparison is BITMAP.
			// The type-cast operator () will not appropriately cast type LPVOID to BITMAP, comparison
			// stops here for now.
			if( actualSize == cachedSize )
			{
				hr = NOERROR;
				LogTestInfoW(__FUNCTIONW__, L"The ACTUAL logon logo bitmap is confirmed as identical to the CACHED logon logo image.");
			}
			else
			{
				hr = E_FAIL;
				pwszResultInfo = L"Failed on comparing the ACTUAL logon logo bitmap as identical to the CACHED logon logo image.";
				break;
			}
			//// SendKey - "window" named "Desktop" in window ""
			//hr = WOWFromPartialQueryId(L";AccessibleName = '{0}' && ClassName => '#32769';Name = '{0}' && Role = 'window'", resKeyDesktop);
			//if( SUCCEEDED(hr) )
			//	SendKeys(L"^%{DELETE}");
			//else
			//{
			//	pwszResultInfo = L"Sending Ctrl+Alt+Delete failed.";
			//	LogTestInfoW(__FUNCTIONW__, L"%s", pwszResultInfo);
			//	break;
			//}
			pwszResultInfo = L"Test succeeded with no errors.";
			break; // No matter what, when the execution stack pointer reaches this position, break out! of the while() loop.
		} // End while( TRUE )

		bfinalResult = SUCCEEDED(hr);
		LogTestInfoW(__FUNCTIONW__,
			L"BVT test function VerifyLogonBranding_BVTEntryPoint() has exited with error status: %s",
			bfinalResult ? L"0" : L"-1" );
		LogTestResultW(bfinalResult, __FUNCTIONW__, L"%s", pwszResultInfo);

		// Cleaning up local resources used by this helper function
		//delete bfinalResult;
		//delete hr;
		//delete logonLogoCachedBitMap;
		//delete logonLogoActualBitMap;
		//delete pwszResultInfo;

		return hr;
	} // STDAPI VerifyLogonBranding_BVTEntryPoint(LPVOID pvReserved)
} // End namespace Branding_BVT