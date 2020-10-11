#include "pch.h"
#include "DBDataSource.h"

#include <filesystem>
#include <sstream>
#include <iostream>


#include "src/datasource/db/model/RootDB.h"
#include "src/datasource/db/model/CustomerDB.h"
#include "src/datasource/db/model/OrderDB.h"
#include "src/datasource/db/model/OrderItemDB.h"
#include "src/datasource/db/model/ProductDB.h"
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
	DataSource() ,m_configFilename(configFilename)
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

void DBDataSource::testConnection()
{
	dbConnect();
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
	try
	{
		// dbClose();
	}
	catch (...)
	{
		// TODO: sometimes there is an exception here. I need to check here.
	}
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
			throw std::ios_base::failure("Unable to open connection with the database.");
		}
		std::cout << "Connection opened with DB !!" << std::endl;
		setIsConnected(true);
	}

	updateLastCall();
}

void DBDataSource::addCustomer(const CustomerPtr& customer)
{
	executeDbQuery([](ref<RootDB> root,  const CustomerPtr& customer)
	{
		modify(root)->addCustomer(CustomerMapping::toDbModel(*customer));
	}, customer);
}

void DBDataSource::updateCustomer(const std::string& email, const CustomerPtr& customer)
{
	executeDbQuery([](ref<RootDB> root, const std::string& email,  const CustomerPtr& customer)
	{
		modify(root)->updateCustomer(email.c_str(), CustomerMapping::toDbModel(*customer));
	}, email, customer);
}

void DBDataSource::deleteCustomer(const std::string& email)
{	
	executeDbQuery([](ref<RootDB> root, const std::string& email)->void
	{
		modify(root)->deleteCustomer(email.c_str());
	}, email);
}

CustomersList DBDataSource::allCustomers()
{
	CustomersList result;
	executeDbQuery([](ref<RootDB> root, CustomersList& allCustomers)
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
	CustomerPtr customer;
	executeDbQuery([](ref<RootDB> root, const std::string& email, CustomerPtr& customer)
	{
		auto customerDb = root->getCustomerByEmail(email.c_str());
		customer = customerDb.is_nil() ? nullptr : CustomerMapping::toModel(customerDb);
	}, email, customer);

	return customer;
}

CustomerPtr DBDataSource::getCustomerByPhone(const std::string& phone)
{
	CustomerPtr customer;
	executeDbQuery([](ref<RootDB> root, const std::string& phone, CustomerPtr& customer)
	{
		auto customerDb = root->getCustomerByPhone(phone.c_str());
		customer = customerDb.is_nil() ? nullptr : CustomerMapping::toModel(customerDb);
	}, phone, customer);

	return customer;
}


void DBDataSource::addProduct(const ProductPtr& product)
{
	executeDbQuery([](ref<RootDB> root, const ProductPtr& product)
	{
		auto productDb = ProductMapping::toDbModel(*product);
		modify(root)->addProduct(productDb);
	}, product);
}

void DBDataSource::deleteProduct(const std::string& sku)
{
	executeDbQuery([](ref<RootDB> root, const std::string& sku)
	{
		auto product =root->getProductBySKU(sku.c_str());

		if (product == nullptr)
			throw std::invalid_argument("Product not found.");

		if (!product->canBeDeleted())
			throw std::invalid_argument("This product cannot been deleted cause it has been ordered.");
		
		modify(root)->deleteProduct(product);
	}, sku);
}

void DBDataSource::updateProduct(const std::string& originalSku, const ProductPtr& product)
{
	executeDbQuery([](ref<RootDB> root, const std::string& originalSku, const ProductPtr& product)
	{
		modify(root)->updateProduct(originalSku.c_str(), ProductMapping::toDbModel(*product));
	}, originalSku, product);
}

ProductPtr DBDataSource::getProductBySKU(const std::string& sku)
{
	ProductPtr result;
	executeDbQuery([](ref<RootDB> root, const std::string& sku, ProductPtr& result)
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

	executeDbQuery([](ref<RootDB> root, ProductsList& result)
	{
		for (const auto& productDb: root->allProducts())
		{
			result.push_back(ProductMapping::toModel(productDb));
		}
	}, result);
	
	return result;
}

void DBDataSource::registerProductUse(const OrderItemsDBProdPairList& oiProdPairs)
{
	for (const auto item: oiProdPairs)
	{
		modify(item.productDb)->registerUse();
	}
}

OrderPtr DBDataSource::registerOrder(const CreateOrderParams& orderParams)
{
	OrderPtr order;
	executeDbQuery([](
		ref<RootDB> root, 
		const CreateOrderParams& params,
		DBDataSource* ds,
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

		ds->registerProductUse(oiProdList);
		
		result = OrderMapping::toModel(order, oiProdList, customer->email().getChars());
		
		
	}, orderParams, this, order);

	return order;
}

uint64_t DBDataSource::getNextOrderNumber()
{
	uint64_t result = 0;

	executeDbQuery([](ref<RootDB> root, uint64_t& result)
	{
		result = modify(root)->nextOrderNumber();
	}, result);

	return result;
}

OrdersList DBDataSource::allOrdersByCustomer(const std::string& customerEmail)
{
	OrdersList result;

	executeDbQuery([&](ref<RootDB> root, OrdersList& orders)
	{
		ref<CustomerDB> customerDb = root->getCustomerByEmail(customerEmail.c_str());
		if (customerDb.is_nil())
			throw std::invalid_argument("This customer doesn't exists.");
		
		for (const auto& orderDb: root->allOrdersFromCustomer(customerEmail.c_str()))
		{
			result.push_back(OrderMapping::toModel(
					orderDb, 
					root->orderItemDBPairs(orderDb),
				customerDb->email().getChars()
				)
			);
		}
	}, result);
	
	return result;
}

OrderPtr DBDataSource::getOrder(uint64_t number, const std::string& customerEmail)
{
	OrderPtr result;

	executeDbQuery([](ref<RootDB> root, uint64_t number, 
		const std::string& customerEmail, OrderPtr& result)
	{
		ref<OrderDB> orderDb = root->getOrder(number, customerEmail.c_str());
		result = OrderMapping::toModel(
			orderDb,
			root->orderItemDBPairs(orderDb),
			customerEmail);
	}, number, customerEmail, result);
	
	return result;
}

void DBDataSource::deleteOrder(uint64_t number, const std::string& customerEmail)
{
	executeDbQuery([](ref<RootDB> root, uint64_t number, const std::string& customerEmail)
	{
		auto customerDb = root->getCustomerByEmail(customerEmail.c_str());

		if (customerDb == nullptr)
			throw std::invalid_argument("Invalid email address. Customer not found.");

		auto orderDb = customerDb->getOrder(number);
		if (orderDb == nullptr)
			throw std::invalid_argument("Order not found.");


		for (const auto& sku: orderDb->allProductSKUsPerItem())
		{
			auto productDb = root->getProductBySKU(sku);

			if (productDb != nullptr)
				modify(productDb)->unregisterUse();
		}


		modify(customerDb)->deleteOrder(orderDb);
		
	}, number, customerEmail);
}

OrdersList DBDataSource::allOrders()
{
	OrdersList result;

	executeDbQuery([](ref<RootDB> root, OrdersList& result)
	{
		for (auto custDb: root->allCustomers())
		{
			for (auto orderDb: custDb->allOrders())
				result.push_back(OrderMapping::toModel(
					orderDb, 
					root->orderItemDBPairs(orderDb),
					custDb->email().getChars()));
		}
	},result);

	return result;
}
