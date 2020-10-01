#pragma once

#include "goods.h"


class OrderItemDB : public object
{
	real8 m_quantity;
	wstring_t m_productSKU;
	ref<set_member> m_key;

	OrderItemDB(const wstring_t& sku, 
		real8 quantity, 
		nat8 orderNumber,
		nat8 itemNumber);

public:
	METACLASS_DECLARATIONS(OrderItemDB, object);

	static ref<OrderItemDB> create(const wstring_t& productSKU, real8 quantity, nat8 orderNumber, nat8 itemNumber);
	bool isEqual(const wstring_t& sku, real8 quantity) const;
	bool isEqual(ref<OrderItemDB> item) const;

	real8 quantity() const { return m_quantity; }
	wstring_t productSKU() const { return m_productSKU; }
	ref<set_member> key() const { return m_key;}
};

