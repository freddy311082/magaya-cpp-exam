#pragma once
#include "goods.h"
#include "dbscls.h"
#include <list>

#include "ShippingAddressDB.h"

class CustomerDB : public object
{
protected:
	wstring_t m_name;
	wstring_t m_phone;
	wstring_t m_email;
	ShippingAddressDB m_shippingAddress;
	ref<set_owner> m_orders;
	ref<set_member> m_key;
	
	CustomerDB(const wstring_t&			name,
		const wstring_t&				phone,
		const wstring_t&				email,
		const ShippingAddressDB&		shippingAddress);
public:
	METACLASS_DECLARATIONS(CustomerDB, object);

	wstring_t name() const { return m_name; }
	wstring_t phone() const { return m_phone; }
	wstring_t email() const { return m_email; }
	const ShippingAddressDB& shippingAddress() const { return m_shippingAddress; }
	ref<set_member> key() const { return m_key; }
	
	static ref<CustomerDB> create(const wstring_t& name,
		const wstring_t& phone,
		const wstring_t& email,
		const ShippingAddressDB& shippingAddress);
	void update(const wstring_t& name,
		const wstring_t& phone,
		const wstring_t& email,
		const ShippingAddressDB& shippingAddress);
};


