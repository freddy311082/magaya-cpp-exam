// CCustomersDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CCustomersDlg.h"
#include "afxdialogex.h"
#include "src/middleware/Service.h"
#include "src/middleware/model/Customer.h"
#include "CNewCustomerDlg.h"
#include "src/ui/utils/mfc_utils.h"


// CCustomersDlg dialog

IMPLEMENT_DYNAMIC(CCustomersDlg, CDialogEx)

CCustomersDlg::CCustomersDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOMERS_DIALOG, pParent)
{
}

CCustomersDlg::~CCustomersDlg()
{
}

void CCustomersDlg::enableUI()
{
	InitCustomerListCtrl();
	setEnableUI(true);
}

void CCustomersDlg::InitCustomerListCtrl()
{
	initListCtrl(m_CustomerListCtrl,{ "Name", "Email", "Phone", "Shipping Address" });
	reloadCustomersList();
}

void CCustomersDlg::setEnableUI(bool value)
{
	addButton.EnableWindow(value);
	deleteButton.EnableWindow(value);
}

void CCustomersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_CustomerListCtrl);
	DDX_Control(pDX, IDC_BUTTON1, addButton);
	DDX_Control(pDX, IDC_BUTTON2, deleteButton);

	setEnableUI(false);
}

void CCustomersDlg::showAllCustomers(const CustomersList& customerList)
{
	for (const auto& customer : customerList)
	{
		addRowToListCtrl(m_CustomerListCtrl,
			customer->email(), 
			{customer->name(), customer->email(), customer->phone(), customer->shippingAddress().toString()});
	}
}


BEGIN_MESSAGE_MAP(CCustomersDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomersDlg::OnAddCustomerBtnClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CCustomersDlg::OnDeleteCustomerBtnClicked)
END_MESSAGE_MAP()


// CCustomersDlg message handlers


void CCustomersDlg::reloadCustomersList()
{
	try
	{
		m_CustomerListCtrl.DeleteAllItems();
		CustomersList customerList = Service::instance().allCustomers();
		showAllCustomers(customerList);

		m_temporalCustomerList = std::move(customerList);

		GetParent()->GetParent()->SendMessage(WM_USER_CUSTOMER_CREATE,
			NULL,
			NULL
		);
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}

void CCustomersDlg::OnAddCustomerBtnClicked()
{
	try
	{
		std::shared_ptr<Customer> customer = std::make_shared<Customer>();
		CNewCustomerDlg newCustDlg(customer, this);
		if (newCustDlg.DoModal() == IDOK)
		{
			Service::instance().addCustomer(*customer);
			reloadCustomersList();
		}
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}


void CCustomersDlg::OnDeleteCustomerBtnClicked()
{
	// int selectedRow = ((CListCtrl*)GetDlgItem(IDC_LIST1))->GetSelectionMark();
	POSITION pos = m_CustomerListCtrl.GetFirstSelectedItemPosition();

	try
	{
		int index = getSelectedRow(m_CustomerListCtrl);
		if (index == -1)
			throw std::invalid_argument("No customer selected. Please, select one.");
		
		auto text = m_CustomerListCtrl.GetItemText(index, 1);
		std::string email = CW2A(text);
		Service::instance().deleteCustomer(email);
		reloadCustomersList();
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}
