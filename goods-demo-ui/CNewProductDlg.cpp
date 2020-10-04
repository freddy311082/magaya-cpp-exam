// CNewProductDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CNewProductDlg.h"
#include "afxdialogex.h"


// CNewProductDlg dialog

IMPLEMENT_DYNAMIC(CNewProductDlg, CDialogEx)

CNewProductDlg::CNewProductDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_PRODUCT_DIALOG, pParent)
{

}

CNewProductDlg::~CNewProductDlg()
{
}

void CNewProductDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewProductDlg, CDialogEx)
END_MESSAGE_MAP()


// CNewProductDlg message handlers
