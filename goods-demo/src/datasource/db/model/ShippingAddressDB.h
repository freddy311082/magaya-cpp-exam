#pragma once

#include "goods.h"

class ShippingAddressDB
{

private:
	wstring_t		m_streetAndNumber;
	wstring_t		m_city;
	wstring_t		m_state;
	wstring_t		m_country;
	nat4			m_zipCode;

public:
	ShippingAddressDB(const wstring_t& street_and_number,
		const wstring_t& city,
		const wstring_t& state,
		const wstring_t& country,
		nat4 zip_code);
	ShippingAddressDB() = default;

	wstring_t streetAndNumber() const
	{
		return m_streetAndNumber;
	}

	wstring_t city() const
	{
		return m_city;
	}

	wstring_t state() const
	{
		return m_state;
	}

	wstring_t country() const
	{
		return m_country;
	}

	nat4 zipCode() const
	{
		return m_zipCode;
	}

	field_descriptor& describe_components();
	friend field_descriptor& describe_field(ShippingAddressDB& shippingAddress);

	ShippingAddressDB& operator = (const ShippingAddressDB& ) = default;
};