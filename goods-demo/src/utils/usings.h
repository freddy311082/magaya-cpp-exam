#pragma once

#include <list>
#include <memory>

template <typename T>
class ref;

// Database
class CustomerDB;
using CustomersDbList = std::list<ref<CustomerDB>>;

class ShippingAddressDB;

class ProductDB;
using ProductDbList = std::list<ref<ProductDB>>;

class ShippingAddressDB;
using ShippingAddressDBPtr = std::unique_ptr<ShippingAddressDB>;

class OrderDB;

class OrderItemDB;
using OrderItemDbList = std::list<ref<OrderDB>>;


// Model
class Customer;
using CustomerPtr = std::unique_ptr<Customer>;
using CustomersList = std::list<CustomerPtr>;

class Order;
using OrderPtr = std::unique_ptr<Order>;

class Product;
using ProductPtr = std::unique_ptr<Product>;
using ProductsList = std::list<ProductPtr>;

class OrderItem;
using OrderItemPtr = std::unique_ptr<OrderItem>;
using OrderItemsList = std::list<OrderItemPtr>;