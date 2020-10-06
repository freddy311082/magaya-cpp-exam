
// goods-demo-uiDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "goods-demo-ui.h"
#include "goods-demo-uiDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgoodsdemouiDlg dialog



CgoodsdemouiDlg::CgoodsdemouiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GOODSDEMOUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pages[0] = &m_customersPage;
	m_pages[1] = &m_productsPage;
	m_pages[2] = &m_ordersPage;
}

void CgoodsdemouiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrol);
}

BEGIN_MESSAGE_MAP(CgoodsdemouiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CgoodsdemouiDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CgoodsdemouiDlg message handlers

BOOL CgoodsdemouiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_TabCtrol.InsertItem(0, _T("Customers"));
	m_TabCtrol.InsertItem(1, _T("Products"));
	m_TabCtrol.InsertItem(2, _T("Orders"));

	Init();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CgoodsdemouiDlg::Init()
{
	CRect rect;
	m_TabCtrol.GetClientRect(&rect);
	m_customersPage.Create(IDD_CUSTOMERS_DIALOG, &m_TabCtrol);
	m_customersPage.SetWindowPos(NULL, 0, 40, rect.Width() - 10, rect.Height() - 10, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_customersPage;

	m_productsPage.Create(IDD_PRODUCTS_DIALOG, &m_TabCtrol);
	m_productsPage.SetWindowPos(NULL, 0, 40, rect.Width() - 10, rect.Height() - 10, SWP_HIDEWINDOW | SWP_NOZORDER);

	m_ordersPage.Create(IDD_ORDERS_DIALOG, &m_TabCtrol);
	m_ordersPage.SetWindowPos(NULL, 0, 40, rect.Width() - 10, rect.Height() - 10, SWP_HIDEWINDOW | SWP_NOZORDER);
}


void CgoodsdemouiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CgoodsdemouiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CgoodsdemouiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CgoodsdemouiDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (m_pwndShow!= NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}

	int selectedIndex = m_TabCtrol.GetCurFocus();
	m_pages[selectedIndex]->ShowWindow(SW_SHOW);
	m_pwndShow = m_pages[selectedIndex];
	
	*pResult = 0;
}
