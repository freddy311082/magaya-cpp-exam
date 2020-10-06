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