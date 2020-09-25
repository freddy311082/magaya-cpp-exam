#include "pch.h"
#include "OrderItemDB.h"
#include "ProductDB.h"

OrderItemDB::OrderItemDB(real8 amount, ref<ProductDB> product, ref<PricePolicyDB> pricePolicy) :
	object(self_class), m_product(product), m_pricePolicy(pricePolicy)
{}

ref<OrderItemDB> OrderItemDB::create(real8 amount, ::ref<ProductDB> product, ::ref<PricePolicyDB> pricePolicy)
{
	return NEW OrderItemDB(amount, product, pricePolicy);
}

::field_descriptor& OrderItemDB::describe_components()
{
	return	FIELD(m_amount),
		FIELD(m_product),
		FIELD(m_pricePolicy);
}

REGISTER(OrderItemDB, object, pessimistic_scheme);
