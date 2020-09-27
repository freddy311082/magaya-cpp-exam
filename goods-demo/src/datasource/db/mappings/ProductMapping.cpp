#include "pch.h"
#include "ProductMapping.h"
#include "src/datasource/db/model/ProductDB.h"
#include "src/middleware/model/Product.h"
#include "PricePolicyMapping.h"

ref<ProductDB> ProductMapping::toDbModel(const Product& product)
{
	PricePolicyDB pricePolicyDb = PricePolicyMapping::toDbModel(product.defaultPricePolicy());
	
	return ProductDB::create(product.sku().c_str(), 
							 product.description().c_str(),
							 pricePolicyDb);
}

ProductPtr ProductMapping::toModel(const ref<ProductDB>& producrDb)
{
	std::string sku = producrDb->sku().getChars(), description = producrDb->description().getChars();
	PricePolicyDB pricePolicy = producrDb->defaultPricePolicy();
	return std::make_unique<Product>(sku, 
									 description,
									 PricePolicyMapping::toModel(pricePolicy));
}
