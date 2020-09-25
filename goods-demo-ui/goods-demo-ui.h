// goods-demo-ui.h : main header file for the goods-demo-ui DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CgoodsdemouiApp
// See goods-demo-ui.cpp for the implementation of this class
//

class CgoodsdemouiApp : public CWinApp
{
public:
	CgoodsdemouiApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
