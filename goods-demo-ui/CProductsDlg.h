#pragma once


// CProductsDlg dialog

class CProductsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductsDlg)
	void showAllProducts();

public:
	CProductsDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CProductsDlg();
	void enableUI();
	void reloadProductList();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRODUCTS_DIALOG };
#endif

protected:
	void setEnableUI(bool value);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddProductBtnClicked();
	afx_msg void OnDeleteProductBtnClicked();
	CListCtrl productsListCtrl;
	CButton addButton;
	CButton deleteButton;
};
