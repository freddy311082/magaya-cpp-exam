// CNewProductDlg.cpp : implementation file
//

#include "pch.h"
#include "goods-demo-ui.h"
#include "CNewProductDlg.h"
#include "afxdialogex.h"
#include  "src/middleware/Service.h"
#include "src/ui/utils/mfc_utils.h"


// CNewProductDlg dialog

IMPLEMENT_DYNAMIC(CNewProductDlg, CDialogEx)

CNewProductDlg::CNewProductDlg(
	std::shared_ptr<Product> product,
	CWnd* pParent /*=nullptr*/):
	CDialogEx(IDD_NEW_PRODUCT_DIALOG, pParent),
	m_product(product)
{
}

CNewProductDlg::~CNewProductDlg()
{
}

void CNewProductDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, skuEdit);
	DDX_Control(pDX, IDC_EDIT2, descriptionEdit);
	DDX_Control(pDX, IDC_EDIT3, priceEdit);
	DDX_Control(pDX, IDC_EDIT4, weightEdit);
}

void CNewProductDlg::OnOK()
{
	m_product->setSKU(getStdStrFromCEdit(skuEdit));
	m_product->setDescription(getStdStrFromCEdit(descriptionEdit));
	try
	{
		m_product->setPrice(getDoubleFromCEdit(priceEdit));
		m_product->setWeight(getDoubleFromCEdit(weightEdit));
	}
	catch ([[maybe_unused]] const std::exception& _)
	{
		AfxMessageBox(_T("Invalid product. Please make sure that all fields are valid."), MB_OK | MB_ICONERROR);
		return;
	}

	if (m_product->isValid())
		CDialogEx::OnOK();
	else
		AfxMessageBox(_T("Invalid product. Please make sure that all fields are valid."), MB_OK | MB_ICONERROR);
}


BEGIN_MESSAGE_MAP(CNewProductDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewProductDlg::OnValidateSKUBtnClicked)
END_MESSAGE_MAP()


// CNewProductDlg message handlers


void CNewProductDlg::OnValidateSKUBtnClicked()
{
	try
	{
		CString sku;
		skuEdit.GetWindowTextW(sku);
		std::string skuStr = CW2A(sku);

		if (Service::instance().existsProductSKU(skuStr))
			throw std::invalid_argument("This product already exists.");
		
		AfxMessageBox(
			_T("Is valid!"),
			MB_OK | MB_ICONINFORMATION);
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}
