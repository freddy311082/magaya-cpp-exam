#pragma once

#include "src/utils/usings.h"


class OrderItemMapping
{
public:
	static ref<OrderItemDB> toDbModel(const OrderItemPtr& orderItem, uint64_t orderNumber, uint32_t itemNumber);
	static OrderItemPtr toModel(const ref<OrderItemDB>& orderItemDB);
};
