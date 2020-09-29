#pragma once

#include "src/utils/usings.h"


class OrderMapping
{
public:
	static ref<OrderDB> toDbModel(const Order& order);
	static OrderPtr toModel(const ref<OrderDB>& orderDb, CustomerPtr&& customer);
};
