#pragma once


// COrdersDlg dialog

class COrdersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COrdersDlg)

public:
	COrdersDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~COrdersDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ORDERS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNewOrderBtnClicked();
};
