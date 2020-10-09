#pragma once
#include "goods.h"
#include "dbscls.h"
#include "datetime.h"
#include "ShippingAddressDB.h"
#include "src/utils/usings.h"
#include <unordered_map>



class OrderDB : public object
{
	nat8 m_number;
	dbDateTime m_datetime;
	nat1 m_paymentType;
	ShippingAddressDB m_shippingAddress;
	ref<set_owner> m_items;
	ref<set_member> m_key;
	nat4 m_lastItemNumber;

	OrderDB(nat8 number,
			const dbDateTime& datetime,
			nat1 paymentType,
			const ShippingAddressDB& shippingAddress);

public:
	nat8 number() const { return m_number; }
	dbDateTime datetime() const { return m_datetime; }
	nat1 paymentType() const{ return m_paymentType; }
	ShippingAddressDB shippingAddress() const { return m_shippingAddress; }
	ref<set_member> key() const { return m_key; }
	OrderItemDbList items() const;
	ref<OrderItemDB> getItem(const wstring_t& productSKU, real8 quantity) const;
	
	
	
	
	static ref<OrderDB> create(	nat4 number,
								const dbDateTime& datetime,
								nat1 paymentType,
								const ShippingAddressDB& shippingAddress);
	ref<OrderItemDB> addItem(const wstring_t& productSKU, real8 quantity);
	void deleteItem(const wstring_t& productSKU, real8 quantity);
	std::list<wstring_t> allProductSKUs() const;
	
	

	~OrderDB() = default;
	METACLASS_DECLARATIONS(OrderDB, object);
};