﻿#pragma once

#include "goods.h"
#include "dbscls.h"
#include "src/utils/usings.h"
#include "src/utils/enums.h"
#include "ConfigDB.h"
#include <unordered_set>
#include <type_traits>


class RootDB : public object
{
	ref<B_tree> m_customers;
	ref<B_tree> m_products;
	ref<ConfigDB> m_config;
	
	ref<CustomerDB> getCustomer(const std::stringstream& query) const;

	std::string buildProdutSKUsQueryFrom(const std::list<wstring_t>& skuList) const;
	std::string buildProdutSKUsQueryFrom(const std::unordered_set<std::string>& skuSets) const;
	ProductDbHashTable productsFromQuery(const std::string& query) const;
	
public:
	RootDB();
	void initialize() const;
	nat8 lastOrderNumber() const { m_config->lastOrderNumber(); }
	nat8 nextOrderNumber();

	// Customers
	void addCustomer(ref<CustomerDB> customer);
	void deleteCustomer(const wstring_t& email);
	void updateCustomer(const wstring_t& email, ref<CustomerDB> customer);
	ref<CustomerDB> getCustomerByEmail(const wstring_t& email) const;
	ref<CustomerDB> getCustomerByPhone(const wstring_t& phone) const;
	CustomersDbList allCustomers() const;

	// Products
	void addProduct(ref<ProductDB> product);
	void deleteProduct(ref<ProductDB> product);
	void updateProduct(const wstring_t& originalSku, ref<ProductDB> product);
	ref<ProductDB> getProductBySKU(const wstring_t& sku) const;
	ProductDbList allProducts() const;
	ProductDbHashTable productsBySKU(const std::list<wstring_t>& skuList) const;
	ProductDbHashTable productsBySKU(const std::unordered_set<std::string>& skuList) const;
	bool hasProductBeenOrdered(const wstring_t& sku) const;

	// Orders
	ref<OrderDB> createOrder(
		nat1 paymentType,
		const ShippingAddressDB& shippingAddress);
	OrdersDBList allOrdersFromCustomer(const wstring_t& customerEmail) const;
	OrderItemsDBProdPairList orderItemDBPairs(ref<OrderDB> orderDb) const;
	ref<OrderDB> getOrder(nat8 number, const wstring_t& customerEmail) const;
	

	~RootDB() = default;

	METACLASS_DECLARATIONS(RootDB, object);
};
