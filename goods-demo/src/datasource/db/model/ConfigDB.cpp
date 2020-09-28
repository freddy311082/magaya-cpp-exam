#include "pch.h"
#include "ConfigDB.h"


ConfigDB::ConfigDB(): object(self_class)
{
	m_key = set_member::create(this, "ConfigDB_Dingle_Object");
}

field_descriptor& ConfigDB::describe_components()
{
	return FIELD(m_lastOrderNumber), FIELD(m_key);
}

ref<ConfigDB> ConfigDB::create()
{
	return NEW ConfigDB();
}


REGISTER(ConfigDB, object, pessimistic_scheme);