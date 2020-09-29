#include "pch.h"
#include "OrderItem.h"
#include <sstream>

using namespace std;

OrderItem::OrderItem(double quantity, ProductPtr&& product) :
	m_quantity(quantity)
{
	if (product == nullptr)
		throw invalid_argument("The product cannot be null.");

	m_product = move(product);
}

double OrderItem::cost() const
{
	return m_product->cost(m_quantity);
}

string OrderItem::info() const
{
	stringstream ss;

	ss << "=== Order Item ===" << endl <<
		"Quantity: " << m_quantity << endl <<
		m_product->info() << endl <<
		"Cost: " << cost() << endl <<
		"==================";
	
	return ss.str();
}

