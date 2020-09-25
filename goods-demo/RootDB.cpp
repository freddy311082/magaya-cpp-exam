#include "pch.h"
#include "RootDB.h"
#include <sstream>
#include "CustomerDB.h"

RootDB::RootDB() : object(self_class)
{
	m_customers = B_tree::create(this);
	m_products = B_tree::create(this);
}

ref<RootDB> RootDB::create()
{
	return NEW RootDB();
}

field_descriptor& RootDB::describe_components()
{
	return NO_FIELDS;
}

void RootDB::initialize() const
{
	if (is_abstract_root())
	{
		ref<RootDB> root = this;
		modify(root)->become(NEW RootDB());
	}
}


ref<CustomerDB> RootDB::getCustomer(const wstring_t& name)
{
	ref<CustomerDB> result;
	std::stringstream query;
	char* _name = name.getChars();
	query << "m_name='" << _name << "'";
	
	
	result_set_cursor cursor;

	try
	{
		m_customers->filter(cursor, query.str().c_str());
		result = cursor.next();
	}
	catch (QueryException const& _)
	{
		throw;
	}

	delete[] _name;
	return result;
}

void RootDB::addCustomer(ref<CustomerDB> customer)
{
	modify(m_customers)->insert(customer);
}

REGISTER(RootDB, object, pessimistic_scheme);