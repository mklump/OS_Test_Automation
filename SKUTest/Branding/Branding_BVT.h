//////////////////////////////////////////////////////////////
//                 
//  This file defines helper function access for Branding_BVT
//	helper functions used in differentiating Branding for
//	Windows SKUs.
//  For use in testing SKU Differentiation of Microsoft Windows
//	
//  Copyright (C) Microsoft Corporation, 2008. For internal use only.
//
//////////////////////////////////////////////////////////////

// a-maklum: Created on Februrary 2008
namespace Branding_BVT
{
	// Helper function that detects and renames all required cached assembly files
	// from .dll file extentions back to .dat binary file extentions.
	extern public HRESULT RenameCacheToDAT();

	// Help function checks to see if cache file needing renaming exists
	extern public HRESULT CheckPathToRenameExists(LPCSTR szPath);

	// Helper function that accepts a SKU name and gets an HBITMAP representing its branding logo
	// that is on the logon screen by loading the appropriate cached bitmap image.
	// The return value represents success of failure in the HBITMAP retrieval opperation.
	extern public HRESULT GetCachedLogonLogoBitmap(__out LPVOID logonLogoCachedBitMap);

	// Helper function that returns the actual logon screen bitmap image as an
	// HBITMAP __out parameter, and success or failure as an HRESULT
	extern public HRESULT ActualBrandingLoadBitmap(__out LPVOID logonLogoBitMap);

	// Helper function that accepts a cached libray and returns its bitmap image resource
	extern public HRESULT LoadCachedLibrary(__in LPWSTR pwszFileName, __out LPVOID logonLogoBitMap);
}