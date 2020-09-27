#include <pch.h>
#include "ProductDB.h"

ProductDB::ProductDB(const wstring_t& sku,
	const wstring_t& description,
	const PricePolicyDB&  defaultPricePolicy) :
	object(self_class),
	m_sku(sku),
	m_description(description),
	m_defaultPricePolicy(defaultPricePolicy)
{
	char* key = m_sku.getChars();
	m_key = set_member::create(this, key);
	delete[] key;
}

ref<ProductDB> ProductDB::create(const wstring_t& sku,
	const wstring_t& description,
	const PricePolicyDB& defaultPricePolicy)
{
	return NEW ProductDB(sku, description, defaultPricePolicy);
}

field_descriptor& ProductDB::describe_components()
{
	return FIELD(m_sku),
		FIELD(m_description),
		FIELD(m_defaultPricePolicy),
		FIELD(m_key);
}

real8 ProductDB::cost(real8 quantity) const
{
	return m_defaultPricePolicy.cost(quantity);
}

void ProductDB::update(const wstring_t& sku, const wstring_t& description, const PricePolicyDB& defaultPricePolicy)
{
	m_sku = sku;
	m_description = description;
	m_defaultPricePolicy = defaultPricePolicy;
}


REGISTER(ProductDB, object, pessimistic_scheme);