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

	void setSKU(const std::string& sku)	{ m_sku = sku; }
	void setDescription(const std::string& description)	{m_description = description; }
	void setPrice(double price){ m_price = price; }
	void setWeight(double weight) { m_weight = weight; }
	

	Product(const std::string& sku, 
	        std::string& description,
			double price,
			double weight = 1);
		std::string info() const;
		Product() = default;

	double cost(double quantity) const { return quantity * m_weight / m_price; }
	bool isValid() const;
};