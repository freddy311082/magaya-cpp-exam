#include "pch.h"
#include "mfc_utils.h"

std::string getStdStrFromCEdit(const CEdit& edit)
{
	CString value;
	edit.GetWindowTextW(value);
	return std::string{ CW2A(value) };
}


int getIntFromCEdit(const CEdit& edit)
{
	return std::stoi(getStdStrFromCEdit(edit));
}

void initListCtrl(CListCtrl& listCtrl, const std::vector<std::string>& headers)
{
	listCtrl.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	const DWORD extendedStyle = listCtrl.GetExtendedStyle();
	listCtrl.SetExtendedStyle(extendedStyle | LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT);

	for (int i = 0; i < headers.size(); ++i)
	{
		listCtrl.InsertColumn(i, CA2W(headers[i].c_str()), LVCFMT_LEFT, 300);
	}
}

void addRowToListCtrl(CListCtrl& listCtrl,
	int row,
	const std::string& itemKey,
	const std::vector<std::string>& items)
{
	CA2W keyValue(items[row].c_str());
	listCtrl.InsertItem(row, keyValue);

	for (int i = 0; i < items.size(); ++i)
	{
		listCtrl.SetItemText(row, i, CA2W(items[i].c_str()));
	}
	
	
}
