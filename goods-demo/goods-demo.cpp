// goods-demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "db-root.h"
#include "database-guard.h"


static int run()
{
	// -- your code here...

	return EXIT_SUCCESS;
}

int main()
{
	database db;

	if (database_guard _{ db, "C:\\Projects\\magaya-cpp-exam\\Debug\\data\\demo.cfg" })
	{
		ref<db_root> root;
		db.get_root(root);
		root->initialize();

		return run();
	}

	return EXIT_FAILURE;
}
