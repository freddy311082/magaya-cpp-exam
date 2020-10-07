// CNewOrderDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CNewOrderDlg.h"
#include "afxdialogex.h"
#include "src/middleware/Service.h"
#include "src/utils/helper_functions.h"
#include "src/ui/utils/mfc_utils.h"




// CNewOrderDlg dialog

IMPLEMENT_DYNAMIC(CNewOrderDlg, CDialogEx)

void CNewOrderDlg::loadProductsFromDB()
{
	try
	{
		m_products.clear();
		listToVector(Service::instance().allProducts(), m_products);
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}

void CNewOrderDlg::loadProductsInCombobox()
{
	loadProductsFromDB();
	productsCombobox.Clear();
	
	for (int i = 0; i < m_products.size(); ++i)
	{
		CA2W value(m_products[i]->description().c_str());
		productsCombobox.AddString(value);
	}
}


CNewOrderDlg::CNewOrderDlg(std::shared_ptr<Order> order, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_ORDER_DIALOG, pParent), m_order(order), m_totalCost(0)
{
}

CNewOrderDlg::~CNewOrderDlg()
{
}

void CNewOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, quantityEdit);
	DDX_Control(pDX, IDC_COMBO1, productsCombobox);
	DDX_Control(pDX, IDC_EDIT2, totalEdit);
	DDX_Control(pDX, IDC_LIST1, itemsCtrlList);
	DDX_Control(pDX, IDC_EDIT3, skuEdit);

	loadProductsInCombobox();
	initListCtrl(itemsCtrlList, { "Product SKU", "Product Name", "Quantity", "Cost" });
}

void CNewOrderDlg::OnOK()
{
	CDialogEx::OnOK();
}


BEGIN_MESSAGE_MAP(CNewOrderDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewOrderDlg::OnAddOrderItemBtnClicked)
END_MESSAGE_MAP()


// CNewOrderDlg message handlers


void CNewOrderDlg::OnAddOrderItemBtnClicked()
{
	CString text;
	std::string stdText;

	try
	{
		if (productsCombobox.GetCurSel() == CB_ERR)
			throw std::invalid_argument("One product must be selected.");

		int prodIndex = productsCombobox.GetCurSel();
		double quantity = getDoubleFromCEdit(quantityEdit);

		m_order->addItem(
			std::make_unique<OrderItem>(
				quantity, 
				std::make_unique<Product>(*m_products[prodIndex]))
		);

		// m_totalCost += quantity;
		// CA2W totalValue(std::to_string(m_totalCost).c_str());
		// totalEdit.SetWindowTextW(totalValue);

		std::string s;
		addRowToListCtrl(itemsCtrlList,  s , {
			m_products[prodIndex]->sku(),
			m_products[prodIndex]->description(),
			std::to_string(quantity),
			std::to_string(m_products[prodIndex]->cost(quantity))
		});

		setValueToCEdit(totalEdit, m_order->totalValue());
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
	
		

	

	quantityEdit.GetWindowTextW(text);
	
}
