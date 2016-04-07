//////////////////////////////////////////////////////////////
//                 
//  This file defines Internet Connection Sharring availability for Windows SKUs.
//  For use in testing SKU Differentiation of Microsoft Windows
//	
//  Copyright (C) Microsoft Corporation, 2008. For internal use only.
//
//////////////////////////////////////////////////////////////

// a-maklum: Created in early 2008
namespace InternetConnectionSharing_BVT
{

	// Returns true if Backup feature is available on the current running SKU/version of Vista, otherwise false
	static public HRESULT IsInternetConnectionSharingAvailable(HRESULT hr);

	// Returns true if Backup feature is available on the current running SKU/version of Vista, otherwise false
	static public HRESULT IsInternetConnectionSharingAvailable(HRESULT hr)
	{
		// Indentify the current SKU
		DWORD dwProductInfoType = 0;
		BOOL fInternetSharingExpected = FALSE;
		if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
		{
			switch (dwProductInfoType)
			{
				case PRODUCT_STARTER:
					// No backup functionality
					LogTestInfoW(__FUNCTIONW__, L"No internet connections sharing functionality expected on Starter.");
					fInternetSharingExpected = FALSE;
					break;
				case PRODUCT_HOME_BASIC:
				case PRODUCT_HOME_BASIC_N:
					// Internet connection sharing functionality (cpl exists) exists in Home Basic
					LogTestInfoW(__FUNCTIONW__, L"Internet connections sharing functionality expected on Home Basic.");
					fInternetSharingExpected = TRUE;
					break;
				case PRODUCT_HOME_PREMIUM:
				case PRODUCT_HOME_PREMIUM_N:
					// Internet connection sharing functionality (cpl) exists in Home Premium
					LogTestInfoW(__FUNCTIONW__, L"Internet connections sharing functionality expected on Home Premium.");
					fInternetSharingExpected = TRUE;
					break;
				case PRODUCT_BUSINESS:
				case PRODUCT_BUSINESS_N:
				case PRODUCT_ENTERPRISE:
				case PRODUCT_ENTERPRISE_N:
				case PRODUCT_ULTIMATE:
				case PRODUCT_ULTIMATE_N:
					// Full functionality of internet connection sharing for remaining Vista SKUs
					LogTestInfoW(__FUNCTIONW__, L"Internet connections sharing functionality expected on Business, Enterprise, and Ultimate.");
					fInternetSharingExpected = TRUE;
					break;
				default:
					LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU, cannot set expectations.");
					break;
			}
		}
		hr = ( TRUE == fInternetSharingExpected ) ? NOERROR : E_FAIL;
		return hr;
	}
}