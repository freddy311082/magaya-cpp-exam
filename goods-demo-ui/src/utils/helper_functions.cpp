#include "pch.h"
#include "helper_functions.h"
#include <string>
#include <sstream>

using namespace std;

bool strToDouble(const string& str, double& result)
{
	try
	{
		result = stod(str);
	}
	catch ([[maybe_unused]] const std::exception& _)
	{
		return false;
	}

	return true;
}

string to_string(PaymentType paymentType)
{
	switch (paymentType)
	{
	case PaymentType::CASH:
		return "Cash";

	case PaymentType::CHECK:
		return "Check";

	case PaymentType::CREDIT_CARD:
		return "Credit Card";

	case PaymentType::OTHER:
		return "Other";
	}

	return "";
}

std::string to_string(const std::tm& datetime)
{
	stringstream ss;

	ss << datetime.tm_year << "-" <<
		datetime.tm_mon << "-" <<
		datetime.tm_mday << " " <<
		datetime.tm_hour << ":" <<
		datetime.tm_min << ":" <<
		datetime.tm_sec;
	
	return ss.str();
}
