#pragma once

#include "goods.h"
#include "dbscls.h"
#include "src/utils/usings.h"
#include "ConfigDB.h"

class RootDB : public object
{
	ref<B_tree> m_customers;
	ref<B_tree> m_products;
	ref<ConfigDB> m_config;
	
public:
	RootDB();
	void initialize() const;

	// Customers
	void addCustomer(ref<CustomerDB> customer);
	void removeCustomer(ref<CustomerDB> customer);
	void updateCustomer(ref<CustomerDB> customer);
	ref<CustomerDB> getCustomerByPhoneOrEmail(const wstring_t& email, const wstring_t& phone) const;
	CustomersDbList allCustomers() const;

	// Products
	void addProduct(ref<ProductDB> product);
	void removeProduct(const wstring_t& sku);
	void updateProduct(ref<ProductDB> product);
	ref<ProductDB> getProductBySKU(const wstring_t& sku) const;
	ProductDbList allProducts() const;

	// Orders

	~RootDB() = default;

	METACLASS_DECLARATIONS(RootDB, object);
};
