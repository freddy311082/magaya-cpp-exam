#pragma once

#include <string>
#include <memory>
#include <list>

#include "ShippingAddress.h"

struct Customer;
using CustomerPtr = std::unique_ptr<Customer>;
using CustomersList = std::list<CustomerPtr>;


struct Customer
{
	Customer(const std::string& name, const std::string& phone, const std::string& email, const ShippingAddress& shippingAddress);

	std::string name;
	std::string phone;
	std::string email;
	ShippingAddress shippingAddress;

	std::string info();
};


