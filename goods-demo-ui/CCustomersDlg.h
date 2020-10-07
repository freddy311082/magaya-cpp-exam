#pragma once
#include <memory>

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
	void InitCustomerListCtrl();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void showAllCustomers();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_CustomerListCtrl;
	void refreshCustomersList();
	void OnAddCustomerBtnClicked();
	afx_msg void OnDeleteCustomerBtnClicked();
};
