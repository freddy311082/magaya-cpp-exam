#pragma once


// CNewProductDlg dialog

class CNewProductDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewProductDlg)

public:
	CNewProductDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNewProductDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_PRODUCT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
