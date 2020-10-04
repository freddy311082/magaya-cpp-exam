// CCustomersDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CCustomersDlg.h"
#include "afxdialogex.h"


// CCustomersDlg dialog

IMPLEMENT_DYNAMIC(CCustomersDlg, CDialogEx)

CCustomersDlg::CCustomersDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOMERS_DIALOG, pParent)
{

}

CCustomersDlg::~CCustomersDlg()
{
}

void CCustomersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomersDlg, CDialogEx)
END_MESSAGE_MAP()


// CCustomersDlg message handlers
