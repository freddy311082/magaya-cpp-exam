#pragma once

#include <vector>
#include <string>
#include "src/utils/usings.h"
#include "src/middleware/model/Customer.h"

// COrdersDlg dialog

class COrdersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COrdersDlg)

	std::vector<CustomerPtr> m_customers;
	void reloadOrders();
	void showOrderItems(int index);
	
public:
	COrdersDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~COrdersDlg();
	void loadCustomers(CustomersList& customers);
	void setEnableUI(bool value);
	void enableUI();
	void enableCreateOrder();
	void disableCreateOrder();
	void loadOrdersIntoCtrlList(const OrdersList& orders);

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ORDERS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNewOrderBtnClicked();
	CComboBox customersCombobox;
	CListCtrl ordersListCtrl;
	CListCtrl orderItemsListCtrl;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	CButton newOrderButton;
	CButton deleteOrderButton;
	afx_msg void OnDeleteOrderBtnClicked();
	afx_msg void OnBnClickedCheck1();
	CButton showAllOrdersCheckBox;
};
