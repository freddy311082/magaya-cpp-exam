#include "pch.h"
#include "PricePolicyDB.h"

PricePolicyDB::PricePolicyDB(real8 price, real8 weight) :
	object(self_class), m_price(price), m_weight(weight)
{
}

::field_descriptor& PricePolicyDB::describe_components()
{
	return FIELD(m_price);
}


real8 PricePolicyDB::cost(real8 quantity)
{
	// In case of countable products, m_weight will always be equal to 1
	return quantity / m_weight * m_price;
}

ref<PricePolicyDB> PricePolicyDB::create(real8 price, real8 weight)
{
	return NEW PricePolicyDB(price, weight);
}


REGISTER(PricePolicyDB, object, pessimistic_scheme);