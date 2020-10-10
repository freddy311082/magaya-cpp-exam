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
	m_shippingAddress(shippingAddress),
	m_numberOfOrders(0)
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
		FIELD(m_orders),
		FIELD(m_numberOfOrders);
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
	modify(m_orders)->insert(order->key());
	m_numberOfOrders++;
}

ref<OrderDB> CustomerDB::getOrder(nat8 orderNumber) const
{
	std::stringstream query;
	query << "m_number=" << orderNumber;

	result_set_cursor cursor;
	m_orders->filter(cursor, query.str().c_str());
	return cursor.next();
}

void CustomerDB::getOrdersInto(OrdersDBList& orders) const
{
	auto order = m_orders->first;

	while (!order.is_nil())
	{
		ref<OrderDB> orderDb = order;
		orders.push_back(orderDb);
		order = order->next;
	}
}

OrdersDBList CustomerDB::allOrders() const
{
	OrdersDBList result;

	auto order = m_orders->first;

	while(!order.is_nil())
	{
		result.push_back(static_cast<ref<OrderDB>>(order->obj));
		order = order->next;
	}
	
	return result;
}

bool CustomerDB::canBeDeleted() const
{
	if (m_orders->empty())
	{
		assert(m_numberOfOrders == 0);
		return true;
	}

	return false;
}

void CustomerDB::deleteOrder(ref<OrderDB> order)
{
	modify(m_orders)->remove(order->key());
	m_numberOfOrders--;
}

void CustomerDB::updateProductSkuInOrders(const wstring_t& originalSku, const wstring_t& newSku)
{
	auto order = m_orders->first;

	while(!order.is_nil())
	{
		ref<OrderDB> orderDb = order->obj;
		modify(orderDb)->updateSku(originalSku, newSku);
		order = order->next;
	}
}


REGISTER(CustomerDB, object, pessimistic_scheme);