#pragma once

#include <string>
#include <memory>

class ShippingAddress
{
public:
	ShippingAddress(const std::string& streetAndNumber, 
		const std::string& city, 
		const std::string& state,
		const std::string& country, 
		uint32_t zip_code);

private:
	std::string m_streetAndNumber;
	std::string m_city;
	std::string m_state;
	std::string m_country;
	uint32_t m_zipCode;

public:
	ShippingAddress() = default;

	void setStreetAndNumber(const std::string& streetAndNumber)
	{
		m_streetAndNumber = streetAndNumber;
	}

	void setCity(const std::string& city)
	{
		m_city = city;
	}

	void setState(const std::string& state)
	{
		m_state = state;
	}

	void setCountry(const std::string& country)
	{
		m_country = country;
	}

	void setZipCode(uint32_t zipCode)
	{
		m_zipCode = zipCode;
	}


	std::string streetAndNumber() const
	{
		return m_streetAndNumber;
	}

	std::string city() const
	{
		return m_city;
	}

	std::string state() const
	{
		return m_state;
	}

	std::string country() const
	{
		return m_country;
	}

	uint32_t zipCode() const
	{
		return m_zipCode;
	}

	std::string info() const;
	bool isValid() const;
	std::string toString() const;
};

using ShippingAddressPtr = std::unique_ptr<ShippingAddress>;
