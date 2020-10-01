#include "pch.h"
#include "DBDataSource.h"

#include <filesystem>
#include <sstream>
#include <iostream>


#include "src/datasource/db/model/RootDB.h"
#include "src/datasource/db/model/CustomerDB.h"
#include "src/datasource/db/model/OrderDB.h"
#include "src/datasource/db/model/OrderItemDB.h"
#include "src/datasource/db/mappings/CustomerMapping.h"
#include "src/datasource/db/mappings/ProductMapping.h"
#include "src/datasource/db/mappings/ShippingAddressMapping.h"
#include "src/datasource/db/mappings/OrderMapping.h"
#include "src/middleware/model/Product.h"
#include "src/middleware/model/Order.h"
#include "src/middleware/model/OrderItem.h"
#include "src/middleware/model/Customer.h"

std::unique_ptr<database> DBDataSource::m_db = std::make_unique<database>();
std::chrono::system_clock::time_point DBDataSource::g_lastCall = std::chrono::system_clock::now();
std::mutex DBDataSource::g_mutex = std::mutex();
bool DBDataSource::g_keepRunning = true;
bool DBDataSource::g_unlockChecking = false;
std::condition_variable DBDataSource::g_keepRunningCond = std::condition_variable();
int DBDataSource::g_seconds = TIME_TO_CHECK_CONNECTION;
uint32_t DBDataSource::g_activeTransactionsNumber = 0;


DBDataSource::DBDataSource(const std::string& configFilename) :
	DataSource() ,m_configFilename(configFilename + ".cfg")
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
		std::cout << "Is connected to DB?: " << (m_isConnected ? "True" : "False") << std::endl;		
		if (isConnected())
		{
			if (totalSecondsSinceLastCall() > TIME_TO_CHECK_CONNECTION && numberOfActiveTransactions() == 0)
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

void DBDataSource::addTransaction()
{
	std::lock_guard<std::mutex> _(g_mutex);
	g_activeTransactionsNumber++;
}

void DBDataSource::removeTransaction()
{
	std::lock_guard<std::mutex> _(g_mutex);
	g_activeTransactionsNumber--;
}

uint32_t DBDataSource::numberOfActiveTransactions()
{
	std::lock_guard<std::mutex> _(g_mutex);
	return g_activeTransactionsNumber;
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
	runDbQuery([](ref<RootDB> root,  const CustomerPtr& customer)
	{
		modify(root)->addCustomer(CustomerMapping::toDbModel(*customer));
	}, customer);
}

void DBDataSource::updateCustomer(const CustomerPtr& customer)
{
	runDbQuery([](ref<RootDB> root, const CustomerPtr& customer)
	{
		modify(root)->updateCustomer(CustomerMapping::toDbModel(*customer));
	}, customer);
}

void DBDataSource::removeCustomer(const CustomerPtr& customer)
{	
	runDbQuery([](ref<RootDB> root, const CustomerPtr& customer)->void
	{
		modify(root)->removeCustomer(CustomerMapping::toDbModel(*customer));
	}, customer);
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

CustomerPtr DBDataSource::getCustomerByEmail(const std::string& email)
{
	return getCustomerByEmailOrPhone(email, "");
}

CustomerPtr DBDataSource::getCustomerByPhone(const std::string& phone)
{
	return getCustomerByEmailOrPhone("", phone);
}

CustomerPtr DBDataSource::getCustomerByEmailOrPhone(const std::string& email, 
													const std::string& phone)
{
	if (email.empty() && phone.empty())
		return nullptr;

	CustomerPtr customer;
	runDbQuery([](
		ref<RootDB> root,
		const std::string& email, 
		const std::string& phone,
		CustomerPtr& customer)
	{
		auto customerDb = root->getCustomerByPhoneEmail(email.c_str(), phone.c_str());

		if (customerDb != nullptr) // Customer was found
			customer = CustomerMapping::toModel(customerDb);
	}, email, phone, customer);

	return customer;
}

void DBDataSource::addProduct(const ProductPtr& product)
{
	runDbQuery([](ref<RootDB> root, const ProductPtr& product)
	{
		auto productDb = ProductMapping::toDbModel(*product);
		modify(root)->addProduct(productDb);
	}, product);
}

void DBDataSource::removeProduct(const std::string& sku)
{
	runDbQuery([](ref<RootDB> root, const std::string& sku)
	{
		modify(root)->removeProduct(sku.c_str());
	}, sku);
}

void DBDataSource::updateProduct(const ProductPtr& product)
{
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

OrderPtr DBDataSource::registerOrder(const CreateOrderParams& orderParams)
{
	OrderPtr order;
	runDbQuery([](
		ref<RootDB> root, 
		const CreateOrderParams& params,
		OrderPtr& result)
	{
		ref<CustomerDB> customer = root->getCustomerByEmail(params.customerEmail.c_str());
		if (customer == nullptr)
			throw std::invalid_argument("Invalid customer. Order cannot be created.");

		nat1 paymentType = static_cast<nat1>(params.paymentType);
		auto address = ShippingAddressMapping::toDbModel(params.shippingAddress);
		auto order = modify(root)->createOrder(paymentType, address);

		OrderItemsDBProdPairList oiProdList;
		for (const auto& item: params.items)
		{
			ref<ProductDB> productDb = root->getProductBySKU(item.productSKU.c_str());
			if (productDb.is_nil())
				throw std::invalid_argument("This order has an invalid product.");
			
			auto itemDb = modify(order)->addItem(item.productSKU.c_str(), item.quantity);
			oiProdList.push_back({productDb, itemDb});
		}

		modify(customer)->addOrder(order);
		result = OrderMapping::toModel(order, oiProdList);
		
	}, orderParams, order);

	return order;
}

uint64_t DBDataSource::getNextOrderNumber()
{
	uint64_t result = 0;

	runDbQuery([](ref<RootDB> root, uint64_t& result)
	{
		result = modify(root)->nextOrderNumber();
	}, result);

	return result;
}
