#pragma once

#include "src/utils/usings.h"
#include "src/middleware/model/Product.h"
#include "src/middleware/model/Order.h"
#include "src/middleware/model/OrderItem.h"
#include <unordered_map>
#include "src/middleware/model/CreateOrderParams.h"

// CNewOrderDlg dialog

class CNewOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewOrderDlg);
	std::unordered_map<std::string, ProductPtr> m_products;
	std::shared_ptr<CreateOrderParams> m_orderParams;
	double m_totalCost;
	
	void loadProductsFromDB();
	void loadProductsInCombobox();
	void initPaymentTypeCombobox();

public:
	CNewOrderDlg(std::shared_ptr<CreateOrderParams> order , CWnd* pParent = nullptr);   // standard constructor
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
	CComboBox skuCombobox;
	CEdit quantityEdit;
	CEdit totalEdit;
	CListCtrl itemsCtrlList;
	CEdit productNameEdit;
	afx_msg void OnAddOrderItemBtnClicked();
	CEdit weightEdit;
	CComboBox paymentTypeCombobox;
	afx_msg void OnCbnSelchangeCombo1();
};
