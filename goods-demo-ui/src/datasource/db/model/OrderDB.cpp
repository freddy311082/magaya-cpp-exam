#include "pch.h"
#include "OrderDB.h"
#include <functional>
#include <string>
#include "OrderItemDB.h"

#include <iostream>



OrderDB::OrderDB(nat8 number,
	const dbDateTime& datetime,
	nat1 paymentType,
	const ShippingAddressDB& shippingAddress) :
	object(self_class),
	m_number(number),
	m_datetime(datetime),
	m_paymentType(paymentType),
	m_shippingAddress(shippingAddress),
	m_lastItemNumber(0)
{
	m_key = set_member::create(this, std::to_string(m_number).c_str());
	m_items = B_tree::create(this);
}


ref<OrderDB> OrderDB::create(nat4 number,
	const dbDateTime& datetime,
	nat1 paymentType,
	const ShippingAddressDB& shippingAddress)
{
	return NEW OrderDB(number, datetime, paymentType, shippingAddress);
}

ref<OrderItemDB> OrderDB::addItem(const wstring_t& productSKU, real8 quantity)
{	
	modify(m_items)->insert(
		OrderItemDB::create(
			productSKU, 
			quantity, 
			m_number, 
			++m_lastItemNumber)->key());
	ref<OrderItemDB> item = m_items->last->obj;
	return item;
}

void OrderDB::deleteItem(const wstring_t& productSKU, real8 quantity)
{
	auto item = getItem(productSKU, quantity);
	if (item != nullptr)
		modify(m_items)->remove(item->key());
	else
		throw std::invalid_argument("This item doesn't exists.");
}

std::list<wstring_t> OrderDB::allProductSKUsPerItem() const
{
	std::list<wstring_t> result;
	auto item = m_items->first;

	bool firstLoop = true;
	while (!item.is_nil())
	{
		ref<OrderItemDB> orderItemDb = item->obj;
		result.push_back(orderItemDb->productSKU());
		item = item->next;
	}

	return result;
}

std::unordered_set<std::string> OrderDB::allProductSKUsUsed() const
{
	std::unordered_set<std::string> result;
	auto item = m_items->first;

	while(!item.is_nil())
	{
		ref<OrderItemDB> orderItemDB;
		result.insert(orderItemDB->productSKU().getChars());
		item = item->next;
	}
	
	return result;
}


OrderItemDbList OrderDB::items() const
{
	OrderItemDbList result;
	auto itemRef = m_items->first;

	while (!itemRef.is_nil())
	{
		ref<OrderItemDB> item = itemRef->obj;
		result.push_back(item);
		itemRef = itemRef->next;
	}

	return result;
}

ref<OrderItemDB> OrderDB::getItem(const wstring_t& productSKU, real8 quantity) const
{
	auto currentItem = m_items->first;
	while (!currentItem.is_nil())
	{
		ref<OrderItemDB> orderItem = currentItem;
		if (orderItem->isEqual(productSKU, quantity))
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
		FIELD(m_lastItemNumber),
		FIELD(m_items),
		FIELD(m_key);
}

REGISTER(OrderDB, object, pessimistic_scheme);