#pragma once

#include "goods.h"
#include "dbscls.h"
#include "src/utils/usings.h"

class RootDB : public object
{
	ref<B_tree> m_customers;
	ref<B_tree> m_products;

public:
	RootDB();
	void initialize() const;

	// Customers
	void addCustomer(ref<CustomerDB> customer);
	void removeCustomer(ref<CustomerDB> customer);
	void updateCustomer(ref<CustomerDB> customer);
	ref<CustomerDB> getCustomerByName(const wstring_t& name) const;
	CustomersDbList allCustomers() const;

	// Products
	void addProdduct(ref<ProductDB> product);
	void removeProduct(const wstring_t& sku);
	void updateProduct(ref<ProductDB> product);
	ref<ProductDB> getProductBySKU(const wstring_t& sku) const;
	ProductDbList allProducts() const;

	~RootDB() = default;

	METACLASS_DECLARATIONS(RootDB, object);
};
