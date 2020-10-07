#include "pch.h"
#include "helper_functions.h"
#include <string>

bool strToDouble(const std::string& str, double& result)
{
	try
	{
		result = std::stod(str);
	}
	catch ([[maybe_unused]] const std::exception& _)
	{
		return false;
	}

	return true;
}
