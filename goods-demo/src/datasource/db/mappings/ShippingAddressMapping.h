#pragma once


struct ShippingAddressDB;
struct ShippingAddress;


class ShippingAddressMapping
{
public:
	static ShippingAddressDB toDbModel(const ShippingAddress& addr);
	static ShippingAddress toModel(const ShippingAddressDB& addrDb);
};
