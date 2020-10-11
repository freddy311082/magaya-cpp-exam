#pragma once
#include <string>
#include <vector>
#include <afxwin.h>
#include <afxcmn.h>


#define WM_USER_NUMBER_START WM_USER + 100
#define WM_USER_CUSTOMER_LIST_UPDATED WM_USER_NUMBER_START
#define WM_USER_ADDED_OR_DELETED_ORDER WM_USER_NUMBER_START + 1
#define WM_USER_PRODUCT_UPDATED WM_USER_NUMBER_START + 2
#define WM_USER_ENABLE_OR_DISABLE_CREATE_ORDER WM_USER_NUMBER_START + 3

std::string getStdStrFromCEdit(const CEdit& edit);
int getIntFromCEdit(const CEdit& edit);
double getDoubleFromCEdit(const CEdit& edit);
void initListCtrl(CListCtrl& listCtrl, const std::vector<std::string>& headers);
void addRowToListCtrl(CListCtrl& listCtrl,
	const std::string& itemKey,
	const std::vector<std::string>& items);
int getSelectedRow(const CListCtrl& listCtrl);
std::vector<int> getAllSelectedRows(const CListCtrl& listCtrl);
std::string getTextFromListCtrl(const CListCtrl& listCtrl, int row, int col);
void setValueToCEdit(CEdit& edit, int value);
void setValueToCEdit(CEdit& edit, double value);
void setValueToCEdit(CEdit& edit, const std::string& value);
