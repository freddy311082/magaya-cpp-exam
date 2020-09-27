#pragma once

#include "goods.h"
#include "PricePolicyDB.h"


class ProductDB : public object
{
protected:
	wstring_t					m_sku;
	wstring_t					m_description;
	PricePolicyDB				m_defaultPricePolicy;
	ref<set_member>				m_key;

	ProductDB(const wstring_t& sku, const wstring_t& description, const PricePolicyDB& defaultPricePolicy);
public:
	METACLASS_DECLARATIONS(ProductDB, object);

	wstring_t sku() const { return m_sku; }
	wstring_t description() const { return m_description; }
	const PricePolicyDB& defaultPricePolicy() const { return m_defaultPricePolicy; }
	ref<set_member> key() const { return m_key; }
	real8 cost(real8 quantity) const;

	static ref<ProductDB> create(const wstring_t& sku,
		const wstring_t& description,
		const PricePolicyDB& defaultPricePolicy);
	void update(const wstring_t& sku, 
		const wstring_t& description, 
		const PricePolicyDB& defaultPricePolicy);
};