#pragma once

#include <memory>
#include <functional>
#include <database.h>
#include <list>
#include <future>
#include <thread>
#include <mutex>
#include <chrono>

#include "src/datasource/DataSource.h"
#include "src/datasource/db/model/RootDB.h"
#include "src/middleware/model/Customer.h"
#include "src/middleware/model/Product.h"


class DataSourceFactory;


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
	
	static constexpr int TIME_TO_CHECK_CONNECTION = 5; // TODO:  move this to a config file

	std::string m_configFilename;
	uint32_t m_dbReconnectSeconds;
	std::thread m_connectionThread;
	std::thread m_timerThread;
	bool m_isConnected = false;
	
	

	template <typename Func, typename... Args>
	void runDbQuery(Func&& func, Args&&... args)
	{
		
		dbConnect();
		ref<RootDB> root;
		m_db->get_root(root);
		root->initialize();
		func(root, std::forward<Args>(args)...);
	}

	
	void dbConnect();
	void dbClose();
	bool isConnected();
	void setIsConnected(bool value);
	void checkDbActivity();
	void updateLastCall();
	int totalSecondsSinceLastCall();

	void validateProduct(const ProductPtr& product);
	CustomerPtr getCustomerByEmailOrPhone(const std::string& email, const std::string& phone);
public:
	DBDataSource(const std::string& configFilename, uint32_t dbReconnectSeconds = 60);
	// Customers
	void addCustomer(const CustomerPtr& customer) override;
	void updateCustomer(const CustomerPtr& customer) override;
	void removeCustomer(const CustomerPtr& customer) override;
	CustomersList allCustomers() override;
	CustomerPtr getCustomerByEmail(const std::string& email) override;
	CustomerPtr getCustomerByPhone(const std::string& phone) override;

	// Products
	void addProduct(const ProductPtr& product) override;
	void removeProduct(const ProductPtr& product) override;
	void updateProduct(const ProductPtr& product) override;
	ProductPtr getProductBySKU(const std::string& sku) override;
	ProductsList allProducts() override;
	
	~DBDataSource();
};

