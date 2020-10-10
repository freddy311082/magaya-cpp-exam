// CNewCustomerDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CNewCustomerDlg.h"
#include "afxdialogex.h"
#include "src/middleware/Service.h"
#include "src/middleware/model/Customer.h"
#include "src/ui/utils/mfc_utils.h"
#include <string>
#include <exception>
#include <sstream>



// CNewCustomerDlg dialog

IMPLEMENT_DYNAMIC(CNewCustomerDlg, CDialogEx)

void CNewCustomerDlg::validateBy(ValidateType type)
{
	CEdit* edit = type == ValidateType::EMAIL ? &emailEdit : &phoneEdit;
	Service& service = Service::instance();

	CString value;
	edit->GetWindowTextW(value);
	std::string stdValue = CT2CA(value);

	try
	{
		bool exists = type == ValidateType::EMAIL ? 
			service.emailCustomerExists(stdValue) :
			service.phoneCustomerExists(stdValue);
		if (exists)
		{
			std::string field { type == ValidateType::EMAIL ? "Email" : "Phone"};
			std::stringstream msg;
			msg << "Invalid " << field << ". This " << field << " already exists.";
			throw std::invalid_argument(msg.str());
		}

		AfxMessageBox(
			_T("Is valid!"),
			MB_OK | MB_ICONINFORMATION);
	}
	catch (const std::exception& error)
	{
		AfxMessageBox(
			CA2W(error.what()),
			MB_OK | MB_ICONERROR);
	}
}


CNewCustomerDlg::CNewCustomerDlg(
	std::shared_ptr<Customer> customerObj,
	DialogMode mode,
	CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_CUSTOMER_DIALOG, pParent),
	m_customer(customerObj), m_mode(mode)
{
}

void CNewCustomerDlg::OnOK()
{
	
	
	try
	{
		m_customer->setName(getStdStrFromCEdit(nameEdit));
		m_customer->setEmail(getStdStrFromCEdit(emailEdit));
		m_customer->setPhone(getStdStrFromCEdit(phoneEdit));

		std::string streetAndNumber{ getStdStrFromCEdit(streetAndNumberEdit) };
		std::string city{ getStdStrFromCEdit(cityEdit) };
		std::string state{ getStdStrFromCEdit(stateEdit) };
		std::string country{ getStdStrFromCEdit(countryEdit) };
		
		m_customer->setShippingAddress(ShippingAddress(
			streetAndNumber,
			city,
			state,
			country,
			getIntFromCEdit(zipCodeEdit)
		));
	}
	catch ([[maybe_unused]] std::invalid_argument& _)
	{
		AfxMessageBox(_T("Invalid Zip Code. It has to be a "
			"a valid number greather than 0."), MB_OK | MB_ICONERROR);
		return;
	}

	catch ([[maybe_unused]] std::out_of_range& _)
	{
		AfxMessageBox(_T("Invalid Zip Code. It's to big."), MB_OK | MB_ICONERROR);
		return;
	}

	if (m_customer->isValid())
		CDialogEx::OnOK();
	else
		AfxMessageBox(_T("Customer is not valid. Please do not leave empty fields."), MB_OK | MB_ICONERROR);
}


BOOL CNewCustomerDlg::DestroyWindow()
{	
	return CDialogEx::DestroyWindow();
}

CNewCustomerDlg::~CNewCustomerDlg()
{
	
}

void CNewCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, nameEdit);
	DDX_Control(pDX, IDC_EDIT2, emailEdit);
	DDX_Control(pDX, IDC_EDIT3, phoneEdit);
	DDX_Control(pDX, IDC_EDIT4, streetAndNumberEdit);
	DDX_Control(pDX, IDC_EDIT5, cityEdit);
	DDX_Control(pDX, IDC_EDIT6, stateEdit);
	DDX_Control(pDX, IDC_EDIT7, countryEdit);
	DDX_Control(pDX, IDC_EDIT8, zipCodeEdit);

	if (m_mode == DialogMode::UPDATE_MODE)
	{
		nameEdit.SetWindowTextW(CA2W(m_customer->name().c_str()));
		emailEdit.SetWindowTextW(CA2W(m_customer->email().c_str()));
		phoneEdit.SetWindowTextW(CA2W(m_customer->phone().c_str()));
		streetAndNumberEdit.SetWindowTextW(CA2W(m_customer->shippingAddress().streetAndNumber().c_str()));
		cityEdit.SetWindowTextW(CA2W(m_customer->shippingAddress().city().c_str()));
		stateEdit.SetWindowTextW(CA2W(m_customer->shippingAddress().state().c_str()));
		countryEdit.SetWindowTextW(CA2W(m_customer->shippingAddress().country().c_str()));
		zipCodeEdit.SetWindowTextW(CA2W(std::to_string(m_customer->shippingAddress().zipCode()).c_str()));
	}
}


BEGIN_MESSAGE_MAP(CNewCustomerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewCustomerDlg::OnValidateEmailClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CNewCustomerDlg::OnValidatePhoneClicked)
END_MESSAGE_MAP()


// CNewCustomerDlg message handlers


void CNewCustomerDlg::OnValidateEmailClicked()
{
	validateBy(ValidateType::EMAIL);
}


void CNewCustomerDlg::OnValidatePhoneClicked()
{
	validateBy(ValidateType::PHONE);
}
