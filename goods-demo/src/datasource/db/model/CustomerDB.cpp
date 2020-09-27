#include "pch.h"
#include "CustomerDB.h"

CustomerDB::CustomerDB(const wstring_t&	name,
	const wstring_t& phone,
	const wstring_t& email,
	const ShippingAddressDB& shippingAddress) :
	object(self_class),
	m_name(name),
	m_phone(phone),
	m_email(email),
	m_shippingAddress(shippingAddress)
{
	char* _name = m_name.getChars();
	m_key = set_member::create(this, _name);
	delete[] _name;
}

ref<CustomerDB> CustomerDB::create(const wstring_t&	name,
	const wstring_t& phone,
	const wstring_t& email,
	const ShippingAddressDB& shippingAddress)
{
	return NEW CustomerDB(name, phone, email, shippingAddress);
}

field_descriptor& CustomerDB::describe_components()
{
	return	FIELD(m_name),
		FIELD(m_phone),
		FIELD(m_email),
		FIELD(m_key),
		FIELD(m_shippingAddress);
}

void CustomerDB::update(const wstring_t& name, const wstring_t& phone, const wstring_t& email,
	const ShippingAddressDB& shippingAddress)
{
	m_name = name;
	m_phone = phone;
	m_email = email;
	m_shippingAddress = shippingAddress;
}


REGISTER(CustomerDB, object, pessimistic_scheme);