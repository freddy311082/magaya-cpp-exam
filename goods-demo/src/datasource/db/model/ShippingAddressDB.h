#pragma once

#include "goods.h"

struct ShippingAddressDB
{
	wstring_t		streetAndNumber;
	wstring_t		city;
	wstring_t		state;
	wstring_t		country;
	nat4			zipCode;

	field_descriptor& describe_components();
	friend field_descriptor& describe_field(ShippingAddressDB& s);

	ShippingAddressDB& operator = (const ShippingAddressDB& ) = default;
};