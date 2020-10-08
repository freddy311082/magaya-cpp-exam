// COrdersDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "COrdersDlg.h"
#include "afxdialogex.h"
#include "CNewOrderDlg.h"
#include "src/middleware/model/Order.h"
#include "src/middleware/Service.h"
#include "src/utils/helper_functions.h"
#include "src/ui/utils/mfc_utils.h"
#include "src/middleware/Service.h"

// COrdersDlg dialog

IMPLEMENT_DYNAMIC(COrdersDlg, CDialogEx)

void COrdersDlg::loadCustomers()
{
	try
	{
		auto custList = Service::instance().allCustomers();
		listToVector(custList, m_customers);

		for (const auto& customer: m_customers)
		{
			CA2W email(customer->email().c_str());
			customersCombobox.AddString(email);
		}

		customersCombobox.SetCurSel(0);
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}

void COrdersDlg::reloadOrders()
{
	ordersListCtrl.DeleteAllItems();
	orderItemsListCtrl.DeleteAllItems();
	showSelectedCustomerOrders();
}

void COrdersDlg::showSelectedCustomerOrders()
{
	int selectedRow = ordersListCtrl.GetSelectionMark();

	if (selectedRow >= 0)
	{
		try
		{
			uint64_t number = 0;
			std::string customerEmail;
			OrderPtr order = Service::instance().getOrder(number, customerEmail);

			int i = 0;
			std::string numStr{ std::to_string(i) };
			orderItemsListCtrl.DeleteAllItems();
			for (const auto& item: order->items())
			{
				addRowToListCtrl(orderItemsListCtrl,
					numStr,
					{
						numStr,
						item->product()->sku(),
						item->product()->description(),
						std::to_string(item->quantity()),
						std::to_string(item->cost())
					}
				);
			}
		}
		catch (const std::exception& error)
		{
			CA2W msg(error.what());
			AfxMessageBox(msg, MB_OK | MB_ICONERROR);
		}
	}
}

COrdersDlg::COrdersDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ORDERS_DIALOG, pParent)
{
	loadCustomers();
}

COrdersDlg::~COrdersDlg()
{
}

void COrdersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, customersCombobox);
	DDX_Control(pDX, IDC_LIST1, ordersListCtrl);
	DDX_Control(pDX, IDC_LIST2, orderItemsListCtrl);

	initListCtrl(ordersListCtrl, {"Order Number", "Customer Email", "Date Time", "Payment Type", "Total"});
	initListCtrl(orderItemsListCtrl, {"Number", "Product SKU", "Product Name", "Quantity", "Cost"});
}


BEGIN_MESSAGE_MAP(COrdersDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &COrdersDlg::OnNewOrderBtnClicked)
	ON_CBN_SELCHANGE(IDC_COMBO1, &COrdersDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &COrdersDlg::OnReloadCustomersClicked)
END_MESSAGE_MAP()


// COrdersDlg message handlers


void COrdersDlg::OnNewOrderBtnClicked()
{
	try
	{
		if (customersCombobox.GetCurSel() == CB_ERR)
			throw std::invalid_argument("Please, select a customer.");

		std::shared_ptr<CreateOrderParams> orderParams = std::make_shared<CreateOrderParams>();
		auto dlg = CNewOrderDlg(orderParams);
		orderParams->customerEmail = m_customers[customersCombobox.GetCurSel()]->email();
		if (dlg.DoModal() == IDOK)
		{
			Service::instance().addOrder(*orderParams);
			reloadOrders();
		}
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}


void COrdersDlg::OnCbnSelchangeCombo1()
{
	try
	{
		int index = customersCombobox.GetCurSel();
		if (index == CB_ERR)
			throw std::invalid_argument("No customer selected.");

		showSelectedCustomerOrders();
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}


void COrdersDlg::OnReloadCustomersClicked()
{
	customersCombobox.Clear();
	loadCustomers();
}
