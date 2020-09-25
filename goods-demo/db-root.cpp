
#include "pch.h"
//#include "db-root.h"
//
//REGISTER(db_root, object, pessimistic_repeatable_read_scheme);
//
//field_descriptor& db_root::describe_components()
//{
//	return NO_FIELDS;
//}
//
//void db_root::initialize() const
//{
//	if (is_abstract_root())
//	{
//		ref<db_root> root = this;
//		modify(root)->become(NEW db_root(db_root::get_self_class()));
//	}
//}
//
