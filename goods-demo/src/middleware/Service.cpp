#include "pch.h"
#include "Service.h"
#include "src/middleware/model/Customer.h"

Service::Service(const std::string& configFilePath)
{
	
	m_dataSource = DataSourceFactory<DataSourceType_DATABASE>::newInstance(configFilePath);
}

Service::Status Service::addCustomer(const CustomerPtr& customer)
{

	return dataSourceCall([](Service* _this, const CustomerPtr& customer)
	{
		if (customer->email().empty() || customer->phone().empty())
			throw std::invalid_argument("Invalid customer: Email or Phone are not valid.");
		_this->m_dataSource->addCustomer(customer);
	}, customer);
}

Service::Status Service::deleteCustomer(const std::string& email)
{
	return dataSourceCall([](Service* _this, const std::string& email)
	{
		if (email.empty())
			throw std::invalid_argument("Invalid customer email.");

		_this->m_dataSource->deleteCustomer(email);
	}, email);
}
