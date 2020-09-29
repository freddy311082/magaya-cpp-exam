#pragma once

#include "goods.h"
#include "dbscls.h"
#include "src/utils/usings.h"
#include "src/utils/enums.h"
#include "ConfigDB.h"


class RootDB : public object
{
	ref<B_tree> m_customers;
	ref<B_tree> m_products;
	ref<ConfigDB> m_config;
	
public:
	RootDB();
	void initialize() const;
	nat8 lastOrderNumber() const { m_config->lastOrderNumber(); }
	nat8 nextOrderNumber();

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
	ref<OrderDB> createOrderForCustomer(
		ref<CustomerDB> customer, 
		nat1 paymentType,
		ShippingAddressDBPtr shippingAddress);

	~RootDB() = default;

	METACLASS_DECLARATIONS(RootDB, object);
};
