#pragma once
#include <memory>

#include "src/middleware/model/Customer.h"
#include "src/utils/usings.h"

// CCustomersDlg dialog

class CCustomersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomersDlg)
	
	CustomersList m_temporalCustomerList;

public:
	CCustomersDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCustomersDlg();
	void enableUI();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOMERS_DIALOG };
#endif

protected:
	void InitCustomerListCtrl();
	void setEnableUI(bool value);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void showAllCustomers(const CustomersList& customerList);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_CustomerListCtrl;
	void reloadCustomersList();
	void OnAddCustomerBtnClicked();
	afx_msg void OnDeleteCustomerBtnClicked();
	CustomersList&& consumeTemporalCustList() { return std::move(m_temporalCustomerList); };
	CButton addButton;
	CButton deleteButton;
};
