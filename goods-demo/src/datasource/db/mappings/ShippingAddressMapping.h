#pragma once


class ShippingAddressDB;
struct ShippingAddress;


class ShippingAddressMapping
{
public:
	static ShippingAddressDB toDbModel(const ShippingAddress& addr);
	static ShippingAddress toModel(const ShippingAddressDB& addrDb);
};
