#include <pch.h>
#include <string>
#include "ShippingAddressDB.h"


field_descriptor& ShippingAddressDB::describe_components()
{
	return	FIELD(streetAndNumber),
		FIELD(city),
		FIELD(state),
		FIELD(country),
		FIELD(zipCode);
}

field_descriptor& describe_field(ShippingAddressDB& addr)
{
	return addr.describe_components();
}
