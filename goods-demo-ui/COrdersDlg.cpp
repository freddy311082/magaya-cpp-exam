// COrdersDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "COrdersDlg.h"
#include "afxdialogex.h"
#include "CNewOrderDlg.h"
#include "src/middleware/model/Order.h"


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
	ON_BN_CLICKED(IDC_BUTTON1, &COrdersDlg::OnNewOrderBtnClicked)
END_MESSAGE_MAP()


// COrdersDlg message handlers


void COrdersDlg::OnNewOrderBtnClicked()
{
	std::shared_ptr<Order> orderPtr = std::make_shared<Order>();
	auto dlg = CNewOrderDlg(orderPtr);
	dlg.DoModal();
}
