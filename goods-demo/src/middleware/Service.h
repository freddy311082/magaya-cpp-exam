#pragma once
#include <string>
#include <functional>
#include "src/datasource/DataSourceFactory.h"


class Service
{
public:
	Service(const std::string& configFilePath);

	enum class StatusCode
	{
		OK,
		FAIL
	};
	
	struct Status
	{
		StatusCode result;
		std::string errorMsg;
	};
	
	Status addCustomer(const CustomerPtr& customer);
	Status deleteCustomer(const std::string& email);


private:
	std::unique_ptr<DataSource> m_dataSource;

	template <typename Func, typename... Args>
	Status dataSourceCall(Func&& func, Args&&... args)
	{
		try
		{
			func(this, std::forward<Args>(args)...);
		}
		catch (std::exception& error)
		{
			return { StatusCode::FAIL, error.what() };
		}
		return { StatusCode::OK, "" };
	}
};

