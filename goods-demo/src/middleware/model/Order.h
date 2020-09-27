#pragma once
#include <memory>
#include <ctime>

#include "src/utils/enums.h"
#include "ShippingAddress.h"

struct Order
{
	int number;
	std::tm datetime;
	PaymentType paymentType;
	ShippingAddressPtr shippingAddress;
};

using OrderPtr = std::unique_ptr<Order>;