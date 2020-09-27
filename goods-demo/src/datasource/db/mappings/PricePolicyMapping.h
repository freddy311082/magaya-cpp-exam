#pragma once

class PricePolicyDB;
class PricePolicy;

class PricePolicyMapping
{
public:
	static PricePolicyDB toDbModel(const PricePolicy& customer);
	static PricePolicy toModel(const PricePolicyDB& customerDb);
};
