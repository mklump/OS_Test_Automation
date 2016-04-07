//////////////////////////////////////////////////////////////
//                 
//  This file defines constants and functions, intended to
//  describe which feature is available on which editions of windows.
//  I cannot recommend using it in new tests as is,
//  a system that pulled data from a seperate file would be far superior.
//	
//  Copyright (C) Microsoft Corporation, 2008. For internal use only.
//
//////////////////////////////////////////////////////////////

// a-jomul: Created in late 2007, for use by Welcome Center test case.

#include <windows.h>            //Common Windows types
#include "Winsatcominterfacei.h" // Windows Experience Index
#include "unknwn.h" // For custom logger
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"

namespace SKUDiff
{
// SKU MASKS

#define SKU_NONE  0
#define SKU_STARTER  1
#define SKU_HOME_BASIC  2
#define SKU_HOME_PREMIUM  4
#define SKU_BUSINESS  8
#define SKU_ENTERPRISE  16
#define SKU_ULTIMATE  32
#define SKU_HOME_BASIC_N  64
#define SKU_HOME_PREMIUM_N  128
#define SKU_BUSINESS_N  256
#define SKU_ENTERPRISE_N  512
#define SKU_ULTIMATE_N  1024

// BASIC GROUPS OF SKUS

#define SKUS_NONE  (SKU_NONE)
#define SKUS_STANDARD  (SKU_STARTER | SKU_HOME_BASIC | SKU_HOME_PREMIUM | SKU_BUSINESS | SKU_ENTERPRISE | SKU_ULTIMATE)
#define SKUS_NATIONAL  (SKU_HOME_BASIC_N | SKU_HOME_PREMIUM_N | SKU_BUSINESS_N | SKU_ENTERPRISE_N | SKU_ULTIMATE_N)
#define SKUS_ALL  (SKUS_STANDARD | SKUS_NATIONAL)

#define SKUS_STARTER  (SKU_STARTER)
#define SKUS_HOME_BASIC  (SKU_HOME_BASIC | SKU_HOME_BASIC_N)
#define SKUS_HOME_PREMIUM  (SKU_HOME_PREMIUM | SKU_HOME_PREMIUM_N)
#define SKUS_BUSINESS  (SKU_BUSINESS | SKU_BUSINESS_N)
#define SKUS_ENTERPRISE  (SKU_ENTERPRISE | SKU_ENTERPRISE_N)
#define SKUS_ULTIMATE  (SKU_ULTIMATE | SKU_ULTIMATE_N)

#define SKUS_HOME  (SKU_STARTER | SKUS_HOME_BASIC | SKUS_HOME_PREMIUM)
#define SKUS_PRO  (SKUS_BUSINESS | SKUS_ENTERPRISE | SKUS_ULTIMATE)
#define SKUS_PREMIUM  (SKUS_HOME_PREMIUM | SKUS_ULTIMATE)
#define SKUS_MCE  (SKU_HOME_PREMIUM | SKU_ULTIMATE)

// SKU DIFFERENTIATED FEATURES (SDF_)
// the key area of this file, defining which SKU's have which features.


#define SDF_DWM  (SKUS_ALL & ~(SKU_STARTER | SKUS_HOME_BASIC))
#define SDF_PRESENTATIONMODE  (SKUS_ALL & ~(SKU_STARTER | SKUS_HOME_BASIC))
#define SDF_NETWORKPROJECTION  (SKUS_ALL & ~(SKU_STARTER | SKUS_HOME_BASIC))
#define SDF_SIDESHOW  (SKUS_ALL & ~(SKU_STARTER | SKUS_HOME_BASIC))
#define SDF_TABLETPC  (SKUS_ALL & ~(SKU_STARTER | SKUS_HOME_BASIC))

#define SDF_PARENTALCONTROLS  (SKUS_ALL & ~(SKUS_BUSINESS | SKUS_ENTERPRISE))

#define SDF_SERVICESFORUNIX  (SKUS_ENTERPRISE | SKUS_ULTIMATE)
#define SDF_MUI  (SKUS_ENTERPRISE | SKUS_ULTIMATE)
#define SDF_REMOTEAERO  (SKUS_ENTERPRISE | SKUS_ULTIMATE)

#define SDF_FASTUSERSWITCH  (SKUS_ALL & ~(SKU_STARTER))
#define SDF_DISKDIAGNOSE  (SKUS_ALL & ~(SKU_STARTER))

#define SDF_DOMAINJOIN  (SKUS_PRO)
#define SDF_GROUPPOLICY  (SKUS_PRO)
#define SDF_ENCRYPTEDFS  (SKUS_PRO)

#define SDF_BACKUP_BASIC  (SKUS_HOME_BASIC)
#define SDF_BACKUP_PREMIUM  (SKUS_HOME_PREMIUM)
#define SDF_BACKUP_PRO  (SKUS_PRO)

#define SDF_TIMEWARP  (SKUS_PRO)

#define SDF_ADVANCEDPHOTO  (SKUS_PREMIUM)
#define SDF_HDPUBLISH  (SKUS_PREMIUM)
#define SDF_MCX  (SKUS_PREMIUM)

#define SDF_MOVIEMAKER  (SKUS_STANDARD)
#define SDF_MEDIAPLAYER  (SKUS_STANDARD)

#define SDF_DVDAUTHORING  (SKUS_MCE)
#define SDF_MEDIACENTER  (SKUS_MCE)




//Welcome Center

#define SDF_WC_COMP_DETAILS			(SKUS_ALL)
#define SDF_WC_CONNECT_INTERNET		(SKUS_ALL)
#define SDF_WC_WHATS_NEW			(SKUS_ALL)
#define SDF_WC_BASICS				(SKUS_ALL)
#define SDF_WC_EASE_ACCESS			(SKUS_ALL)
#define SDF_WC_CONTROL_PANEL		(SKUS_ALL)
#define SDF_WC_PERSONALIZE			(SKUS_ALL)
#define SDF_WC_ADD_USERS			(SKUS_ALL & ~(SKUS_ENTERPRISE))
#define SDF_WC_REGISTER_WINDOWS		(SKUS_ALL & ~(SKUS_ENTERPRISE))
#define SDF_WC_UPGRADE				(SKUS_HOME_BASIC | SKUS_HOME_PREMIUM) // Business?
#define SDF_WC_ULTIMATE_EXTRAS		(SKUS_NONE)
#define SDF_WC_ADD_PRINTER			(SKUS_BUSINESS | SKUS_ENTERPRISE)
#define SDF_WC_MCE					(SKU_ULTIMATE | SKU_HOME_PREMIUM)
#define SDF_WC_EASY_TRANSFER		(SKUS_ALL & ~(SKUS_STARTER | SKUS_ENTERPRISE))
#define SDF_WC_BACKUP_RESTORE		(SKUS_ALL & ~(SKUS_STARTER | SKUS_ENTERPRISE))
#define SDF_WC_DEMOS				(SKUS_STANDARD)

//WAU
#define SDF_WINDOWS_ANYTIME_UPGRADE	(SKUS_HOME_BASIC | SKUS_HOME_PREMIUM | SKUS_BUSINESS)

// FUNCTIONS


// 
int GetCurrentSKUMask()
{
	LOGLIBENTER;
	DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		switch (dwProductInfoType)
		{
		case PRODUCT_STARTER:
			LOGLIBRETURN(SKU_STARTER);
		case PRODUCT_HOME_BASIC:
			LOGLIBRETURN(SKU_HOME_BASIC);
		case PRODUCT_HOME_PREMIUM:
			LOGLIBRETURN(SKU_HOME_PREMIUM);
		case PRODUCT_BUSINESS:
			LOGLIBRETURN(SKU_BUSINESS);
		case PRODUCT_ENTERPRISE:
			LOGLIBRETURN(SKU_ENTERPRISE);
		case PRODUCT_ULTIMATE:
			LOGLIBRETURN(SKU_ULTIMATE);
		
		case PRODUCT_HOME_BASIC_N:
			LOGLIBRETURN(SKU_HOME_BASIC_N);
		case PRODUCT_HOME_PREMIUM_N:
			LOGLIBRETURN(SKU_HOME_PREMIUM_N);
		case PRODUCT_BUSINESS_N:
			LOGLIBRETURN(SKU_BUSINESS_N);
		case PRODUCT_ENTERPRISE_N:
			LOGLIBRETURN(SKU_ENTERPRISE_N);
		case PRODUCT_ULTIMATE_N:
			LOGLIBRETURN(SKU_ULTIMATE_N);
		default:
			LogTestInfoW(__FUNCTIONW__, L"Unknown SKU.");
			LOGLIBRETURN(0);			
		}
	}
	LOGLIBEXIT;return 0;			
}

BOOL FeatureExpected(int sdf)
{
	LOGLIBENTER;
	if (GetCurrentSKUMask() & sdf)
	{
		LOGLIBRETURN_BOOL(TRUE);
	}
	LOGLIBRETURN_BOOL(FALSE);
	
}

//#define START_MENU_WELCOME_CENTER				STARTMENU_ITEM(resKeyWelcomeCenter) //temporary
//#define WC_EXPAND_TASKS				L"TODO" //temporary
}