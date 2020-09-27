#include "pch.h"
#include "PricePolicyMapping.h"
#include "src/datasource/db/model/PricePolicyDB.h"
#include "src/middleware/model/PricePolicy.h"

using namespace std;

PricePolicyDB PricePolicyMapping::toDbModel(const PricePolicy& pricePolicy)
{
	return PricePolicyDB{ pricePolicy.price(), pricePolicy.weight() };
}

PricePolicy PricePolicyMapping::toModel(const PricePolicyDB& pricePolicyDb)
{
	return PricePolicy (pricePolicyDb.price(), pricePolicyDb.weight() );
}
