// CProductsDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CProductsDlg.h"
#include "afxdialogex.h"
#include "src/ui/utils/mfc_utils.h"
#include "CNewProductDlg.h"
#include "src/middleware/Service.h"
#include "src/middleware/model/Product.h"


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
	DDX_Control(pDX, IDC_LIST1, m_productsListCtrl);
	initListCtrl(m_productsListCtrl, {"SKU", "Description", "Price", "Weight"});
}


BEGIN_MESSAGE_MAP(CProductsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CProductsDlg::OnAddProductBtnClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CProductsDlg::OnDeleteProductBtnClicked)
END_MESSAGE_MAP()


// CProductsDlg message handlers


void CProductsDlg::OnAddProductBtnClicked()
{
	std::shared_ptr<Product> product = std::make_shared<Product>();
	CNewProductDlg newProductDlg(product, this);
	try
	{
		if (newProductDlg.DoModal())
		{
			Service::instance().addProduct(*product);
		}
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}


void CProductsDlg::OnDeleteProductBtnClicked()
{
	// TODO: Add your control notification handler code here
}
