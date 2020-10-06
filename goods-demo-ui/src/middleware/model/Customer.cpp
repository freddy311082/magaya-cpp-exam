#include "pch.h"
#include "Customer.h"
#include <sstream>

using namespace std;

Customer::Customer(const std::string& name, const std::string& phone, const std::string& email,
                   const ShippingAddress& shippingAddress)
	: m_name(name),
	m_phone(phone),
	m_email(email),
	m_shippingAddress(shippingAddress)
{
}

bool Customer::isValid() const
{
	return !m_name.empty() &&
		!m_phone.empty() &&
		!m_email.empty() &&
		m_shippingAddress.isValid();
}

std::string Customer::info()
{
	stringstream ss;
	ss << "** Customer **" << endl <<
		"name: " << m_name << endl <<
		"phone: " << m_phone << endl <<
		"email: " << m_email << endl <<
		m_shippingAddress.info() << endl;

	return ss.str();
}
