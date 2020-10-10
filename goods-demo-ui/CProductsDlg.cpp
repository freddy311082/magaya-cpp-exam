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
#include  <string>


// CProductsDlg dialog

IMPLEMENT_DYNAMIC(CProductsDlg, CDialogEx)

void CProductsDlg::showAllProducts()
{
	ProductsList products = Service::instance().allProducts();

	int i = 0;
	for (const auto& product : products)
	{
		addRowToListCtrl(productsListCtrl,
			product->sku(),
			{ product->sku(),
				product->description(),
				std::to_string(product->price()),
				std::to_string(product->weight()),
				std::to_string(product->timesUsed())
			});
	}
}

std::shared_ptr<Product> CProductsDlg::getProductObjFromListCtrl(int row)
{
	
	return std::make_shared<Product>(
		getTextFromListCtrl(productsListCtrl, row, 0),
		getTextFromListCtrl(productsListCtrl, row, 1),
		std::stod(getTextFromListCtrl(productsListCtrl, row, 2)),
		std::stod(getTextFromListCtrl(productsListCtrl, row, 3)),
		std::stoi(getTextFromListCtrl(productsListCtrl, row, 4))
	);
}

void CProductsDlg::reloadProductList()
{
	productsListCtrl.DeleteAllItems();
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
	productsListCtrl.EnableWindow(value);
}

void CProductsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, productsListCtrl);
	DDX_Control(pDX, IDC_BUTTON1, addButton);
	DDX_Control(pDX, IDC_BUTTON2, deleteButton);
	
	initListCtrl(productsListCtrl, 
		{
			"SKU",
			"Description",
			"Price",
			"Weight",
			"Times Used" });
	setEnableUI(false);
}


BEGIN_MESSAGE_MAP(CProductsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CProductsDlg::OnAddProductBtnClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CProductsDlg::OnDeleteProductBtnClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CProductsDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CProductsDlg message handlers


void CProductsDlg::OnAddProductBtnClicked()
{
	std::shared_ptr<Product> product = std::make_shared<Product>();
	CNewProductDlg newProductDlg(product);
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
		std::vector<int> indexesToDelete = getAllSelectedRows(productsListCtrl);

		if (indexesToDelete.empty())
			throw std::invalid_argument("No product selected. Please, select at least one.");

		if (AfxMessageBox(_T("Ar you sure that you want to delete this Product?"), 
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			for (int index : indexesToDelete)
			{
				Service::instance().deleteProduct(getTextFromListCtrl(productsListCtrl, index, 0));
			}
			reloadProductList();
		}
	}
	catch (const std::exception& error)
	{
		CA2W msg(error.what());
		AfxMessageBox(msg, MB_OK | MB_ICONERROR);
	}
}


void CProductsDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (productsListCtrl.GetSelectedCount() > 0)
	{
		try
		{
			CString text;
			int index = getSelectedRow(productsListCtrl);
			auto productUpdates = getProductObjFromListCtrl(index);
			std::string originalSku{ productUpdates->sku() };

			if (CNewProductDlg(productUpdates, DialogMode::UPDATE_MODE, this).DoModal() == IDOK)
			{
				Service::instance().updateProduct(originalSku, *productUpdates);
				reloadProductList();
			}
		}
		catch (const std::exception& error)
		{
			CA2W msg(error.what());
			AfxMessageBox(msg, MB_OK | MB_ICONERROR);
		}
	}
	
	*pResult = 0;
}
