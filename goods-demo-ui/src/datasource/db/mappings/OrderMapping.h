#pragma once

#include "src/utils/usings.h"


class OrderMapping
{
public:
	static ref<OrderDB> toDbModel(const Order& order,
		bool createorderItems = true);
	static OrderPtr toModel(const ref<OrderDB>& orderDb, 
		const OrderItemsDBProdPairList& oiProdList, 
		const std::string& customerEmail);
};
