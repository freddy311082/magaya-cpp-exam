// CNewCustomerDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CNewCustomerDlg.h"
#include "afxdialogex.h"


// CNewCustomerDlg dialog

IMPLEMENT_DYNAMIC(CNewCustomerDlg, CDialogEx)

CNewCustomerDlg::CNewCustomerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_CUSTOMER_DIALOG, pParent)
{

}

CNewCustomerDlg::~CNewCustomerDlg()
{
}

void CNewCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewCustomerDlg, CDialogEx)
END_MESSAGE_MAP()


// CNewCustomerDlg message handlers
