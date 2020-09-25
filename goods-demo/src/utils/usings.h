#pragma once

#include <memory>
#include <list>

template <typename T>
class ref;

// Database
class CustomerDB;
using CustomersDbList = std::list<ref<CustomerDB>>;

struct ShippingAddressDB;
