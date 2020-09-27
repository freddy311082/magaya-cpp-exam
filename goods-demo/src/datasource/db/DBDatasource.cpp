#include "pch.h"
#include "DBDataSource.h"

#include <filesystem>
#include <sstream>
#include <iostream>


#include "../goods-demo/src/datasource/db/model/RootDB.h"
#include "../goods-demo/src/datasource/db/mappings/CustomerMapping.h"
#include "../goods-demo/src/datasource/db/mappings/ProductMapping.h"

std::unique_ptr<database> DBDataSource::m_db = std::make_unique<database>();
std::chrono::system_clock::time_point DBDataSource::g_lastCall = std::chrono::system_clock::now();
std::mutex DBDataSource::g_mutex = std::mutex();
bool DBDataSource::g_keepRunning = true;
bool DBDataSource::g_unlockChecking = false;
std::condition_variable DBDataSource::g_keepRunningCond = std::condition_variable();
int DBDataSource::g_seconds = TIME_TO_CHECK_CONNECTION;


DBDataSource::DBDataSource(const std::string& configFilename, uint32_t dbReconnectSeconds) :
	DataSource() ,m_configFilename(configFilename + ".cfg"), m_dbReconnectSeconds(dbReconnectSeconds)
{
	if (!std::filesystem::exists(m_configFilename))
	{
		std::stringstream error_str;
		error_str << "Config file " << m_configFilename << " doesn't exists." << std::endl;
		throw std::ios::failure(error_str.str());
	}

	m_connectionThread = std::thread([&](DBDataSource* ds)
	{
		ds->checkDbActivity();
	}, this);

	m_timerThread = std::thread([]()
	{
		while(true)
		{
			std::cout << "Timer Thread: " << g_seconds << " s !!" << std::endl;
			if (!g_keepRunning)
				return; // end thread

			if (--g_seconds == 0)
			{
				g_unlockChecking = true;
				g_keepRunningCond.notify_all();
				g_seconds = TIME_TO_CHECK_CONNECTION;
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	});
}


void DBDataSource::checkDbActivity()
{
	while(g_keepRunning)
	{
		std::mutex lockingSleep;
		std::unique_lock<std::mutex>  lock(lockingSleep);
		g_keepRunningCond.wait(lock, [] {return g_unlockChecking; });
		g_unlockChecking = false;
		std::cout << "Entre a checkDbActivity !!!!" << std::endl;
		std::cout << "Is connected to DB?: " << (m_isConnected ? "True" : "False") << std::endl;		
		if (isConnected())
		{
			if (totalSecondsSinceLastCall() > TIME_TO_CHECK_CONNECTION)
			{
				dbClose();
				std::cout << "Connection closed with DB !!" << std::endl;
			}
		}
	}
}

void DBDataSource::updateLastCall()
{
	std::lock_guard<std::mutex> _(g_mutex);
	g_lastCall = std::chrono::system_clock::now();
}

int DBDataSource::totalSecondsSinceLastCall()
{
	std::lock_guard<std::mutex> _(g_mutex);
	auto now = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(now - g_lastCall).count();
}


void DBDataSource::dbClose()
{
	g_mutex.lock();
	m_db->close();
	g_mutex.unlock();
	setIsConnected(false);
}

bool DBDataSource::isConnected()
{
	std::lock_guard<std::mutex> _(g_mutex);
	return m_isConnected;
}

void DBDataSource::setIsConnected(bool value)
{
	std::lock_guard<std::mutex> _(g_mutex);
	m_isConnected = value;
}

DBDataSource::~DBDataSource()
{
	m_db->close();
	g_keepRunning = false;
	g_unlockChecking = true;
	g_keepRunningCond.notify_all();
	m_timerThread.join();
	m_connectionThread.join();
}


void DBDataSource::dbConnect()
{
	// for multi threading scenario, we need to check this
	if (!isConnected())
	{
		task::initialize(task::normal_stack);
		if (!m_db->open(m_configFilename.c_str()))
		{
			setIsConnected(false);
			throw std::runtime_error("Unable to open connection with the database.");
		}
		std::cout << "Connection opened with DB !!" << std::endl;
		setIsConnected(true);
	}

	updateLastCall();
}

void DBDataSource::addCustomer(const CustomerPtr& customer)
{
	if (customer == nullptr)
		throw std::invalid_argument("Customer cannot be NULL.");

	if (customer->name().empty())
		throw std::invalid_argument("Invalid customer name.");

	if (getCustomerByName(customer->name()) != nullptr)
		throw std::invalid_argument("This customer already exists");
	
	runDbQuery([](ref<RootDB> root,  const CustomerPtr& cust)
	{
		modify(root)->addCustomer(CustomerMapping::toDbModel(*cust));
	}, customer);
}

void DBDataSource::updateCustomer(const CustomerPtr& customer)
{
	if (customer == nullptr)
		throw std::invalid_argument("Customer cannot be NULL.");

	runDbQuery([](ref<RootDB> root, const CustomerPtr& customer)
	{
		modify(root)->updateCustomer(CustomerMapping::toDbModel(*customer));
	}, customer);
}

void DBDataSource::removeCustomer(const CustomerPtr& customer)
{
	if (customer == nullptr)
		throw std::invalid_argument("Customer cannot be NULL.");
	
	runDbQuery([](ref<RootDB> root, const CustomerPtr& customer)->void
	{
		modify(root)->removeCustomer(CustomerMapping::toDbModel(*customer));
	}, customer);
}

CustomerPtr DBDataSource::getCustomerByName(const std::string& name)
{
	if (name.empty())
		throw std::invalid_argument("Invalid customer name.");

	CustomerPtr result;
	runDbQuery([](ref<RootDB> root, const std::string& name , CustomerPtr& result)
	{
		auto customer = root->getCustomerByName(name.c_str());

		if (customer != nullptr)
			result = CustomerMapping::toModel(customer);
		
	}, name, result);

	return result;
}

CustomersList DBDataSource::allCustomers()
{
	CustomersList result;
	runDbQuery([](ref<RootDB> root, CustomersList& allCustomers)
	{
		for (const auto& customerDb: root->allCustomers())
		{
			allCustomers.push_back(CustomerMapping::toModel(customerDb));
		}
	}, result);

	return result;
}

void DBDataSource::validateProduct(const ProductPtr& product)
{
	if (product == nullptr)
		throw std::invalid_argument("Product cannot be NULL.");

	if (product->sku().empty())
		throw std::invalid_argument("SKU value is invalid.");
}

void DBDataSource::addProduct(const ProductPtr& product)
{
	validateProduct(product);

	runDbQuery([](ref<RootDB> root, const ProductPtr& product)
	{
		if (root->getProductBySKU(product->sku().c_str()) != nullptr)
			throw std::invalid_argument("This product already exists");

		auto productDb = ProductMapping::toDbModel(*product);
		modify(root)->addProdduct(productDb);
		std::cout << "Aqui estoy !!" << std::endl;
	}, product);
}

void DBDataSource::removeProduct(const ProductPtr& product)
{
	validateProduct(product);

	runDbQuery([](ref<RootDB> root, const ProductPtr& product)
	{
		modify(root)->removeProduct(product->sku().c_str());
	}, product);
}

void DBDataSource::updateProduct(const ProductPtr& product)
{
	validateProduct(product);

	runDbQuery([](ref<RootDB> root, const ProductPtr& product)
	{
		modify(root)->updateProduct(ProductMapping::toDbModel(*product));
	}, product);
}

ProductPtr DBDataSource::getProductBySKU(const std::string& sku)
{
	ProductPtr result;
	runDbQuery([](ref<RootDB> root, const std::string& sku, ProductPtr& result)
	{
		auto productDb = root->getProductBySKU(sku.c_str());

		if (productDb != nullptr)
			result = ProductMapping::toModel(productDb);
		
	}, sku, result);

	return result;
}

ProductsList DBDataSource::allProducts()
{
	ProductsList result;

	runDbQuery([](ref<RootDB> root, ProductsList& result)
	{
		for (const auto& productDb: root->allProducts())
		{
			result.push_back(ProductMapping::toModel(productDb));
		}
	}, result);
	
	return result;
}
