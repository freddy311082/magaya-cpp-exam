#pragma once

class db_root : public object
{
public:
	METACLASS_DECLARATIONS(db_root, object);

	static ref<db_root> create()
	{
		return NEW db_root(self_class);
	}

	void initialize() const;

protected:
	db_root(class_descriptor& desc)
		: object(desc)
	{
	}
};
