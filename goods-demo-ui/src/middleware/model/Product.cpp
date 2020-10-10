#include "pch.h"
#include "Product.h"
#include <sstream>

using namespace std;

Product::Product(const std::string& sku, std::string& description, double price, double weight, uint32_t timeUsed)
	: m_sku(sku), m_description(description), m_price(price), m_weight(weight), m_timesUsed(timeUsed)
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
		"Time Used: " << m_timesUsed << endl <<
		"****************";
	
	return ss.str();
}

bool Product::isValid() const
{
	return !m_sku.empty() &&
		!m_description.empty() &&
		m_price >= 0 &&
		m_weight >= 0;
}
