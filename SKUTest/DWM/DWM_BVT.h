//////////////////////////////////////////////////////////////
//                 
//  This file defines helper function access for DWM_BVT
//	helper functions used in differentiating Display
//	Windows Management for Windows SKUs.
//  For use in testing SKU Differentiation of Microsoft Windows
//	
//  Copyright (C) Microsoft Corporation, 2008. For internal use only.
//
//////////////////////////////////////////////////////////////

// a-maklum: Created on Februrary 2008
namespace DWM_BVT
{
	// Helper function to close all opened and excessive windows that may or may not be left open.
	extern public HRESULT CloseExcessWindows();
}