#pragma once

#include <memory>

#include "model.h"

class DataSource
{
public:
	/*
	 * The idea behind this method is allow the user of this class to create more datasource nad without any change
	 * keep using this method as the DataSource constructor.
	 */

	// Customers
	virtual void addCustomer(const CustomerPtr& customer)  = 0;
	virtual void updateCustomer(const CustomerPtr& customer)  = 0;
	virtual void removeCustomer(const CustomerPtr& customer)  = 0;
	virtual CustomersList allCustomers()  = 0;
	virtual CustomerPtr getCustomerByEmail(const std::string& email) = 0;
	virtual CustomerPtr getCustomerByPhone(const std::string& phone) = 0;


	// Products
	virtual void addProduct(const ProductPtr& product)  = 0;
	virtual void removeProduct(const ProductPtr& product)  = 0;
	virtual void updateProduct(const ProductPtr& product)  = 0;
	virtual ProductPtr getProductBySKU(const std::string& sku)  = 0;
	virtual ProductsList allProducts()  = 0;

	virtual ~DataSource() = default;
};

