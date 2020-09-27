#include "pch.h"
#include "PricePolicy.h"
#include <sstream>

using namespace std;

PricePolicy::PricePolicy(double price, real8 weight)
	: m_price(price), m_weight(weight)
{
}

std::string PricePolicy::info() const
{
	stringstream ss;

	ss << "*** Price Policy ***" << endl <<
		"Price: " << m_price << endl <<
		"Weight: " << m_weight << endl <<
		"********************";
	
	return ss.str();
}
