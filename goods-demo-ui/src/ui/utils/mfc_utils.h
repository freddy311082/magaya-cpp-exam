#pragma once
#include <string>
#include <vector>
#include <afxwin.h>
#include <afxcmn.h>

std::string getStdStrFromCEdit(const CEdit& edit);
int getIntFromCEdit(const CEdit& edit);
double getDoubleFromCEdit(const CEdit& edit);
void initListCtrl(CListCtrl& listCtrl, const std::vector<std::string>& headers);
void addRowToListCtrl(CListCtrl& listCtrl,
	const std::string& itemKey,
	const std::vector<std::string>& items);
int getSelectedRow(const CListCtrl& listCtrl);
void setValueToCEdit(CEdit& edit, int value);
void setValueToCEdit(CEdit& edit, double value);
void setValueToCEdit(CEdit& edit, const std::string& value);
