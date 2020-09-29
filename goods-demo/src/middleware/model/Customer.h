#pragma once

#include <string>
#include <list>

#include "ShippingAddress.h"

class Customer
{
	std::string m_name;
	std::string m_phone;
	std::string m_email;
	ShippingAddress m_shippingAddress;

public:
	std::string name() const
	{
		return m_name;
	}

	std::string phone() const
	{
		return m_phone;
	}

	std::string email() const
	{
		return m_email;
	}

	ShippingAddress shippingAddress() const
	{
		return m_shippingAddress;
	}

	Customer(const std::string& name, 
	         const std::string& phone, 
	         const std::string& email, 
	         const ShippingAddress& shippingAddress);
	Customer() = default;

	

	std::string info();
};


