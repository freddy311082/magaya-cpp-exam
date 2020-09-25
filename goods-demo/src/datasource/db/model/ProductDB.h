#pragma once

#include "goods.h"


class PricePolicyDB;

class ProductDB : public object
{
private:
	wstring_t					m_sku;
	wstring_t					m_description;
	ref<PricePolicyDB>	m_defaultPricePolicy;

	ProductDB(const wstring_t& sku, const wstring_t& description, ref<PricePolicyDB> defaultPricePolicy);

public:
	static ref<ProductDB> create(const wstring_t& sku,
		const wstring_t& description,
		ref<PricePolicyDB> defaultPricePolicy);

	~ProductDB() = default;
	METACLASS_DECLARATIONS(ProductDB, object);
};