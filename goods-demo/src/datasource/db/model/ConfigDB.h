#pragma once

#include "goods.h"

class ConfigDB : public object
{
private:
	nat8 m_lastOrderNumber = 0;
	ref<set_member> m_key;

	ConfigDB();
public:
	METACLASS_DECLARATIONS(ConfigDB, object);
	
	nat8 lastOrderNumber() const
	{
		return m_lastOrderNumber;
	}
	nat8 netxOrderNumber() { return ++m_lastOrderNumber; }
	ref<set_member> key() const { return m_key; }
	static ref<ConfigDB> create();
};

