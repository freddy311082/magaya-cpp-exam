#include <pch.h>
#include "ProductDB.h"
#include  "PricePolicyDB.h"

ProductDB::ProductDB(const wstring_t& sku,
	const wstring_t& description,
	ref<PricePolicyDB> defaultPricePolicy) :
	object(self_class),
	m_sku(sku),
	m_description(description),
	m_defaultPricePolicy(defaultPricePolicy)
{}

ref<ProductDB> ProductDB::create(const wstring_t& sku,
	const wstring_t& description,
	ref<PricePolicyDB> defaultPricePolicy)
{
	return NEW ProductDB(sku, description, defaultPricePolicy);
}

::field_descriptor& ProductDB::describe_components()
{
	return	FIELD(m_sku),
		FIELD(m_description),
		FIELD(m_defaultPricePolicy);
}


REGISTER(ProductDB, set_owner, pessimistic_scheme);