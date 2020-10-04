// COrdersDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "COrdersDlg.h"
#include "afxdialogex.h"


// COrdersDlg dialog

IMPLEMENT_DYNAMIC(COrdersDlg, CDialogEx)

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
}


BEGIN_MESSAGE_MAP(COrdersDlg, CDialogEx)
END_MESSAGE_MAP()


// COrdersDlg message handlers
