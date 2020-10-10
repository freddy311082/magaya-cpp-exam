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
	std::shared_ptr<Customer> getCustomerObjFromListCtrl(int row);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl customerListCtrl;
	void reloadCustomersList();
	void OnAddCustomerBtnClicked();
	afx_msg void OnDeleteCustomerBtnClicked();
	CustomersList&& consumeTemporalCustList() { return std::move(m_temporalCustomerList); };
	CButton addButton;
	CButton deleteButton;
	afx_msg void OnHdnItemdblclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
