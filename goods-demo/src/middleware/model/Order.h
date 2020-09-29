﻿#pragma once
#include <memory>
#include <ctime>

#include "src/utils/enums.h"
#include "src/utils/usings.h"
#include "ShippingAddress.h"




class Order
{
	int m_number;
	std::tm m_datetime;
	PaymentType m_paymentType;
	ShippingAddress m_shippingAddress;
	CustomerPtr m_customer;
	OrderItemsList m_items;
	double m_totalValue;
	
public:

	Order(int m_number, const std::tm& m_datetime, PaymentType m_payment_type,
		const ShippingAddress& m_shipping_address, CustomerPtr&& customer);

	int number() const{ return m_number; }
	std::tm datetime() const { return m_datetime; }
	PaymentType paymentType() const { return m_paymentType; }
	ShippingAddress shippingAddress() const { return m_shippingAddress; }
	const CustomerPtr& customer() const { return m_customer; }
	double totalValue() const { return m_totalValue; }
	const OrderItemsList& items() const { return m_items;}

	void addItem(OrderItemPtr&& item);
	void removeItem(size_t pos);
	void updateItem(size_t pos, OrderItemPtr&& item);
};

using OrderPtr = std::unique_ptr<Order>;