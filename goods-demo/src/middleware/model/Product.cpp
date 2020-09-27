#include "pch.h"
#include "Product.h"
#include <sstream>

using namespace std;

Product::Product(const std::string& sku, std::string& description, const PricePolicy& defaultPricePolicy)
	: m_sku(sku), m_description(description), m_defaultPricePolicy(defaultPricePolicy)
{
}

std::string Product::info() const
{
	stringstream ss;

	ss << "*** Product  ***" << endl <<
		"SKU: " << m_sku << endl <<
		"Description: " << m_description << endl <<
		m_defaultPricePolicy.info() <<
		"****************";
	
	
	return ss.str();
}
