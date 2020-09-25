#pragma once

#include <goods.h>
#include <memory>

class CustomerDB;
struct Customer;
using CustomerPtr = std::unique_ptr<Customer>;

class CustomerMapping
{
public:
	static ref<CustomerDB> toDbModel(const Customer& customer);
	static CustomerPtr toModel(const ref<CustomerDB>& customerDb);
};
