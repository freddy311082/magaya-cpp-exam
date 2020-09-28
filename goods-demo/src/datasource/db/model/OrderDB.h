#pragma once
#include "goods.h"
#include "dbscls.h"
#include "datetime.h"
#include  "ShippingAddressDB.h"

class OrderDB : public set_owner
{
private:
	nat4 m_number;
	dbDateTime m_datetime;
	nat1 m_paymentType;
	ShippingAddressDB m_shippingAddress;
	ref<set_member> m_customer;
	ref<set_member> m_key;

	OrderDB(nat4 number,
			const dbDateTime& datetime,
			nat1 paymentType,
			const ShippingAddressDB& shippingAddress);

public:
	static ref<OrderDB> create(	nat4 number,
								const dbDateTime& datetime,
								nat1 paymentType,
								const ShippingAddressDB& shippingAddress);

	~OrderDB() = default;

	METACLASS_DECLARATIONS(OrderDB, set_owner);
};