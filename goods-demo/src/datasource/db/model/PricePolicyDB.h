#pragma once

#include "goods.h"


class PricePolicyDB : public object
{
protected:
	real8 m_price;
	real8 m_weight;

	PricePolicyDB(real8 price, real8 weight = 1.);

public:
	ref<PricePolicyDB> create(real8 price, real8 weight = 1.);
	real8 cost(real8 quantity);
	~PricePolicyDB() = default;

	METACLASS_DECLARATIONS(PricePolicyDB, object);

};