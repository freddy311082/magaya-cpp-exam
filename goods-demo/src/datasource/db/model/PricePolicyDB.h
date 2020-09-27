#pragma once

#include "goods.h"


class PricePolicyDB
{
	real8 m_price;
	real8 m_weight;

public:
	PricePolicyDB(real8 price, real8 weight = 1.0);

	PricePolicyDB() = default;

	real8 price() const { return m_price; }
	real8 weight() const { return m_weight; }

	real8 cost(real8 quantity) const;
	field_descriptor& describe_components();
	friend field_descriptor& describe_field(PricePolicyDB& shippingAddress);

	PricePolicyDB& operator = (const PricePolicyDB&) = default;
};