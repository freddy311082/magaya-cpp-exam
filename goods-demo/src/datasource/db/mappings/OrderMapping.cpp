#include "pch.h"
#include "OrderMapping.h"
#include "OrderItemMapping.h"
#include "CustomerMapping.h"
#include "ProductMapping.h"
#include "ShippingAddressMapping.h"
#include "src/datasource/db/model/OrderDB.h"
#include "src/datasource/db/model/OrderItemDB.h"
#include "src/middleware/model/Order.h"
#include "src/middleware/model/Customer.h"
#include "src/middleware/model/OrderItem.h"

ref<OrderDB> OrderMapping::toDbModel(const Order& order)
{
	dbDateTime dt(
		order.datetime().tm_year,
		order.datetime().tm_mon,
		order.datetime().tm_yday,
		order.datetime().tm_hour,
		order.datetime().tm_min,
		order.datetime().tm_sec);
	ref<CustomerDB> customerDb = CustomerMapping::toDbModel(*order.customer());
	ref<OrderDB> orderDb = OrderDB::create(
		order.number(),
		dt,
		static_cast<uint8_t>(order.paymentType()),
		ShippingAddressMapping::toDbModel(order.shippingAddress()),
		customerDb);

	int i = 0;
	for (const auto& item: order.items())
	{
		ref<ProductDB> productDb = ProductMapping::toDbModel(*item->product());
		modify(orderDb)->addItem(productDb, item->quantity());
	}
	return orderDb;
}

OrderPtr OrderMapping::toModel(const ref<OrderDB>& orderDb, CustomerPtr&& customer)
{
	if (customer == nullptr)
		throw std::invalid_argument("Customer is not valid.");
	
	std::time_t datetime = orderDb->datetime().asTime_t();
	
	OrderPtr order = std::make_unique<Order>(
		orderDb->number(), 
		*std::localtime(&datetime),
		static_cast<PaymentType>(orderDb->paymentType()),
		ShippingAddressMapping::toModel(orderDb->shippingAddress()),
		std::move(customer));

	auto item = orderDb->items()->first;

	while(!item.is_nil())
	{
		ref<OrderItemDB> orderItemDb = item;
		order->addItem(OrderItemMapping::toModel(orderItemDb));
		item = item->next;
	}

	return order;
}
