#include "pch.h"
#include "DBDataSource.h"

#include <filesystem>
#include <sstream>

#include "../goods-demo/src/datasource/db/model/RootDB.h"
#include "../goods-demo/src/datasource/db/mappings/CustomerMapping.h"
#include "../goods-demo/src/datasource/db/mappings/ShippingAddressMapping.h"


DBDataSource::DBDataSource(const std::string& configFilename) :
	DataSource() ,m_configFilename(configFilename + ".cfg")
{
	if (!std::filesystem::exists(m_configFilename))
	{
		std::stringstream error_str;
		error_str << "Config file " << m_configFilename << " doesn't exists." << std::endl;
		throw std::ios::failure(error_str.str());
	}
}


void DBDataSource::dbClose()
{
	m_isConnected = false;
	m_db->close();
}

DBDataSource::~DBDataSource()
{
	m_db->close();
}


void DBDataSource::dbConnect()
{
	// for multi threading scenario, we need to check this
	//task::initialize(task::normal_stack);
	if (!m_db->open(m_configFilename.c_str()))
	{
		m_isConnected = false;
		throw std::runtime_error("Unable to open connection with the database.");
	}
	
	m_isConnected = true;
}

void DBDataSource::addCustomer(const CustomerPtr& customer)
{
	if (customer == nullptr)
		throw std::invalid_argument("Customer cannot be NULL.");

	if (customer->name.empty())
		throw std::invalid_argument("Invalid customer name.");
	
	runDbQuery([](ref<RootDB> root,  const CustomerPtr& cust)
	{
		modify(root)->addCustomer(CustomerMapping::toDbModel(*cust));
	}, customer);
}

void DBDataSource::deleteCustomer(const CustomerPtr& customer)
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
