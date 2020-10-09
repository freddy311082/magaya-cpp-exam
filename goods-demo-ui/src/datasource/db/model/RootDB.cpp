#include "pch.h"
#include "RootDB.h"
#include <sstream>
#include "CustomerDB.h"
#include "ProductDB.h"
#include "OrderDB.h"
#include "OrderItemDB.h"
#include <iostream>
#include <ctime>

RootDB::RootDB() : object(self_class)
{
	m_customers = B_tree::create(this);
	m_products = B_tree::create(this);
	m_config = ConfigDB::create();
}

field_descriptor& RootDB::describe_components()
{
	return FIELD(m_customers),
		FIELD(m_products),
		FIELD(m_config);
}

void RootDB::initialize() const
{
	if (is_abstract_root())
	{
		ref<RootDB> root = this;
		modify(root)->become(NEW RootDB());
	}
}


nat8 RootDB::nextOrderNumber()
{
	return modify(m_config)->nextOrderNumber();
}

void RootDB::addCustomer(ref<CustomerDB> customer)
{
	if (getCustomerByEmail(customer->email()) != nullptr ||
		getCustomerByPhone(customer->phone()) != nullptr)
		throw std::invalid_argument("This customer already exists.");
	
	modify(m_customers)->insert(customer->key());
}

void RootDB::deleteCustomer(const wstring_t& email)
{
	auto customerDb = getCustomerByEmail(email);

	if (customerDb == nullptr)
		throw std::invalid_argument("Customer doesn't exists");

	if (!customerDb->canBeDeleted())
		throw std::invalid_argument("This customer has orders associated. It cannot be deleted.");

	modify(m_customers)->remove(customerDb->key());
}

ref<CustomerDB> RootDB::getCustomer(const std::stringstream& query) const
{
		
	result_set_cursor cursor;
	m_customers->filter(cursor, query.str().c_str());
	return cursor.next();
}

ref<CustomerDB> RootDB::getCustomerByEmail(const wstring_t& email) const
{
	std::stringstream query;
	query << "m_email='" << email.getChars() << "'";
	return getCustomer(query);
}

ref<CustomerDB> RootDB::getCustomerByPhone(const wstring_t& phone) const
{
	std::stringstream query;
	query << "m_phone='" << phone.getChars() << "'";
	return getCustomer(query);
}

void RootDB::updateCustomer(ref<CustomerDB> customer)
{
	auto cust = getCustomerByEmail(customer->email());

	if (cust == nullptr)
		throw std::invalid_argument("Customer not found.");

	modify(cust)->update(cust->name(), customer->phone(), customer->email(), customer->shippingAddress());
}

CustomersDbList RootDB::allCustomers() const
{
	CustomersDbList result;
	for (auto mbr = m_customers->first; !mbr.is_nil(); mbr = mbr->next)
	{
		ref<CustomerDB> customer = mbr->obj;
		result.push_back(customer);
	}

	return result;
}

void RootDB::addProduct(ref<ProductDB> product)
{
	if (getProductBySKU(product->sku()) != nullptr)
		throw std::invalid_argument("This product already exists.");

	modify(m_products)->insert(product->key());
}

void RootDB::deleteProduct(ref<ProductDB> product)
{
	modify(m_products)->remove(product->key());
}

void RootDB::updateProduct(ref<ProductDB> product)
{
	wstring_t sku = product->sku();
	auto productDb = getProductBySKU(sku);

	if (productDb == nullptr)
		throw std::invalid_argument("Product not found.");

	modify(productDb)->update(product->sku(), product->description(), product->price(), product->weight());
}

ProductDbList RootDB::allProducts() const
{
	ProductDbList result;

	for (auto mbr = m_products->first; !mbr.is_nil(); mbr = mbr->next)
	{
		ref<ProductDB> product = mbr->obj;
		result.push_back(product);
	}

	return result;
}

ProductDbHashTable RootDB::productsBySKU(const std::list<wstring_t>& skuList) const
{
	ProductDbHashTable result;
	std::stringstream query;
	bool firstLoop = true;

	// building the query string
	for (const wstring_t& sku: skuList)
	{
		query << (firstLoop ? "" : " || ");
		query << "m_sku='" << sku.getChars() << "'";
		firstLoop = false;
	}
	
	result_set_cursor cursor;
	m_products->filter(cursor, query.str().c_str());

	auto productRef = cursor.next();
	while (!productRef.is_nil())
	{
		ref<ProductDB> productDb = productRef;
		result[productDb->sku().getChars()] = productDb;
		productRef = cursor.next();
	}

	return result;
}

bool RootDB::hasProductBeenOrdered(const wstring_t& sku) const
{
	auto product = getProductBySKU(sku);

	if (product.is_nil())
		throw std::invalid_argument("This product doesn't exists.");

	return product->timesUsed() > 0;
}

ref<OrderDB> RootDB::createOrder(
	nat1 paymentType,
	const ShippingAddressDB& shippingAddress)
{
	nat8 orderNumber = modify(m_config)->nextOrderNumber();
	std::time_t tNow = std::time(nullptr);	
	return  OrderDB::create(orderNumber, dbDateTime(tNow), paymentType, shippingAddress);
	
}

OrdersDBList RootDB::allOrdersFromCustomer(const wstring_t& customerEmail) const
{
	std::stringstream query;
	char* email = customerEmail.getChars();
	query << "m_email='" << email << "'";
	result_set_cursor cursor;

	m_customers->filter(cursor, query.str().c_str());

	ref<CustomerDB> customerDB = cursor.next();
	if (customerDB.is_nil())
		throw std::invalid_argument("This customer doesn't exists.");

	return customerDB->allOrders();
}

OrderItemsDBProdPairList RootDB::orderItemDBPairs(ref<OrderDB> orderDb) const
{
	OrderItemsDBProdPairList result;
	
	auto orderProducts = productsBySKU(orderDb->allProductSKUs());

	for (const auto& item: orderDb->items())
		result.push_back({ orderProducts[item->productSKU().getChars()], item });
	
	return result;
}

ref<OrderDB> RootDB::getOrder(nat8 number, const wstring_t& customerEmail) const
{
	std::stringstream query;
	query << "m_email='" << customerEmail.getChars() << "' and m_orders contains (m_number=" << number << ")";
	result_set_cursor cursor;
	m_customers->filter(cursor, query.str().c_str());

	ref<CustomerDB> customer = cursor.next();

	if (customer != nullptr)
		return customer->getOrder(number);

	return nullptr;
}

ref<ProductDB> RootDB::getProductBySKU(const wstring_t& sku) const
{
	ref<ProductDB> product;

	std::stringstream query;
	char* skuStr = sku.getChars();
	query << "m_sku='" << skuStr << "'";

	result_set_cursor cursor;
	m_products->filter(cursor, query.str().c_str());
	delete[] skuStr;

	return cursor.next();
}


REGISTER(RootDB, object, pessimistic_scheme);