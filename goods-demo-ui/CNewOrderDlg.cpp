// CNewOrderDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CNewOrderDlg.h"
#include "afxdialogex.h"


// CNewOrderDlg dialog

IMPLEMENT_DYNAMIC(CNewOrderDlg, CDialogEx)

CNewOrderDlg::CNewOrderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_ORDER_DIALOG, pParent)
{

}

CNewOrderDlg::~CNewOrderDlg()
{
}

void CNewOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewOrderDlg, CDialogEx)
END_MESSAGE_MAP()


// CNewOrderDlg message handlers
