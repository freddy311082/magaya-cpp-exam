#include <pch.h>
#include <string>
#include "ShippingAddressDB.h"

ShippingAddressDB::ShippingAddressDB(const wstring_t& street_and_number, const wstring_t& city, const wstring_t& state,
	const wstring_t& country, nat4 zip_code)
	: m_streetAndNumber(street_and_number),
	m_city(city),
	m_state(state),
	m_country(country),
	m_zipCode(zip_code)
{
}

field_descriptor& ShippingAddressDB::describe_components()
{
	return	FIELD(m_streetAndNumber),
		FIELD(m_city),
		FIELD(m_state),
		FIELD(m_country),
		FIELD(m_zipCode);
}

field_descriptor& describe_field(ShippingAddressDB& addr)
{
	return addr.describe_components();
}
