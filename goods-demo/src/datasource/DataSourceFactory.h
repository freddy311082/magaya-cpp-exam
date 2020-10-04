#pragma once
#include <type_traits>
#include <memory>
#include "src/datasource/db/DBDatasource.h"

enum DataSourceType
{
	DataSourceType_DATABASE
};


template <DataSourceType T> struct DataSourceFactory
{
	template <typename... Args>
	static std::unique_ptr<DataSource> newInstance(Args&&... args)
	{
		return nullptr;
	}
};


template <> struct DataSourceFactory<DataSourceType_DATABASE>
{
	template <typename... Args>
	static std::unique_ptr<DataSource> newInstance(Args&&... args)
	{
		return std::make_unique<DBDataSource>(std::forward<Args>(args)...);
	}
};
