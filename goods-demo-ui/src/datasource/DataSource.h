#pragma once

#include <memory>
#include <string>
#include "src/utils/usings.h"
#include "src/middleware/model/CreateOrderParams.h"

class DataSource
{
public:
	/*
	 * The idea behind this method is allow the user of this class to create more datasource nad without any change
	 * keep using this method as the DataSource constructor.
	 */

	/*
	 * This method MUST throw std:::ios_base_failure exception in case the connection cannot
	 * be established.
	 */
	virtual void testConnection() = 0;

	// Customers
	virtual void addCustomer(const CustomerPtr& customer)  = 0;
	virtual void updateCustomer(const std::string& email, const CustomerPtr& customerUpdates)  = 0;
	virtual void deleteCustomer(const std::string& email)  = 0;
	virtual CustomersList allCustomers()  = 0;
	virtual CustomerPtr getCustomerByEmail(const std::string& email) = 0;
	virtual CustomerPtr getCustomerByPhone(const std::string& phone) = 0;


	// Products
	virtual void addProduct(const ProductPtr& product)  = 0;
	virtual void deleteProduct(const std::string& sku)  = 0;
	virtual void updateProduct(const ProductPtr& product)  = 0;
	virtual ProductPtr getProductBySKU(const std::string& sku)  = 0;
	virtual ProductsList allProducts()  = 0;

	// Orders
	virtual OrderPtr registerOrder(const CreateOrderParams& orderParams) = 0;
	virtual uint64_t getNextOrderNumber() = 0;
	virtual OrdersList allOrdersByCustomer(const std::string& customerEmail) = 0;
	virtual OrderPtr getOrder(uint64_t number, const std::string& customerEmail) = 0;
	virtual void deleteOrder(uint64_t number, const std::string& customerEmail) = 0;
	
	virtual ~DataSource() = default;
};

