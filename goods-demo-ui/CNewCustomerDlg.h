#pragma once


// CNewCustomerDlg dialog

class CNewCustomerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewCustomerDlg)

public:
	CNewCustomerDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNewCustomerDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_CUSTOMER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
