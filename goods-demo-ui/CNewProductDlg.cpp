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
	DialogMode mode,
	CWnd* pParent /*=nullptr*/):
	CDialogEx(IDD_NEW_PRODUCT_DIALOG, pParent),
	m_product(product), m_mode(mode)
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

	if (m_mode == DialogMode::UPDATE_MODE)
	{
		skuEdit.SetWindowTextW(CA2W(m_product->sku().c_str()));
		descriptionEdit.SetWindowTextW(CA2W(m_product->description().c_str()));
		priceEdit.SetWindowTextW(CA2W(std::to_string(m_product->price()).c_str()));
		weightEdit.SetWindowTextW(CA2W(std::to_string(m_product->weight()).c_str()));
	}
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
