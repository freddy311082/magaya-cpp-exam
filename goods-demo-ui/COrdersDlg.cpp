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

	if (customersCombobox.GetCurSel() == CB_ERR)
		return;

	try
	{
		CString text;
		customersCombobox.GetWindowTextW(text);
		std::string email = CW2A(text);
		auto orders = Service::instance().allOrdersFromCustomer(email);
		

		for (const auto& order: orders)
		{
			char dateTimeStr[20];
			char* format = "%d:%d:%d %d:%d:%d";
			auto datetime = std::mktime(&order->datetime());
			std::strftime(dateTimeStr, 20, format, localtime(&datetime));

			addRowToListCtrl(ordersListCtrl,
				std::to_string(order->number()),
				{
					std::to_string(order->number()),
					order->customeEmail(),
					dateTimeStr,
					to_string(static_cast<PaymentType>(order->paymentType())),
					std::to_string(order->totalValue())					
				});
		}
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}

void COrdersDlg::showOrderItems(int index)
{
	int selectedRow = ordersListCtrl.GetSelectionMark();

	if (selectedRow >= 0)
	{
		try
		{
			CString numberValue = ordersListCtrl.GetItemText(index, 0);
			std::string numberStd = CW2A(numberValue);
			int64_t number = std::stoll(numberStd);
		
			CString emailCStr;
			customersCombobox.GetWindowTextW(emailCStr);
			std::string email{ CW2A(emailCStr) };
;
			OrderPtr order = Service::instance().getOrder(number, email);

			int i = 0;
			
			orderItemsListCtrl.DeleteAllItems();

			for (const auto& item: order->items())
			{
				std::string numStr{ std::to_string(++i) };
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

	loadCustomers();
	reloadOrders();
}


BEGIN_MESSAGE_MAP(COrdersDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &COrdersDlg::OnNewOrderBtnClicked)
	ON_CBN_SELCHANGE(IDC_COMBO1, &COrdersDlg::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &COrdersDlg::OnNMClickList1)
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
		orderParams->shippingAddress = m_customers[customersCombobox.GetCurSel()]->shippingAddress();
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

		reloadOrders();
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}




void COrdersDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (ordersListCtrl.GetSelectedCount() > 0)
	{
		
		POSITION pos = ordersListCtrl.GetFirstSelectedItemPosition();
		
		if (pos != nullptr)
		{
			int index = ordersListCtrl.GetNextSelectedItem(pos);
			showOrderItems(index);
		//
		// 	CString numberValue = ordersListCtrl.GetItemText(index, 0);
		// 	std::string numberStd = CW2A(numberValue);
		// 	int64_t number = std::stoll(numberStd);
		//
		// 	CString emailCStr;
		// 	customersCombobox.GetWindowTextW(emailCStr);
		// 	std::string email{ CW2A(emailCStr) };
		//
		// 	OrderPtr order = Service::instance().getOrder(number, email);
		//
		}
	}
		
	*pResult = 0;
}
