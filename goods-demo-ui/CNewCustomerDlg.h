#pragma once

#include <memory>
#include <string>
#include "src/middleware/model/Customer.h"

// CNewCustomerDlg dialog

class CNewCustomerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewCustomerDlg)

	enum class ValidateType
	{
		EMAIL,
		PHONE
	};

	void validateBy(ValidateType type);
	
public:
	CNewCustomerDlg(
		std::shared_ptr<Customer> customerObj, 
		CWnd* pParent = nullptr);   // standard constructor

	BOOL DestroyWindow() override;
	virtual ~CNewCustomerDlg();
	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_CUSTOMER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	std::shared_ptr<Customer> m_customer;

	void OnOK() override;

	DECLARE_MESSAGE_MAP()
public:
	CEdit nameEdit;
	CEdit emailEdit;
	CEdit phoneEdit;
	CEdit streetAndNumberEdit;
	CEdit cityEdit;
	CEdit stateEdit;
	CEdit countryEdit;
	CEdit zipCodeEdit;
	afx_msg void OnValidateEmailCliecked();
	afx_msg void OnValidateEmailClicked();
};
