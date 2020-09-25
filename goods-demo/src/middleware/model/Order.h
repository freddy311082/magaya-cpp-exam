#pragma once
#include <memory>
#include <ctime>

#include "src/utils/enums.h"
#include "ShippingAddress.h"
#include "OrderItem.h"

struct Order
{
	int number;
	std::tm datetime;
	PaymentType paymentType;
	ShippingAddressPtr shippingAddress;
	OrderItemList orderItems;
};

using OrderPtr = std::unique_ptr<Order>;