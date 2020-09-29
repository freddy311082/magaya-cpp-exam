#pragma once

#include "goods.h"


class ProductDB;

class OrderItemDB : public object
{
	real8 m_quantity;
	ref<ProductDB> m_product;
	ref<set_member> m_key;

	OrderItemDB(ref<ProductDB> product, real8 quantity, nat8 orderNumber, nat8 itemNumber);

public:
	METACLASS_DECLARATIONS(OrderItemDB, object);

	static ref<OrderItemDB> create(ref<ProductDB> product, real8 quantity, nat8 orderNumber, nat8 itemNumber);
	bool isEqual(ref<ProductDB> product, real8 quantity) const;
	bool isEqual(ref<OrderItemDB> item) const;

	real8 quantity() const { return m_quantity; }
	ref<ProductDB> product() const { return m_product; }
	ref<set_member> key() const { return m_key;}
};

