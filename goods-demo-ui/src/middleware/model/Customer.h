﻿#pragma once

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
	std::string name() const { return m_name; }
	std::string phone() const { return m_phone; }
	const std::string email() const { return m_email; }
	const ShippingAddress& shippingAddress() const { return m_shippingAddress; }

	void setName(const std::string& name) { m_name = name; }
	void setPhone(const std::string& phone) { m_phone = phone; }
	void setEmail(const std::string& email) { m_email = email; }
	void setShippingAddress(const ShippingAddress& shipping_address) { m_shippingAddress = shipping_address; }

	Customer(const std::string& name,  
	         const std::string& phone, 
	         const std::string& email, 
	         const ShippingAddress& shippingAddress);
	Customer() = default;

	bool isValid() const;

	std::string info();
};


