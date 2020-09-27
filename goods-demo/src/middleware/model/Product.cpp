#include "pch.h"
#include "Product.h"
#include <sstream>

using namespace std;

Product::Product(const std::string& sku, std::string& description, double price, double weight)
	: m_sku(sku), m_description(description), m_price(price), m_weight(weight)
{
}

std::string Product::info() const
{
	stringstream ss;

	ss << "*** Product  ***" << endl <<
		"SKU: " << m_sku << endl <<
		"Description: " << m_description << endl <<
		"Price: " << m_price << endl <<
		"Weight: " << m_weight << endl <<
		"****************";
	
	
	return ss.str();
}
