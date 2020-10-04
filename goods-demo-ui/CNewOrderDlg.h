#pragma once


// CNewOrderDlg dialog

class CNewOrderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewOrderDlg)

public:
	CNewOrderDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNewOrderDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_ORDER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
