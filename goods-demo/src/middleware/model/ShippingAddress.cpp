#include "pch.h"
#include "ShippingAddress.h"
#include <sstream>

using namespace std;

//std::string streetAndNumber;
//std::string city;
//std::string state;
//std::string country;
//uint32_t zipCode;

std::string ShippingAddress::info() const
{
	stringstream ss;

	ss << ">> Shipping Address >>" << endl <<
		"Street and Number: " << streetAndNumber << endl <<
		"City: " << city << endl <<
		"State: " << state << endl <<
		"Country: " << country << endl <<
		"ZipCode: " << zipCode << endl;

	return ss.str();
}
