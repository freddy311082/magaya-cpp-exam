#pragma once
#include <string>
#include <functional>
#include <memory>
#include "src/datasource/DataSourceFactory.h"

class Service
{
	std::unique_ptr<DataSource> m_dataSource;
	static std::unique_ptr<Service> m_singleton;
	
public:
	static const std::string g_configFile;
	static Service& instance();
	Service();
	
	void addCustomer(const Customer& customer);
	void deleteCustomer(const std::string& email);
	CustomersList allCustomers();
	bool emailCustomerExists(const std::string& email);
	bool phoneCustomerExists(const std::string& phone);

	void addProduct(const Product& product);
	ProductsList allProducts();
	void deleteProduct(const std::string& sku);
	bool existsProductSKU(const std::string& sku);

	void addOrder(const CreateOrderParams& orderParams);
	OrderPtr getOrder(uint32_t number, const std::string& customerEmail);
	OrdersList allOrdersFromCustomer(const std::string& email);
};

