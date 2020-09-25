#pragma once

#include <memory>

struct PricePolicy
{
	double price = 0;
	double weight = 0;
};

using PricePolicyPtr = std::unique_ptr<PricePolicy>;