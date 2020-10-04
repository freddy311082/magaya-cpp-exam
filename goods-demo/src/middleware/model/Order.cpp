#include "pch.h"
#include "Order.h"
#include "OrderItem.h"
#include <algorithm>
#include <list>
#include <sstream>

using namespace  std;

Order::Order(int m_number, const std::tm& m_datetime, PaymentType m_payment_type,
	const ShippingAddress& m_shipping_address) 
	: m_number(m_number),
	m_datetime(m_datetime),
	m_paymentType(m_payment_type),
	m_shippingAddress(m_shipping_address),
	m_totalValue(0)
{
}

void Order::addItem(OrderItemPtr&& item)
{
	if (item == nullptr)
		throw std::invalid_argument("Invalid order item.");

	m_items.push_back(move(item));
}

void Order::removeItem(size_t pos)
{
	if (pos > m_items.size() - 1)
		throw out_of_range("Invalid Order Item index.");

	size_t i = 0;
	auto it = find_if(
		m_items.begin(), 
		m_items.end(), 
		[&](const auto& _) {return i++ == pos; });

	m_items.erase(it);
}

void Order::updateItem(size_t pos, OrderItemPtr&& item)
{
	if (item == nullptr)
		throw invalid_argument("Invalid order item.");

	if (pos > m_items.size() - 1)
		throw out_of_range("Invalid Order Item index.");

	removeItem(pos);
	size_t i = 0;
		
	 auto it = find_if(
	 	m_items.begin(), 
	 	m_items.end(), 
	 	[&](const auto& _) { return ++i == pos; });
	auto posIteratorToBeDeleted = it;
	++posIteratorToBeDeleted;
	m_items.erase(posIteratorToBeDeleted);
	m_items.insert(++it, move(item));
}

std::string Order::info() const
{
	stringstream itemsSs;

	for (const auto& item: m_items)
		itemsSs << item->info();
	
	stringstream ss;
	ss << "<<<<< Order >>>>>" << endl <<
		"Order Number: " << m_number << endl <<
		"Payment Type: " << to_string(static_cast<int>(m_paymentType)) << endl <<
		m_shippingAddress.info() <<
		"Total Value" << m_totalValue << endl <<
		itemsSs.str() <<
		"<<<<<<<<<>>>>>>>>";
	return ss.str();
}
