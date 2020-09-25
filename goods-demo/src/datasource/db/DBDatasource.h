#pragma once

#include <memory>
#include <functional>
#include <database.h>
#include <list>

#include "src/datasource/DataSource.h"
#include "src/datasource/db/model/RootDB.h"
#include "src/middleware/model/Customer.h"
#include "src/middleware/model/Product.h"



class DBDataSource final: public DataSource
{
private:
	std::unique_ptr<database> m_db = std::make_unique<database>();
	std::string m_configFilename;
	bool m_isConnected = false;

	template <typename Func, typename... Args>
	void runDbQuery(Func&& func, Args&&... args)
	{
		try
		{
			if (!m_isConnected)
				dbConnect();

			ref<RootDB> root;
			m_db->get_root(root);
			root->initialize();
			func(root, std::forward<Args>(args)...);

			dbClose();
		} catch (...)
		{
			dbClose();
			throw;
		}
	}

	void dbConnect();
	void dbClose();
	
	
public:
	DBDataSource(const std::string& configFilename);
	
	void addCustomer(const CustomerPtr& customer);
	void deleteCustomer(const CustomerPtr& customer);
	CustomerPtr getCustomerByName(const std::string& name);
	CustomersList  allCustomers();
	
	~DBDataSource();
};

