#pragma once

#include <goods.h>
#include "src/utils/usings.h"

class ProductMapping
{
public:
	static ref<ProductDB> toDbModel(const Product& product);
	static ProductPtr toModel(const ref<ProductDB>& producrDb);
};
