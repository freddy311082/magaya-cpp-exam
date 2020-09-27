#include "pch.h"
#include "ProductMapping.h"
#include "src/datasource/db/model/ProductDB.h"
#include "src/middleware/model/Product.h"

ref<ProductDB> ProductMapping::toDbModel(const Product& product)
{	
	return ProductDB::create(product.sku().c_str(), 
							 product.description().c_str(),
							 product.price(),
							 product.weight());
}

ProductPtr ProductMapping::toModel(const ref<ProductDB>& producrDb)
{
	std::string sku = producrDb->sku().getChars(), description = producrDb->description().getChars();
	return std::make_unique<Product>(sku, 
									 description,
									 producrDb->price(),
									 producrDb->weight());
}
