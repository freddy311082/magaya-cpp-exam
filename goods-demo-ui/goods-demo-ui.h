
// goods-demo-ui.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CgoodsdemouiApp:
// See goods-demo-ui.cpp for the implementation of this class
//

class CgoodsdemouiApp : public CWinApp
{
public:
	CgoodsdemouiApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMenuExitClicked();
};

extern CgoodsdemouiApp theApp;
