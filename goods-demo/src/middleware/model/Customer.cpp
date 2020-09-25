#include "pch.h"
#include "Customer.h"
#include <sstream>

using namespace std;


Customer::Customer(const std::string& name, const std::string& phone, const std::string& email,
	const ShippingAddress& shippingAddress)
	: name(name),
	phone(phone),
	email(email),
	shippingAddress(shippingAddress)
{
}

std::string Customer::info()
{
	stringstream ss;
	ss << "** Customer **" << endl <<
		"name: " << name << endl <<
		"phone: " << phone << endl <<
		"email: " << email << endl <<
		shippingAddress.info() << endl;

	return ss.str();
}
