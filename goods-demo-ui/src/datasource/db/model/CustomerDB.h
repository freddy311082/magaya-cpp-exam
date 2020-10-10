#pragma once
#include "goods.h"
#include "dbscls.h"

#include "ShippingAddressDB.h"
#include "src/utils/usings.h"

class CustomerDB : public object
{
protected:
	wstring_t m_name;
	wstring_t m_phone;
	wstring_t m_email;
	ShippingAddressDB m_shippingAddress;
protected:
	ref<set_owner> m_orders;
	ref<set_member> m_key;
	nat8 m_numberOfOrders;
	
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
	nat8 numberOfOrders() const { return m_numberOfOrders; }
	static ref<CustomerDB> create(const wstring_t& name,
		const wstring_t& phone,
		const wstring_t& email,
		const ShippingAddressDB& shippingAddress);
	void update(const wstring_t& name,
		const wstring_t& phone,
		const wstring_t& email,
		const ShippingAddressDB& shippingAddress);
	void addOrder(ref<OrderDB> order);
	ref<OrderDB> getOrder(nat8 orderNumber) const;
	void getOrdersInto(OrdersDBList& orders) const;
	OrdersDBList allOrders() const;
	bool canBeDeleted() const;
	void deleteOrder(ref<OrderDB> order);
	void updateProductSkuInOrders(const wstring_t& originalSku, const wstring_t& newSku);
};


