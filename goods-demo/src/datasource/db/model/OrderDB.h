#pragma once
#include "goods.h"
#include "dbscls.h"
#include "datetime.h"
#include  "ShippingAddressDB.h"
#include <list>

class OrderItemDB;
class ProductDB;
class CustomerDB;

class OrderDB : public object
{
	nat8 m_number;
	dbDateTime m_datetime;
	nat1 m_paymentType;
	ShippingAddressDB m_shippingAddress;
	ref<set_member> m_customer;
	ref<B_tree> m_items;
	ref<set_member> m_key;
	nat4 m_lastItemNumber;

	OrderDB(nat8 number,
			const dbDateTime& datetime,
			nat1 paymentType,
			const ShippingAddressDB& shippingAddress,
			ref<CustomerDB> customer);

public:
	nat8 number() const { return m_number; }
	dbDateTime datetime() const { return m_datetime; }
	nat1 paymentType() const{ return m_paymentType; }
	ShippingAddressDB shippingAddress() const { return m_shippingAddress; }
	ref<set_member> key() const { return m_key; }
	ref<set_member> customerKey() const { return m_customer; }
	ref<B_tree> items() const { return m_items; }
	ref<OrderItemDB> getItem(ref<ProductDB> product, real8 quantity) const;
	
	
	
	static ref<OrderDB> create(	nat4 number,
								const dbDateTime& datetime,
								nat1 paymentType,
								const ShippingAddressDB& shippingAddress,
								ref<CustomerDB> customer);
	void addItem(ref<ProductDB> product, real8 quantity);
	void deleteItem(ref<ProductDB> product, real8 quantity);
	
	

	~OrderDB() = default;
	METACLASS_DECLARATIONS(OrderDB, object);
};