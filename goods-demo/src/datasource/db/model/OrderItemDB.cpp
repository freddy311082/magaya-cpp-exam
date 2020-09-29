#include "pch.h"
#include "OrderItemDB.h"
#include  "ProductDB.h"
#include  <string>

OrderItemDB::OrderItemDB(ref<ProductDB> product, real8 quantity, nat8 orderNumber, nat8 itemNumber) :
	object(self_class), m_product(product), m_quantity(quantity)
{
	m_key = set_member::create(this,
		(std::to_string(orderNumber) +
			"_" +
			std::to_string(itemNumber)).c_str());
}

ref<OrderItemDB> OrderItemDB::create(ref<ProductDB> product, real8 quantity, nat8 orderNumber, nat8 itemNumber)
{
	return NEW OrderItemDB(product, quantity, orderNumber, itemNumber);
}

bool OrderItemDB::isEqual(ref<OrderItemDB> item) const
{
	return isEqual(item->m_product, item->m_quantity);
}

bool OrderItemDB::isEqual(ref<ProductDB> product, real8 quantity) const
{
	return product->sku() == m_product->sku() &&
		quantity == m_quantity;
}

field_descriptor& OrderItemDB::describe_components()
{
	return FIELD(m_product), FIELD(m_quantity), FIELD(m_key);
}




REGISTER(OrderItemDB, object, pessimistic_scheme);