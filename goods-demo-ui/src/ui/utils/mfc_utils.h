#pragma once
#include <string>
#include <vector>
#include <afxwin.h>
#include <afxcmn.h>

std::string getStdStrFromCEdit(const CEdit& edit);
int getIntFromCEdit(const CEdit& edit);
void initListCtrl(CListCtrl& listCtrl, const std::vector<std::string>& headers);
void addRowToListCtrl(CListCtrl& listCtrl,
	int row,
	const std::string& itemKey,
	const std::vector<std::string>& items);
