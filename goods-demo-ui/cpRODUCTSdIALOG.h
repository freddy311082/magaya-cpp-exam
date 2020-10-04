#pragma once


// cpRODUCTSdIALOG dialog

class cpRODUCTSdIALOG : public CDialogEx
{
	DECLARE_DYNAMIC(cpRODUCTSdIALOG)

public:
	cpRODUCTSdIALOG(CWnd* pParent = nullptr);   // standard constructor
	virtual ~cpRODUCTSdIALOG();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRODUCTS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
