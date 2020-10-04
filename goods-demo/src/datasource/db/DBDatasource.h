#pragma once

#include <memory>
#include <database.h>
#include <list>
#include <future>
#include <thread>
#include <mutex>
#include <chrono>

#include "src/datasource/DataSource.h"
#include "src/datasource/db/model/RootDB.h"


class DBDataSource final: public DataSource
{
private:
	
	static std::unique_ptr<database> m_db;
	static std::mutex g_mutex;
	static std::chrono::system_clock::time_point g_lastCall;
	static bool g_keepRunning;
	static std::condition_variable g_keepRunningCond;
	static bool g_unlockChecking;
	static int g_seconds;
	static uint32_t g_activeTransactionsNumber;
	
	static constexpr int TIME_TO_CHECK_CONNECTION = 5; // TODO:  move this to a config file

	std::string m_configFilename;
	std::thread m_connectionThread;
	std::thread m_timerThread;
	bool m_isConnected = false;
	
	

	template <typename Func, typename... Args>
	void runDbQuery(Func&& func, Args&&... args)
	{
		addTransaction();
		try
		{
			dbConnect();
			ref<RootDB> root;
			m_db->get_root(root);
			root->initialize();
			func(root, std::forward<Args>(args)...);
			removeTransaction();
		}
		catch (...)
		{
			removeTransaction();
			throw;
		}
	}

	
	void dbConnect();
	void dbClose();
	bool isConnected();
	void setIsConnected(bool value);
	void checkDbActivity();
	void updateLastCall();
	int totalSecondsSinceLastCall();
	void addTransaction();
	void removeTransaction();
	uint32_t numberOfActiveTransactions();

	CustomerPtr getCustomerByEmailOrPhone(const std::string& email, const std::string& phone);
public:
	DBDataSource(const std::string& configFilename);
	// Customers
	void addCustomer(const CustomerPtr& customer) override;
	void updateCustomer(const CustomerPtr& customer) override;
	void deleteCustomer(const std::string& email) override;
	CustomersList allCustomers() override;
	CustomerPtr getCustomerByEmail(const std::string& email) override;
	CustomerPtr getCustomerByPhone(const std::string& phone) override;

	// Products
	void addProduct(const ProductPtr& product) override;
	void removeProduct(const std::string& sku) override;
	void updateProduct(const ProductPtr& product) override;
	ProductPtr getProductBySKU(const std::string& sku) override;
	ProductsList allProducts() override;

	// Orders
	OrderPtr registerOrder(const CreateOrderParams& orderParams) override;
	uint64_t getNextOrderNumber() override;

	OrdersList allOrdersByCustomer(const std::string& customerEmail) override;
	~DBDataSource();
};

