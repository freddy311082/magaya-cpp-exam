#pragma once

#include "src/middleware/model/ShippingAddress.h"
#include "src/datasource/db/model/ShippingAddressDB.h"


class ShippingAddressMapping
{
public:
	static ShippingAddressDB toDbModel(const ShippingAddress& addr);
	static ShippingAddress toModel(const ShippingAddressDB& addrDb);
};
