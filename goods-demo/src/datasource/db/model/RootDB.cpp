#include "pch.h"
#include "RootDB.h"
#include <sstream>
#include "CustomerDB.h"
#include <iostream>

void RootDB::throw_invalid_argument(const char* dbErrorMessage) const
{
	std::stringstream error;
	error << "Error deleting customer: " << dbErrorMessage;
	throw std::invalid_argument(error.str());
}

RootDB::RootDB() : object(self_class)
{
	m_customers = B_tree::create(this);
}

field_descriptor& RootDB::describe_components()
{
	return FIELD(m_customers);
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
	modify(m_customers)->insert(customer->key());
}

void RootDB::removeCustomer(ref<CustomerDB> customer)
{
	std::stringstream query;
	query << "m_name='" << customer->name().getChars() << "'";

	try
	{
		auto customer = m_customers->find(query.str().c_str());

		if (customer == nullptr)
			throw std::invalid_argument("Customer not found.");

		modify(m_customers)->remove(customer);
	}
	catch (const QueryException& exc)
	{
		throw_invalid_argument(exc.msg);
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
		throw_invalid_argument(exc.msg);
	}

	return nullptr;
}

void RootDB::updateCustomer(ref<CustomerDB> customer)
{
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


REGISTER(RootDB, object, pessimistic_scheme);