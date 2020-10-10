#pragma once

#include <string>
#include "src/utils/usings.h"

class Product
{
	std::string m_sku;
	std::string m_description;
	double m_price;
	double m_weight;
	uint32_t m_timesUsed;

public:
	double price() const { return m_price; }
	double weight() const { return m_weight; }
	std::string sku() const { return m_sku; }
	std::string description() const { return m_description; }
	uint32_t timesUsed() const { return m_timesUsed; }

	void setSKU(const std::string& sku)	{ m_sku = sku; }
	void setDescription(const std::string& description)	{m_description = description; }
	void setPrice(double price){ m_price = price; }
	void setWeight(double weight) { m_weight = weight; }
	void setTimesUsed(int timeUsed) { m_timesUsed = timeUsed; }
	

	Product(const std::string& sku, 
	        std::string& description,
			double price,
			double weight = 1,
			uint32_t timeUsed = 0);
		std::string info() const;
	Product() = default;
	Product(const Product& product) = default;

	double cost(double quantity) const { return quantity * m_weight / m_price; }
	bool isValid() const;
};