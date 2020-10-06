#pragma once

#include <string>
#include "src/utils/usings.h"

class Product
{
	std::string m_sku;
	std::string m_description;
	double m_price;
	double m_weight;

public:
	double price() const { return m_price; }
	double weight() const { return m_weight; }
	std::string sku() const { return m_sku; }
	std::string description() const { return m_description; }

	Product(const std::string& sku, 
	        std::string& description,
			double price,
			double weight = 1);
		std::string info() const;

	double cost(double quantity) const { return quantity * m_price / m_weight; }
};