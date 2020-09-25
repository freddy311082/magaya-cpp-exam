#pragma once

#include <list>
#include <memory>

#include "Product.h"

struct OrderItem
{
	double amount;
	PricePolicyPtr pricePolicy;
	ProductPtr product;
};

using OrderItemPtr = std::unique_ptr<OrderItem>;
using OrderItemList = std::list<OrderItemPtr>;
