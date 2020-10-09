#include "pch.h"
#include "helper_functions.h"
#include <string>

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
