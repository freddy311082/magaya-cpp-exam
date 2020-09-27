#include "pch.h"
#include "RootDB.h"
#include <sstream>
#include "CustomerDB.h"
#include "ProductDB.h"
#include <iostream>

RootDB::RootDB() : object(self_class)
{
	m_customers = B_tree::create(this);
	m_products = B_tree::create(this);
}

field_descriptor& RootDB::describe_components()
{
	return FIELD(m_customers),
		FIELD(m_products);
}

void RootDB::initialize() const
{
	if (is_abstract_root())
	{
		ref<RootDB> root = this;
		modify(root)->become(NEW RootDB());
	}
}



void RootDB::addCustomer(ref<CustomerDB> customer)
{
	if (customer == nullptr)
		throw std::invalid_argument("Invalid customer.");

	modify(m_customers)->insert(customer->key());
}

void RootDB::removeCustomer(ref<CustomerDB> customer)
{
	std::stringstream query;
	query << "m_name='" << customer->name().getChars() << "'";

	try
	{
		if (customer == nullptr)
			throw std::invalid_argument("Customer not found.");

		modify(m_customers)->remove(customer);
	}
	catch (const QueryException& exc)
	{
		throw std::invalid_argument(exc.msg);
	}
}

ref<CustomerDB> RootDB::getCustomerByName(const wstring_t& name) const
{
	try
	{
		std::stringstream query;
		query << "m_name='" << name.getChars() << "'";
		result_set_cursor cursor;
		m_customers->filter(cursor, query.str().c_str());
		ref<CustomerDB> result = cursor.next();
		return result;
	}
	catch (const QueryException& exc)
	{
		throw std::invalid_argument(exc.msg);
	}

	return nullptr;
}

void RootDB::updateCustomer(ref<CustomerDB> customer)
{
	auto cust = getCustomerByName(customer->name());

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

void RootDB::addProdduct(ref<ProductDB> product)
{
	if (product == nullptr)
		throw std::invalid_argument("Invalid product.");

	modify(m_products)->insert(product->key());
}

void RootDB::removeProduct(const wstring_t& sku)
{
	auto product = getProductBySKU(sku);

	if (product == nullptr)
		throw std::invalid_argument("Product not found.");

	modify(m_products)->remove(product->key());
}

void RootDB::updateProduct(ref<ProductDB> product)
{
	if (product == nullptr)
		throw std::invalid_argument("Invalid product.");

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

ref<ProductDB> RootDB::getProductBySKU(const wstring_t& sku) const
{
	ref<ProductDB> product;

	if (!sku.isNull())
	{
		std::stringstream query;
		query << "m_sku='" << sku << "'";
		result_set_cursor cursor;
		m_products->filter(cursor, query.str().c_str());
		 product = cursor.next();
	}

	return product;
}


REGISTER(RootDB, object, pessimistic_scheme);