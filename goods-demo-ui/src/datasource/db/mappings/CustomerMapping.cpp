#include "pch.h"
#include <memory>
#include "CustomerMapping.h"
#include "src/datasource/db/model/CustomerDB.h"
#include "src/middleware/model/Customer.h"
#include "ShippingAddressMapping.h"

ref<CustomerDB> CustomerMapping::toDbModel(const Customer& customer)
{
	return  CustomerDB::create(	customer.name().c_str(),
						customer.phone().c_str(),
						customer.email().c_str(),
						ShippingAddressMapping::toDbModel(customer.shippingAddress()));
}

CustomerPtr CustomerMapping::toModel(const ref<CustomerDB>& customerDb)
{
	ShippingAddress shippingAddr = ShippingAddressMapping::toModel(customerDb->shippingAddress());
	
	return std::make_unique<Customer>(
		customerDb->name().getChars(),
		customerDb->phone().getChars(),
		customerDb->email().getChars(),
		shippingAddr,
		customerDb->numberOfOrders());
}
