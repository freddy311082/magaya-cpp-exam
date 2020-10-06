#include "pch.h"
#include "OrderMapping.h"
#include "OrderItemMapping.h"
#include "ShippingAddressMapping.h"
#include "src/datasource/db/model/OrderDB.h"
#include "src/datasource/db/model/ProductDB.h"

#include "src/middleware/model/Order.h"
#include "src/middleware/model/OrderItem.h"

ref<OrderDB> OrderMapping::toDbModel(const Order& order, bool populateOrderItems)
{
	dbDateTime dt(
		order.datetime().tm_year,
		order.datetime().tm_mon,
		order.datetime().tm_yday,
		order.datetime().tm_hour,
		order.datetime().tm_min,
		order.datetime().tm_sec);
	ref<OrderDB> orderDb = OrderDB::create(
		order.number(),
		dt,
		static_cast<uint8_t>(order.paymentType()),
		ShippingAddressMapping::toDbModel(order.shippingAddress()));

	int i = 0;
	for (const auto& item: order.items())
	{
		modify(orderDb)->addItem(
			item->product()->sku().c_str(), 
			item->quantity());
	}
	return orderDb;
}

OrderPtr OrderMapping::toModel(
	const ref<OrderDB>& orderDb, 
	const OrderItemsDBProdPairList& oiProdList)
{	
	std::time_t datetime = orderDb->datetime().asTime_t();
	
	OrderPtr order = std::make_unique<Order>(
		orderDb->number(), 
		*std::localtime(&datetime),
		static_cast<PaymentType>(orderDb->paymentType()),
		ShippingAddressMapping::toModel(orderDb->shippingAddress()));

	for (const auto& oiProdPair: oiProdList)
	{
		order->addItem(OrderItemMapping::toModel(oiProdPair.orderItemDb, oiProdPair.productDb));
	}

	return order;
}
