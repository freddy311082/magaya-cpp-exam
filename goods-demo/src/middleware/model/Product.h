#pragma once

#include <string>
#include <memory>

#include "PricePolicy.h"

struct Product
{
	std::string sku;
	std::string description;
	PricePolicyPtr defaultPricePolicy;
};

using ProductPtr = std::unique_ptr<Product>;
