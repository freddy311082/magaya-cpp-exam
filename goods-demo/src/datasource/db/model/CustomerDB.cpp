#include "pch.h"
#include <sstream>
#include "CustomerDB.h"
#include "OrderDB.h"


CustomerDB::CustomerDB(const wstring_t&	name,
	const wstring_t& phone,
	const wstring_t& email,
	const ShippingAddressDB& shippingAddress) :
	object(self_class),
	m_name(name),
	m_phone(phone),
	m_email(email),
	m_shippingAddress(shippingAddress)
{
	char* _name = m_name.getChars();
	m_key = set_member::create(this, _name);
	m_orders = B_tree::create(this);
	delete[] _name;
}

ref<CustomerDB> CustomerDB::create(const wstring_t&	name,
	const wstring_t& phone,
	const wstring_t& email,
	const ShippingAddressDB& shippingAddress)
{
	return NEW CustomerDB(name, phone, email, shippingAddress);
}

field_descriptor& CustomerDB::describe_components()
{
	return	FIELD(m_name),
		FIELD(m_phone),
		FIELD(m_email),
		FIELD(m_key),
		FIELD(m_shippingAddress),
		FIELD(m_orders);
}

void CustomerDB::update(const wstring_t& name, const wstring_t& phone, const wstring_t& email,
	const ShippingAddressDB& shippingAddress)
{
	m_name = name;
	m_phone = phone;
	m_email = email;
	m_shippingAddress = shippingAddress;
}

void CustomerDB::addOrder(ref<OrderDB> order)
{
	if (getOrder(order->number()) == nullptr)
		modify(m_orders)->insert(order->key());
	else
		throw std::invalid_argument("Unable to insert this order: Order number already in use.");
}

ref<OrderDB> CustomerDB::getOrder(nat8 orderNumber) const
{
	std::stringstream query;
	query << "m_number=" << orderNumber;

	result_set_cursor cursor;
	m_orders->filter(cursor, query.str().c_str());
	return cursor.next();
}


REGISTER(CustomerDB, object, pessimistic_scheme);