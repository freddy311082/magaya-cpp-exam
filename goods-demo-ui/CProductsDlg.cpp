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

void CProductsDlg::showAllProducts()
{
	ProductsList products = Service::instance().allProducts();

	int i = 0;
	for (const auto& product : products)
	{
		addRowToListCtrl(m_productsListCtrl,
			product->sku(),
			{ product->sku(),
				product->description(),
				std::to_string(product->price()),
				std::to_string(product->weight())
			});
	}
}

void CProductsDlg::reloadProductList()
{
	m_productsListCtrl.DeleteAllItems();
	showAllProducts();
}

CProductsDlg::CProductsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRODUCTS_DIALOG, pParent)
{

}

CProductsDlg::~CProductsDlg()
{
}

void CProductsDlg::enableUI()
{
	reloadProductList();
	setEnableUI(true);
}

void CProductsDlg::setEnableUI(bool value)
{
	addButton.EnableWindow(value);
	deleteButton.EnableWindow(value);
}

void CProductsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_productsListCtrl);
	initListCtrl(m_productsListCtrl, { "SKU", "Description", "Price", "Weight" });
	DDX_Control(pDX, IDC_BUTTON1, addButton);
	DDX_Control(pDX, IDC_BUTTON2, deleteButton);

	setEnableUI(false);
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
		if (newProductDlg.DoModal() == IDOK)
		{
			Service::instance().addProduct(*product);
			reloadProductList();
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
	try
	{
		int index = getSelectedRow(m_productsListCtrl);
		if (index == -1)
			throw std::invalid_argument("No product selected. Please, select one.");
		
		auto text = m_productsListCtrl.GetItemText(index, 0);
		std::string sku = CW2A(text);
		Service::instance().deleteProduct(sku);
		reloadProductList();
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}
