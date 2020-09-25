#include "pch.h"
#include "ShippingAddressMapping.h"
#include "src/middleware/model/ShippingAddress.h"
#include "src/datasource/db/model/ShippingAddressDB.h"


ShippingAddressDB ShippingAddressMapping::toDbModel(const ShippingAddress& addr)
{
	return ShippingAddressDB{
	addr.streetAndNumber.c_str(),
		addr.city.c_str(),
		addr.state.c_str(),
		addr.country.c_str(),
		addr.zipCode };
};


ShippingAddress ShippingAddressMapping::toModel(const ShippingAddressDB& addrDb)
{
	return ShippingAddress{ addrDb.streetAndNumber.getChars(),
						 addrDb.city.getChars(),
						 addrDb.state.getChars(),
						 addrDb.country.getChars(),
						 addrDb.zipCode };
}
