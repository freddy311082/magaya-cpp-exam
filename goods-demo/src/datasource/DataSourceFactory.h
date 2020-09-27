#pragma once
#include <type_traits>
#include <memory>
#include "src/datasource/db/DBDatasource.h"

enum DataSourceType
{
	DataSourceType_DATABASE
};


class DataSourceFactory final {
public:
	template <DataSourceType ENUM = DataSourceType_DATABASE,
				typename... Args>
	static std::shared_ptr<DataSource> newInstance(Args&&... args)
	{
		return std::make_shared<DBDataSource>(std::forward<Args>(args)...);
	}	
};