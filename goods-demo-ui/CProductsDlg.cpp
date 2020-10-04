// CProductsDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CProductsDlg.h"
#include "afxdialogex.h"


// CProductsDlg dialog

IMPLEMENT_DYNAMIC(CProductsDlg, CDialogEx)

CProductsDlg::CProductsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRODUCTS_DIALOG, pParent)
{

}

CProductsDlg::~CProductsDlg()
{
}

void CProductsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductsDlg, CDialogEx)
END_MESSAGE_MAP()


// CProductsDlg message handlers
