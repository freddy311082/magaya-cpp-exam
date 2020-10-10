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
	reloadCustomersList();
}

void CCustomersDlg::setEnableUI(bool value)
{
	addButton.EnableWindow(value);
	deleteButton.EnableWindow(value);
	customerListCtrl.EnableWindow(value);
	
}

void CCustomersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, customerListCtrl);
	DDX_Control(pDX, IDC_BUTTON1, addButton);
	DDX_Control(pDX, IDC_BUTTON2, deleteButton);

	initListCtrl(customerListCtrl, {
		"Name",
		"Email",
		"Phone",
		"Street and Number",
		"City",
		"State",
		"Country",
		"Zip Code",
		"Number of Orders"
		});

	setEnableUI(false);
}

void CCustomersDlg::showAllCustomers(const CustomersList& customerList)
{
	for (const auto& customer : customerList)
	{
		addRowToListCtrl(customerListCtrl,
			customer->email(), 
			{
				customer->name(),
				customer->email(),
				customer->phone(),
				customer->shippingAddress().streetAndNumber(),
				customer->shippingAddress().city(),
				customer->shippingAddress().state(),
				customer->shippingAddress().country(),
				std::to_string(customer->shippingAddress().zipCode()),
				std::to_string(customer->numberOfOrders())
			});
	}
}

std::shared_ptr<Customer> CCustomersDlg::getCustomerObjFromListCtrl(int row)
{
	ShippingAddress address(getTextFroListCtrl(customerListCtrl, row, 3),
		getTextFroListCtrl(customerListCtrl, row, 4),
		getTextFroListCtrl(customerListCtrl, row, 5),
		getTextFroListCtrl(customerListCtrl, row, 6),
		std::stoi(getTextFroListCtrl(customerListCtrl, row, 7)));

	return std::make_shared<Customer>(
		getTextFroListCtrl(customerListCtrl, row, 0),
		getTextFroListCtrl(customerListCtrl, row, 2),
		getTextFroListCtrl(customerListCtrl, row, 1),
		address,
		std::stoi(getTextFroListCtrl(customerListCtrl, row, 8))
	);
}


BEGIN_MESSAGE_MAP(CCustomersDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCustomersDlg::OnAddCustomerBtnClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CCustomersDlg::OnDeleteCustomerBtnClicked)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CCustomersDlg::OnHdnItemdblclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CCustomersDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CCustomersDlg message handlers


void CCustomersDlg::reloadCustomersList()
{
	try
	{
		customerListCtrl.DeleteAllItems();
		CustomersList customerList = Service::instance().allCustomers();
		showAllCustomers(customerList);

		m_temporalCustomerList = std::move(customerList);

		[[maybe_unused]] auto _ =GetParent()->GetParent()->SendMessage(WM_USER_CUSTOMER_CREATED,
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
		CNewCustomerDlg newCustDlg(customer, DialogMode::CREATE_NEW_MODE,  this);
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
	try
	{
		int index = getSelectedRow(customerListCtrl);
		if (index == -1)
			throw std::invalid_argument("No customer selected. Please, select one.");
		if (AfxMessageBox(_T("Ar you sure that you want to delete this customer?"), 
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			Service::instance().deleteCustomer(getTextFroListCtrl(customerListCtrl, index, 1));
			reloadCustomersList();
		}
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}


void CCustomersDlg::OnHdnItemdblclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	if (customerListCtrl.GetSelectedCount() > 0)
	{
		try
		{
			CString text;
			int index = getSelectedRow(customerListCtrl);
			auto customerUpdates = getCustomerObjFromListCtrl(index);
			std::string originalEmail{ customerUpdates->email() };
			
			if (CNewCustomerDlg(customerUpdates, DialogMode::UPDATE_MODE, this).DoModal() == IDOK)
			{
				Service::instance().updateCustomer(originalEmail, *customerUpdates);
				reloadCustomersList();
			}
		}
		catch (const std::exception& error)
		{
			CA2W msg(error.what());
			AfxMessageBox(msg, MB_OK | MB_ICONERROR);
		}

		
	}
	
	*pResult = 0;
}


void CCustomersDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (customerListCtrl.GetSelectedCount() > 0)
	{
		try
		{
			CString text;
			int index = getSelectedRow(customerListCtrl);
			auto customerUpdates = getCustomerObjFromListCtrl(index);
			std::string originalEmail{ customerUpdates->email() };

			if (CNewCustomerDlg(customerUpdates, DialogMode::UPDATE_MODE, this).DoModal() == IDOK)
			{
				Service::instance().updateCustomer(originalEmail, *customerUpdates);
				reloadCustomersList();
			}
		}
		catch (const std::exception& error)
		{
			CA2W msg(error.what());
			AfxMessageBox(msg, MB_OK | MB_ICONERROR);
		}
	}

	*pResult = 0;
}
