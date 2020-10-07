#pragma once

#include "src/utils/usings.h"
#include "src/middleware/model/Product.h"
#include "src/middleware/model/Order.h"
#include "src/middleware/model/OrderItem.h"
#include <vector>

// CNewOrderDlg dialog

class CNewOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewOrderDlg);
	std::vector<ProductPtr> m_products;
	std::shared_ptr<Order> m_order;
	double m_totalCost;
	
	void loadProductsFromDB();
	void loadProductsInCombobox();
	

public:
	CNewOrderDlg(std::shared_ptr<Order> order , CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNewOrderDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_ORDER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnOK() override;

	DECLARE_MESSAGE_MAP()
public:
	CComboBox productsCombobox;
	CEdit quantityEdit;
	CEdit totalEdit;
	CListCtrl itemsCtrlList;
	CEdit skuEdit;
	afx_msg void OnAddOrderItemBtnClicked();
	CEdit weightEdit;
};
