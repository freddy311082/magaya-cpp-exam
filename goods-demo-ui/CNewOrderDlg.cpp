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
		for (auto& product: Service::instance().allProducts())
		{
			m_products[product->sku()] = std::move(product);
		}
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
	skuCombobox.Clear();

	for (const auto& product: m_products)
	{
		CA2W value(product.second->sku().c_str());
		skuCombobox.AddString(value);
	}

	skuCombobox.SetCurSel(0);
	OnCbnSelchangeCombo1();
}

void CNewOrderDlg::initPaymentTypeCombobox()
{
	// CASH = 1,
	// CREDIT_CARD = 2,
	// CHECK = 3,
	// OTHER = 4
	paymentTypeCombobox.AddString(CA2W("Cash"));
	paymentTypeCombobox.AddString(CA2W("Credit Card"));
	paymentTypeCombobox.AddString(CA2W("Check"));
	paymentTypeCombobox.AddString(CA2W("Other"));

	paymentTypeCombobox.SetCurSel(0);
}


CNewOrderDlg::CNewOrderDlg(std::shared_ptr<CreateOrderParams> orderParams, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_ORDER_DIALOG, pParent), m_orderParams(orderParams), m_totalCost(0)
{
}

CNewOrderDlg::~CNewOrderDlg()
{
}

void CNewOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, quantityEdit);
	DDX_Control(pDX, IDC_COMBO1, skuCombobox);
	DDX_Control(pDX, IDC_EDIT2, totalEdit);
	DDX_Control(pDX, IDC_LIST1, itemsCtrlList);
	DDX_Control(pDX, IDC_EDIT3, productNameEdit);
	DDX_Control(pDX, IDC_COMBO2, paymentTypeCombobox);

	initPaymentTypeCombobox();
	loadProductsInCombobox();
	initListCtrl(itemsCtrlList, 
		{
			"Product SKU",
			"Product Name",
			"Quantity",
			"Cost"
		});
}

void CNewOrderDlg::OnOK()
{
	CDialogEx::OnOK();
}


BEGIN_MESSAGE_MAP(CNewOrderDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewOrderDlg::OnAddOrderItemBtnClicked)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CNewOrderDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CNewOrderDlg message handlers


void CNewOrderDlg::OnAddOrderItemBtnClicked()
{
	CString text;
	std::string stdText;

	try
	{
		if (skuCombobox.GetCurSel() == CB_ERR)
			throw std::invalid_argument("One product must be selected.");

		CString comboText;
		skuCombobox.GetWindowTextW(comboText);
		std::string productSKU = CW2A(comboText);
		double quantity = getDoubleFromCEdit(quantityEdit);
		m_totalCost += m_products[productSKU]->cost(quantity);

		m_orderParams->items.push_back({ quantity, m_products[productSKU]->sku() });
		
		std::string s;
		addRowToListCtrl(itemsCtrlList,  s , {
			m_products[productSKU]->sku(),
			m_products[productSKU]->description(),
			std::to_string(quantity),
			std::to_string(m_products[productSKU]->cost(quantity))
		});

		setValueToCEdit(totalEdit, m_totalCost);
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
	
	quantityEdit.GetWindowTextW(text);
}

void CNewOrderDlg::OnCbnSelchangeCombo1()
{
	CString text;
	skuCombobox.GetWindowTextW(text);
	std::string skuKey{ CW2A(text) };
	text = m_products[skuKey]->description().c_str();
	productNameEdit.SetWindowTextW(text);
}
