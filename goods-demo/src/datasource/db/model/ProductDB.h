#pragma once

#include "goods.h"


class ProductDB : public object
{
protected:
	wstring_t m_sku;
	wstring_t m_description;
	real8 m_price;
	real8 m_weight;
	ref<set_member>				m_key;

	ProductDB(const wstring_t& sku, const wstring_t& description, real8 price, real8 weight = 1.);
public:
	METACLASS_DECLARATIONS(ProductDB, object);

	wstring_t sku() const { return m_sku; }
	wstring_t description() const { return m_description; }
	real8 price() const { return m_price; }
	real8 weight() const { return m_weight; }
	ref<set_member> key() const { return m_key; }
	real8 cost(real8 quantity) const;

	static ref<ProductDB> create(const wstring_t& sku,
		const wstring_t& description,
		real8 price, 
		real8 weight = 1.);
	void update(const wstring_t& sku, 
		const wstring_t& description, 
		const real8 price, 
		real8 weight);
};