#pragma once

#include <goods.h>
#include <memory>

#include "src/utils/usings.h"

class CustomerMapping
{
public:
	static ref<CustomerDB> toDbModel(const Customer& customer);
	static CustomerPtr toModel(const ref<CustomerDB>& customerDb);
};
