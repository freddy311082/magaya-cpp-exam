#pragma once

#include "src/utils/usings.h"
#include <string>
#include "Product.h"

class OrderItem
{
	double m_quantity;
	ProductPtr m_product;
public:
	OrderItem(double quantity, ProductPtr&& product);
	OrderItem(const OrderItem& item);

	double quantity() const
	{
		return m_quantity;
	}

	const ProductPtr& product() const
	{
		return m_product;
	}

	double cost() const;
	std::string info() const;
};