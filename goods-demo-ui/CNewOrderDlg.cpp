// CNewOrderDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CNewOrderDlg.h"
#include "afxdialogex.h"
#include "src/middleware/Service.h"
#include "src/utils/helper_functions.h"
#include "src/ui/utils/mfc_utils.h"
#include <unordered_set>
#include <string>


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
	paymentTypeCombobox.AddString(CA2W("Cash"));
	paymentTypeCombobox.AddString(CA2W("Credit Card"));
	paymentTypeCombobox.AddString(CA2W("Check"));
	paymentTypeCombobox.AddString(CA2W("Other"));

	paymentTypeCombobox.SetCurSel(0);
}

void CNewOrderDlg::reloadItems()
{
	itemsCtrlList.DeleteAllItems();

	m_totalCost = 0;
	for (const auto& orderItem: m_orderParams->items)
	{
		double cost =m_products[orderItem.productSKU]->cost(orderItem.quantity);
		addRowToListCtrl(itemsCtrlList, "", {
			orderItem.productSKU,
			m_products[orderItem.productSKU]->description(),
			std::to_string(orderItem.quantity),
			std::to_string(cost)
		});
	}
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
	DDX_Control(pDX, IDC_EDIT4, customerLabel);

	initPaymentTypeCombobox();
	loadProductsInCombobox();
	initListCtrl(itemsCtrlList,
		{
			"Product SKU",
			"Product Name",
			"Quantity",
			"Cost"
		});
	std::string text{};
	CA2W labelText{ m_orderParams->customerEmail.c_str() };
	customerLabel.SetWindowTextW(labelText);
	
}

void CNewOrderDlg::OnOK()
{
	CDialogEx::OnOK();
}

BEGIN_MESSAGE_MAP(CNewOrderDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewOrderDlg::OnAddOrderItemBtnClicked)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CNewOrderDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNewOrderDlg::OnDeleteOrderItemClicked)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CNewOrderDlg::OnCbnSelchangeCombo2)
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
		
		addRowToListCtrl(itemsCtrlList,  "" , {
			m_products[productSKU]->sku(),
			m_products[productSKU]->description(),
			std::to_string(quantity),
			std::to_string(m_products[productSKU]->cost(quantity))
		});

		setValueToCEdit(totalEdit, m_totalCost);
		setValueToCEdit(quantityEdit, "");
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


void CNewOrderDlg::OnDeleteOrderItemClicked()
{
	std::vector<int> selectexIndexes = getAllSelectedRows(itemsCtrlList);
	int selectedIndexPos = 0, i = 0;
	
	m_orderParams->items.erase(std::remove_if(
		m_orderParams->items.begin(),
		m_orderParams->items.end(),
		[&]([[maybe_unused]]auto& _)
		{
			if (selectedIndexPos < selectexIndexes.size() && selectexIndexes[selectedIndexPos] == i++)
			{
				selectedIndexPos++;
				return true;
			}

			return false;
		}
	), m_orderParams->items.end());
	reloadItems();
}


void CNewOrderDlg::OnCbnSelchangeCombo2()
{
	CString text;
	paymentTypeCombobox.GetWindowTextW(text);
	std::string strPaymentTypeValue = CW2A(text);
	std::unordered_map<std::string, PaymentType> paymentTypeMap = {
		{"Cash", PaymentType::CASH},
		{"Credit Card", PaymentType::CREDIT_CARD},
		{"Check", PaymentType::CHECK},
		{"Other", PaymentType::OTHER}
	};

	m_orderParams->paymentType = paymentTypeMap[strPaymentTypeValue];
}
