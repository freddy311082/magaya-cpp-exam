#include "pch.h"
#include "PricePolicyDB.h"


PricePolicyDB::PricePolicyDB(real8 price, real8 weight)
	: m_price(price),m_weight(weight)
{
}

field_descriptor& PricePolicyDB::describe_components()
{
	return FIELD(m_price), FIELD(m_weight);
}

real8 PricePolicyDB::cost(real8 quantity) const
{
	// In case of countable products, m_weight will always be equal to 1
	return quantity / m_weight * m_price;
}

field_descriptor& describe_field(PricePolicyDB& pricePolicy)
{
	return pricePolicy.describe_components();
}
