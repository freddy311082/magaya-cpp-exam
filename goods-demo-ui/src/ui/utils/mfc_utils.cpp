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

double getDoubleFromCEdit(const CEdit& edit)
{
	return std::stod(getStdStrFromCEdit(edit));
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
	const std::string& itemKey,
	const std::vector<std::string>& items)
{
	int row = listCtrl.GetItemCount();
	CA2W keyValue(items[0].c_str());
	listCtrl.InsertItem(row, keyValue);

	int index = row < 0 ? listCtrl.GetItemCount() : row;
	for (int i = 0; i < items.size(); ++i)
	{
		listCtrl.SetItemText(index, i, CA2W(items[i].c_str()));
	}
	
	
}

int getSelectedRow(const CListCtrl& listCtrl)
{
	POSITION pos = listCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return -1;

	return listCtrl.GetNextSelectedItem(pos);
}

std::string getTextFroListCtrl(const CListCtrl& listCtrl, int row, int col)
{
	CString text = listCtrl.GetItemText(row, col);
	std::string  result{ CW2A(text) };
	return result;
}

void setValueToCEdit(CEdit& edit, int value)
{
	setValueToCEdit(edit, std::to_string(value));
}

void setValueToCEdit(CEdit& edit, double value)
{
	setValueToCEdit(edit, std::to_string(value));
}

void setValueToCEdit(CEdit& edit, const std::string& value)
{
	CA2W str(value.c_str());
	edit.SetWindowTextW(str);
}
