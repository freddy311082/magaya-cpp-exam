#include "pch.h"
#include "ShippingAddress.h"
#include <sstream>

using namespace std;

//std::string streetAndNumber;
//std::string city;
//std::string state;
//std::string country;
//uint32_t zipCode;

ShippingAddress::ShippingAddress(const std::string& street_and_number, const std::string& city,
	const std::string& state, const std::string& country, uint32_t zip_code):
	m_streetAndNumber(street_and_number),
	m_city(city),
	m_state(state),
	m_country(country),
	m_zipCode(zip_code)
{
}

std::string ShippingAddress::info() const
{
	stringstream ss;

	ss << ">> Shipping Address >>" << endl <<
		"Street and Number: " << m_streetAndNumber << endl <<
		"City: " << m_city << endl <<
		"State: " << m_state << endl <<
		"Country: " << m_country << endl <<
		"ZipCode: " << m_zipCode << endl;

	return ss.str();
}

bool ShippingAddress::isValid() const
{
	return !m_streetAndNumber.empty() &&
		!m_state.empty() &&
		!m_country.empty() &&
		!m_country.empty() &&
		m_zipCode > 0;
}

std::string ShippingAddress::toString() const
{
	return m_streetAndNumber + ", " +
		m_city + ", " + m_state + ", " +
		m_country + ", ZIP: " + to_string(m_zipCode);
}
