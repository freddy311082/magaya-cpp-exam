#pragma once
#include <type_traits>
#include <memory>

#include "model.h"

class DataSource
{
public:

	/*
	 * The idea behind this method is allow the user of this class to create more datasource nad without any change
	 * keep using this method as the DataSource constructor.
	 */
	template <	typename T,
				//typename = std::is_class<T>::value_type() && std::is_base_of<DataSource, T>::value_type(),
				typename... Args>
	static std::unique_ptr<T> newInstance(Args&&... args)
	{
		return std::make_unique<T>(std::forward(args)...);
	}

	//virtual void addCustomer(CustomerPtr&& customer) = 0;
	//virtual void addProduct(ProductPtr&& product) = 0;

	virtual ~DataSource() = default;
};

