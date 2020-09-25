#pragma once

#include <object.h>


class CustomerDB;

class RootDB : public object
{
private:
	ref<B_tree> m_products;
	ref<B_tree> m_customers;

	RootDB();

public:
	static ref<RootDB> create();
	void initialize() const;
	void addCustomer(ref<CustomerDB> customer);
	~RootDB() = default;

	ref<CustomerDB> getCustomer(const wstring_t& name);

	METACLASS_DECLARATIONS(RootDB, object);
};
