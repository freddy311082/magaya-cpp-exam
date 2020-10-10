#include <pch.h>
#include "ProductDB.h"

ProductDB::ProductDB(const wstring_t& sku,
	const wstring_t& description,
	real8 price, 
	real8 weight) :
	object(self_class),
	m_sku(sku),
	m_description(description),
	m_price(price),
	m_weight(weight),
	m_timesUsed(0)
{
	generateKey();
}

void ProductDB::generateKey()
{
	char* key = m_sku.getChars();
	m_key = set_member::create(this, key);
	delete[] key;
}

ref<ProductDB> ProductDB::create(const wstring_t& sku,
                                 const wstring_t& description,
                                 real8 price, real8 weight)
{
	return NEW ProductDB(sku, description, price, weight);
}

field_descriptor& ProductDB::describe_components()
{
	return FIELD(m_sku),
		FIELD(m_description),
		FIELD(m_price),
		FIELD(m_weight),
		FIELD(m_key),
		FIELD(m_timesUsed);
}

real8 ProductDB::cost(real8 quantity) const
{
	return quantity * m_price / m_weight;
}

void ProductDB::update(const wstring_t& sku, const wstring_t& description, real8 price, real8 weight)
{
	m_sku = sku;
	m_description = description;
	m_price = price;
	m_weight = weight;
	generateKey();
}


REGISTER(ProductDB, object, pessimistic_scheme);