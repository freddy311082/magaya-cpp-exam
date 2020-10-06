#include "pch.h"
#include "OrderItemMapping.h"
#include "ProductMapping.h"
#include "src/datasource/db/model/OrderItemDB.h"
#include "src/middleware/model/OrderItem.h"

ref<OrderItemDB> OrderItemMapping::toDbModel(const OrderItemPtr& orderItem, 
	uint64_t orderNumber, uint32_t itemNumber)
{
	return OrderItemDB::create(orderItem->product()->sku().c_str(), 
		orderItem->quantity(), 
		orderNumber, 
		itemNumber);
}

OrderItemPtr OrderItemMapping::toModel(
	const ref<OrderItemDB>& orderItemDB,
	const ref<ProductDB>& productDb)
{
	return std::make_unique<OrderItem>(
		orderItemDB->quantity(), 
		ProductMapping::toModel(productDb));
}
