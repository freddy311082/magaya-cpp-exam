#pragma once

#include "goods.h"
#include "dbscls.h"
#include "src/utils/usings.h"


class RootDB : public object
{
private:
	

	void throw_invalid_argument(const char* dbErrorMessage) const;

public:
	ref<B_tree> m_customers;
	RootDB();
	void initialize() const;

	void addCustomer(ref<CustomerDB> customer);
	void removeCustomer(ref<CustomerDB> customer);
	ref<CustomerDB> getCustomerByName(const wstring_t& name) const;
	void updateCustomer(ref<CustomerDB> customer);
	CustomersDbList allCustomers() const;

	~RootDB() = default;

	METACLASS_DECLARATIONS(RootDB, object);
};
