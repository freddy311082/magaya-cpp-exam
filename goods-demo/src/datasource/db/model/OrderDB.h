#pragma once
#include "goods.h"
#include "dbscls.h"
#include "datetime.h"

class ShippingAddressDB;

class OrderDB : public set_owner
{
private:
	nat4						m_number;
	dbDateTime					m_datetime;
	nat1						m_paymentType;
	ref<ShippingAddressDB>		m_shippingAddress;
	ref<set_member>				m_orderItems;

	OrderDB(nat4					number,
			const dbDateTime&		datetime,
			nat1					paymentType,
			ref<ShippingAddressDB>	shippingAddress);

public:
	static ref<OrderDB> create(	nat4 number,
								const dbDateTime& datetime,
								nat1 paymentType,
								ref<ShippingAddressDB> shippingAddress);

	~OrderDB() = default;

	METACLASS_DECLARATIONS(OrderDB, set_owner);
};