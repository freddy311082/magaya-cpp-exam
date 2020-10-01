#include "pch.h"
#include "OrderItemDB.h"
#include  <string>

OrderItemDB::OrderItemDB(const wstring_t& sku, real8 quantity, nat8 orderNumber, nat8 itemNumber) :
	object(self_class), m_productSKU(sku), m_quantity(quantity)
{
	m_key = set_member::create(this,
		(std::to_string(orderNumber) +
			"_" +
			std::to_string(itemNumber)).c_str());
}

ref<OrderItemDB> OrderItemDB::create(const wstring_t& productSKU, real8 quantity, nat8 orderNumber, nat8 itemNumber)
{
	return NEW OrderItemDB(productSKU, quantity, orderNumber, itemNumber);
}

bool OrderItemDB::isEqual(ref<OrderItemDB> item) const
{
	return isEqual(item->m_productSKU, item->m_quantity);
}

bool OrderItemDB::isEqual(const wstring_t& sku, real8 quantity) const
{
	return sku == m_productSKU &&
		quantity == m_quantity;
}

field_descriptor& OrderItemDB::describe_components()
{
	return FIELD(m_productSKU), FIELD(m_quantity), FIELD(m_key);
}




REGISTER(OrderItemDB, object, pessimistic_scheme);