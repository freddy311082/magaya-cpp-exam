#pragma once

#include <goods.h>
#include <memory>

class ProductDB;
class Product;

using ProductPtr = std::unique_ptr<Product>;

class ProductMapping
{
public:
	static ref<ProductDB> toDbModel(const Product& product);
	static ProductPtr toModel(const ref<ProductDB>& producrDb);
};
