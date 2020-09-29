#include "pch.h"
#include "OrderItemMapping.h"
#include "ProductMapping.h"
#include "src/datasource/db/model/OrderItemDB.h"
#include "src/middleware/model/OrderItem.h"

ref<OrderItemDB> OrderItemMapping::toDbModel(const OrderItemPtr& orderItem, 
	uint64_t orderNumber, uint32_t itemNumber)
{
	ref<ProductDB> product = ProductMapping::toDbModel(*orderItem->product());
	return OrderItemDB::create(product, orderItem->quantity(), orderNumber, itemNumber);
}

OrderItemPtr OrderItemMapping::toModel(const ref<OrderItemDB>& orderItemDB)
{
	ProductPtr product = ProductMapping::toModel(orderItemDB->product());
	return std::make_unique<OrderItem>(orderItemDB->quantity(), std::move(product));
}
