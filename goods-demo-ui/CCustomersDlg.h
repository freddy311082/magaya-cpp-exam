#pragma once


// CCustomersDlg dialog

class CCustomersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomersDlg)

public:
	CCustomersDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCustomersDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOMERS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
