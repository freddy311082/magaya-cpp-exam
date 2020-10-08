#include "pch.h"
#include <cstdlib>
#include "Service.h"
#include "src/middleware/model/Customer.h"
#include "src/middleware/model/Product.h"
#include "src/middleware/model/Order.h"
#include "src/middleware/model/OrderItem.h"

using namespace std;

const string Service::g_configFile = "C:\\goods\\server.cfg"; // TODO: The best idea here is having this in a config file
unique_ptr<Service> Service::m_singleton = nullptr;

Service& Service::instance()
{
	static std::once_flag oneFlag;

	std::call_once(oneFlag, [&]() {
		m_singleton = make_unique<Service>();
	});

	return *m_singleton;
}

Service::Service()
{
	
	m_dataSource = DataSourceFactory<DataSourceType_DATABASE>::newInstance(g_configFile);
}

void  Service::addCustomer(const Customer& customer)
{
	if (customer.email().empty() || customer.phone().empty())
		throw invalid_argument("Invalid customer: Email or Phone are not valid.");

	m_dataSource->addCustomer(make_unique<Customer>(customer));
}

void Service::deleteCustomer(const string& email)
{
	if (email.empty())
		throw invalid_argument("Invalid customer email.");

	m_dataSource->deleteCustomer(email);
}


CustomersList Service::allCustomers()
{
	return m_dataSource->allCustomers();
}

bool Service::emailCustomerExists(const std::string& email)
{
	if (email.empty())
		throw std::invalid_argument("Invalid Email value. It cannot be empty.");
	
	return m_dataSource->getCustomerByEmail(email) != nullptr;
}

bool Service::phoneCustomerExists(const std::string& phone)
{
	if (phone.empty())
		throw std::invalid_argument("Invalid Phone value. It cannot be empty.");
	
	return m_dataSource->getCustomerByPhone(phone) != nullptr;
}

void Service::addProduct(const Product& product)
{
	if (product.sku().empty())
		throw std::invalid_argument("Invalid Product. The SKU value cannot no be empty.");

	if (product.price() < 0 || product.weight() < 0)
		throw std::invalid_argument("Invalid Product. Price and Weight must be positive values.");

	m_dataSource->addProduct(std::make_unique<Product>(product));
}

ProductsList Service::allProducts()
{
	return m_dataSource->allProducts();
}

void Service::deleteProduct(const std::string& sku)
{
	if (sku.empty())
		throw std::invalid_argument("Invalid SKU. It cannot be empty.");

	m_dataSource->deleteProduct(sku);
}

bool Service::existsProductSKU(const std::string& sku)
{
	if (sku.empty())
		throw std::invalid_argument("Invalid SKU. It cannot be empty.");

	return m_dataSource->getProductBySKU(sku) != nullptr;
}

void Service::addOrder(const CreateOrderParams& orderParams)
{
	if (orderParams.customerEmail.empty())
		throw std::invalid_argument("Customer email is not valid.");

	if (!orderParams.shippingAddress.isValid())
		throw std::invalid_argument("The shipping address is not valid.");

	if (orderParams.items.empty())
		throw std::invalid_argument("The order at least needs one item.");
	
	m_dataSource->registerOrder(orderParams);
}

OrderPtr Service::getOrder(uint32_t number, const std::string& customerEmail)
{
	if (customerEmail.empty())
		std::invalid_argument("Invalid customer email.");
	
	m_dataSource->getOrder(number, customerEmail);
}
