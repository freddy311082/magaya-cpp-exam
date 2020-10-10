#pragma once
#include <memory>
#include "src/middleware/model/Product.h"
#include "src/utils/enums.h"

// CNewProductDlg dialog

class CNewProductDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewProductDlg)
	std::shared_ptr<Product> m_product;
	DialogMode m_mode;

public:
	CNewProductDlg(std::shared_ptr<Product> product,
		DialogMode mode = DialogMode::CREATE_NEW_MODE,
		CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNewProductDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_PRODUCT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnOK() override;

	DECLARE_MESSAGE_MAP()
public:
	CEdit skuEdit;
	CEdit descriptionEdit;
	CEdit priceEdit;
	CEdit weightEdit;
	afx_msg void OnValidateSKUBtnClicked();
};
