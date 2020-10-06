// CCustomersDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CCustomersDlg.h"
#include "afxdialogex.h"
#include "src/middleware/Service.h"
#include "src/middleware/model/Customer.h"
#include "CNewCustomerDlg.h"


// CCustomersDlg dialog

IMPLEMENT_DYNAMIC(CCustomersDlg, CDialogEx)

CCustomersDlg::CCustomersDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOMERS_DIALOG, pParent)
{
}

CCustomersDlg::~CCustomersDlg()
{
}

void CCustomersDlg::InitCustomerListCtrl()
{
	m_CustomerListCtrl.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	const DWORD extendedStyle = m_CustomerListCtrl.GetExtendedStyle();
	m_CustomerListCtrl.SetExtendedStyle(extendedStyle | LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT);


	CA2W headers[4] = { CA2W("Name"), CA2W("Email"), CA2W("Phone"), CA2W("Shipping Address")};

	for (int i = 0; i < 4; ++i)
	{
		m_CustomerListCtrl.InsertColumn(i, headers[i], LVCFMT_LEFT, 300);
	}
}

void CCustomersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_CustomerListCtrl);

	InitCustomerListCtrl();
	showAllCustomers();
}

void CCustomersDlg::showAllCustomers()
{
	auto customerList = Service::instance().allCustomers();

	int i = 0;
	for (const auto& customer : customerList)
	{
		CA2W emailItem(customer->email().c_str());
		m_CustomerListCtrl.InsertItem(i, emailItem);

		m_CustomerListCtrl.SetItemText(i, 0, CA2W(customer->name().c_str()));
		m_CustomerListCtrl.SetItemText(i, 1, CA2W(customer->email().c_str()));
		m_CustomerListCtrl.SetItemText(i, 2, CA2W(customer->phone().c_str()));
		m_CustomerListCtrl.SetItemText(i, 3, CA2W(customer->shippingAddress().toString().c_str()));

		i++;
	}
}


BEGIN_MESSAGE_MAP(CCustomersDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomersDlg::OnAddCustomerBtnClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CCustomersDlg::OnDeleteCustomerBtnClicked)
END_MESSAGE_MAP()


// CCustomersDlg message handlers


void CCustomersDlg::refreshCustomersList()
{
	m_CustomerListCtrl.DeleteAllItems();
	showAllCustomers();
}

void CCustomersDlg::OnAddCustomerBtnClicked()
{
	std::shared_ptr<Customer> customer = std::make_shared<Customer>();
	CNewCustomerDlg newCustDlg(customer, this);
	if (newCustDlg.DoModal() == IDOK)
	{
		Service::instance().addCustomer(*customer);
		refreshCustomersList();
	}
}


void CCustomersDlg::OnDeleteCustomerBtnClicked()
{
	// int selectedRow = ((CListCtrl*)GetDlgItem(IDC_LIST1))->GetSelectionMark();
	POSITION pos = m_CustomerListCtrl.GetFirstSelectedItemPosition();

	try
	{
		if (pos == NULL)
		{
			throw std::invalid_argument("No customer selected. Please, select one.");
		}
		
		int index = m_CustomerListCtrl.GetNextSelectedItem(pos);
		auto text = m_CustomerListCtrl.GetItemText(index, 1);
		std::string email = CW2A(text);
		Service::instance().deleteCustomer(email);
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
	
	refreshCustomersList();
}
