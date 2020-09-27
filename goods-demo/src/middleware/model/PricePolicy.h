#pragma once

#include <memory>
#include <string>

class PricePolicy
{
	double m_price = 0;
	double m_weight = 1.;

public:
	PricePolicy(double price, real8 weight = 1.);
	PricePolicy() = default;
	double price() const { return m_price; }
	double weight() const { return m_weight; }
	PricePolicy& operator = (const PricePolicy&) = default;
	std::string info() const;
};

using PricePolicyPtr = std::unique_ptr<PricePolicy>;