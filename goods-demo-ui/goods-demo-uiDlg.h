
// goods-demo-uiDlg.h : header file
//

#pragma once

#include "CCustomersDlg.h"
#include "CProductsDlg.h"
#include "COrdersDlg.h"


// CgoodsdemouiDlg dialog
class CgoodsdemouiDlg : public CDialogEx
{
	bool m_initCustomersPending;
// Construction
public:
	CgoodsdemouiDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GOODSDEMOUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnCustomerAddedMessage(WPARAM wParam, LPARAM lParam);
	void Init();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrol;
	CCustomersDlg m_customersPage;
	CProductsDlg m_productsPage;
	COrdersDlg m_ordersPage;
	CDialogEx* m_pages[3];
	CWnd* m_pwndShow;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
