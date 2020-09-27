#pragma once

#include <string>
#include <memory>
#include  <list>

#include "PricePolicy.h"

class Product
{
	std::string m_sku;
	std::string m_description;
	PricePolicy m_defaultPricePolicy;

public:
	std::string sku() const
	{
		return m_sku;
	}

	std::string description() const
	{
		return m_description;
	}

	PricePolicy defaultPricePolicy() const
	{
		return m_defaultPricePolicy;
	}

	Product(const std::string& sku, 
	        std::string& description, 
	        const PricePolicy& defaultPricePolicy);
		std::string info() const;
};

using ProductPtr = std::unique_ptr<Product>;
using ProductsList = std::list<ProductPtr>;