#pragma once

#include "goods.h"

class ProductDB;
class PricePolicyDB;

class OrderItemDB : public object
{
private:
	real8 m_amount;
	ref<ProductDB> m_product;
	ref<PricePolicyDB> m_pricePolicy;

	OrderItemDB(real8 amount, ref<ProductDB> product, ref<PricePolicyDB> pricePolicy);

public:
	static ref<OrderItemDB> create(real8 amount, ref<ProductDB> product, ref<PricePolicyDB> pricePolicy);
	~OrderItemDB() = default;

	METACLASS_DECLARATIONS(OrderItemDB, object);
};