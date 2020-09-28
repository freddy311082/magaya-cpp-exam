#include "pch.h"
#include "OrderDB.h"
#include <string>

using namespace std;


OrderDB::OrderDB(nat4 number,
	const dbDateTime& datetime,
	nat1 paymentType,
	const ShippingAddressDB& shippingAddress) :
	set_owner(self_class, this),
	m_number(number),
	m_datetime(datetime),
	m_paymentType(paymentType),
	m_shippingAddress(shippingAddress)
{
	
}


GOODS_NAMESPACE::ref<OrderDB> OrderDB::create(nat4 number,
	const dbDateTime& datetime,
	nat1 paymentType,
	const ShippingAddressDB& shippingAddress)
{
	return NEW OrderDB(number, datetime, paymentType, shippingAddress);
}

field_descriptor& OrderDB::describe_components()
{
	return	FIELD(m_number),
		FIELD(m_datetime),
		FIELD(m_paymentType),
		FIELD(m_shippingAddress),
		FIELD(m_customer);
}

REGISTER(OrderDB, set_owner, pessimistic_scheme);