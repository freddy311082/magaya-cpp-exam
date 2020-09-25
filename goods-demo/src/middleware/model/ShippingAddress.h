#pragma once

#include <string>
#include <memory>

struct ShippingAddress
{
	std::string streetAndNumber;
	std::string city;
	std::string state;
	std::string country;
	uint32_t zipCode;

	std::string info() const;
};

using ShippingAddressPtr = std::unique_ptr<ShippingAddress>;
