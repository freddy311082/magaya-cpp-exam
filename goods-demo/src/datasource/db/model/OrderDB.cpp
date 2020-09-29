#include "pch.h"
#include "OrderDB.h"

#include <functional>
#include <string>
#include "OrderItemDB.h"
#include "ProductDB.h"
#include "CustomerDB.h"


OrderDB::OrderDB(nat8 number,
	const dbDateTime& datetime,
	nat1 paymentType,
	const ShippingAddressDB& shippingAddress,
	ref<CustomerDB> customer) :
	object(self_class),
	m_number(number),
	m_datetime(datetime),
	m_paymentType(paymentType),
	m_shippingAddress(shippingAddress),
	m_customer(customer->key()),
	m_lastItemNumber(0)
{
	m_key = set_member::create(this, std::to_string(m_number).c_str());
	m_items = B_tree::create(this);
}


GOODS_NAMESPACE::ref<OrderDB> OrderDB::create(nat4 number,
	const dbDateTime& datetime,
	nat1 paymentType,
	const ShippingAddressDB& shippingAddress,
	ref<CustomerDB> customer)
{
	return NEW OrderDB(number, datetime, paymentType, shippingAddress, customer);
}

void OrderDB::addItem(ref<ProductDB> product, real8 quantity)
{
	auto item = OrderItemDB::create(product, quantity, m_number, ++m_lastItemNumber);
	modify(m_items)->insert(item->key());	
}

void OrderDB::deleteItem(ref<ProductDB> product, real8 quantity)
{
	auto item = getItem(product, quantity);
	if (item != nullptr)
		modify(m_items)->remove(item->key());
	else
		throw std::invalid_argument("This item doesn't exists.");
}


ref<OrderItemDB> OrderDB::getItem(ref<ProductDB> product, real8 quantity) const
{
	auto currentItem = m_items->first;
	while (!currentItem.is_nil())
	{
		ref<OrderItemDB> orderItem = currentItem;
		if (orderItem->isEqual(product, quantity))
			return orderItem;
		
		currentItem = currentItem->next;
	}

	return nullptr;
}

field_descriptor& OrderDB::describe_components()
{
	return	FIELD(m_number),
		FIELD(m_datetime),
		FIELD(m_paymentType),
		FIELD(m_shippingAddress),
		FIELD(m_customer),
		FIELD(m_lastItemNumber),
		FIELD(m_items),
		FIELD(m_key);
}

REGISTER(OrderDB, set_owner, pessimistic_scheme);