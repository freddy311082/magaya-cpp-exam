#pragma once

#include <string>
#include <list>
#include <utility>
#include "src/utils/enums.h"
#include "src/middleware/model/ShippingAddress.h"

struct  OrderItemParam;

using OrderItemsListParam = std::list<OrderItemParam>;

struct  OrderItemParam
{
	double quantity;
	std::string productSKU;
};

struct CreateOrderParams
{
	std::string customerEmail;
	PaymentType paymentType;
	ShippingAddress shippingAddress;
	OrderItemsListParam items;
};
