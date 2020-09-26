// goods-demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
//#include "db-root.h"
//#include "database-guard.h"
#include "wstring.h"
#include "src/datasource/db/DBDatasource.h"
#include <sstream>

using namespace std;


static int run()
{
	// -- your code here...

	return EXIT_SUCCESS;
}

int main()
{
	///*database db;

	//if (database_guard _{ db, "C:\\goods\\server.cfg" })
	//{
	//	ref<db_root> root;
	//	db.get_root(root);
	//	root->initialize();
	//	wstring_t aa = "adad";
	//	auto s = ShippingAddressDB::create(aa, aa, aa, aa, 56);
	//	return run();
	//}*/

	
	try
	{
		//{
		//	DBDataSource ds("C:\\goods\\server");

		//	string str{ "aa" };
		//	ShippingAddress addr = ShippingAddress{ str, str, str, str, 11 };

		//	for (size_t i = 0; i < 3; ++i)
		//	{
		//		std::stringstream mail, custname;
		//		custname << "cust name " << i;
		//		mail << "cut" << i << "@cust.com";
		//		CustomerPtr cust = make_unique<Customer>(custname.str(), "234345345", mail.str(), addr);
		//		ds.addCustomer(cust);
		//		custname.clear();
		//		mail.clear();
		//	}
		//}

		{
			DBDataSource ds("C:\\goods\\server");

			for (const auto& cutomer: ds.allCustomers())
			{
				cout << cutomer->info() << endl << endl;
			}

			cout << "Sleeping!!" << endl;
			std::this_thread::sleep_for(std::chrono::seconds(20));
			cout << "Waking Up!!" << endl;
		}

		{
			DBDataSource ds("C:\\goods\\server");

			auto customer = ds.getCustomerByName("cust name 0");

			assert(customer != nullptr);
			cout << "Customer found !!" << endl << customer->info() << endl;

			customer = ds.getCustomerByName("unknown customer");
			assert(customer == nullptr);
			cout << "No customer found !" << endl;
			
		}
	
		
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}

	

	//database db;
	//if (db.open("C:\\goods\\server.cfg"))
	//{
	//	GOODS_NAMESPACE::ref<RootDB> root;
	//	db.get_root(root);
	//	root->initialize();
	//}

	return EXIT_FAILURE;
}

//#include "pch.h"
//#include "goods.h"
//#include "dbscls.h"
//#include <iostream>
//
//USE_GOODS_NAMESPACE
//
//const int nOrders = 2;
//const int nSuppliers = 5;
//const int nStreets = 100;
//
//const int queryBufSize = 64 * 1024;
//
//struct Address {
//	wstring_t street;
//	wstring_t city;
//	wstring_t state;
//	int4      zipcode;
//
//	field_descriptor& describe_components() {
//		return FIELD(street), FIELD(city), FIELD(state), FIELD(zipcode);
//	}
//
//	friend field_descriptor& describe_field(Address& s) {
//		return s.describe_components();
//	}
//};
//
//class Supplier : public object {
//public:
//	wstring_t name;
//	Address   addr;
//	float     rating;
//	ref<set_member> key;
//	ref<set_owner> orders;
//
//	Supplier(wstring_t const& sName, Address const& sAddr, float sRating) : object(self_class), name(sName), addr(sAddr), rating(sRating)
//	{
//		char* supplierName = name.getChars();
//		key = set_member::create(this, supplierName);
//		delete[] supplierName;
//		orders = B_tree::create(this);
//	}
//
//	METACLASS_DECLARATIONS(Supplier, object);
//};
//
//class Order : public object {
//public:
//	ref<Supplier> supplier;
//	wstring_t item;
//	nat8 price;
//	nat8 delivery;
//	ref<set_member> supplier_orders;
//	ref<set_member> all_orders;
//
//	Order(ref<Supplier> oSupplier, wstring_t oItem, nat8 oPrice, nat8 oDelivery)
//		: object(self_class), supplier(oSupplier), item(oItem), price(oPrice), delivery(oDelivery)
//	{
//		char* itemName = item.getChars();
//		all_orders = set_member::create(this, itemName);
//		supplier_orders = set_member::create(this, itemName);
//		delete[] itemName;
//	}
//
//	METACLASS_DECLARATIONS(Order, object);
//};
//
//class Database : public object {
//public:
//	ref<B_tree> suppliers;
//	ref<B_tree> orders;
//
//	void initialize() const {
//		if (is_abstract_root()) {
//			ref<Database> root = this;
//			modify(root)->become(NEW Database());
//		}
//	}
//
//	void populate() const
//	{
//		char buf[256];
//		time_t delivery = time(NULL);
//		int orderId = 1000;
//		Address addr;
//		addr.city = "Boston";
//		addr.state = "MT";
//		for (int i = 1; i <= nSuppliers; i++) {
//			sprintf(buf, "%d-th avenu", i % nStreets);
//			addr.street = buf;
//			addr.zipcode = i % nStreets;
//			sprintf(buf, "X%d", i);
//			ref<Supplier> supplier = NEW Supplier(buf, addr, i % 3);
//			std::cout << supplier->key->get_key() << " - " << supplier->name << std::endl;
//			modify(suppliers)->insert(supplier->key);
//
//			for (int j = 1; j <= nOrders; j++) {
//				sprintf(buf, "#%d", orderId++);
//				ref<Order> order = NEW Order(supplier, buf, 999 + (j & 1), delivery++);
//				modify(orders)->insert(order->all_orders);
//				modify(supplier->orders)->insert(order->supplier_orders);
//			}
//		}
//	}
//
//	Database() : object(self_class) {
//		orders = B_tree::create(this);
//		suppliers = B_tree::create(this);
//	}
//
//
//	METACLASS_DECLARATIONS(Database, object);
//};
//
//field_descriptor& Order::describe_components()
//{
//	return FIELD(supplier), FIELD(item), FIELD(price), FIELD(delivery), FIELD(supplier_orders), FIELD(all_orders);
//}
//
//field_descriptor& Supplier::describe_components()
//{
//	return FIELD(name), FIELD(addr), FIELD(rating), FIELD(key), FIELD(orders);
//}
//
//field_descriptor& Database::describe_components()
//{
//	return FIELD(orders), FIELD(suppliers);
//}
//
//REGISTER(Supplier, object, pessimistic_scheme);
//REGISTER(Order, object, pessimistic_scheme);
//REGISTER(Database, object, pessimistic_scheme);
//
//
//
//int main()
//{
//	database db;
//	task::initialize(task::normal_stack);
//	if (db.open("C:\\goods\\server.cfg")) {
//		ref<Database> root;
//		db.get_root(root);
//		root->initialize();
//		if (root->orders->empty()) {
//			time_t start = time(NULL);
//			root->populate();
//			printf("Elapsed time for populating database: %d seconds\n", (int)(time(NULL) - start));
//		}
//		{
//			time_t start = time(NULL);
//			result_set_cursor cursor;
//			try {
//				root->orders->filter(cursor, "price >= 1000 and item like '#%' and supplier.addr.city='Boston' and supplier.rating>1", queryBufSize);
//			}
//			catch (QueryException const& x) {
//				fprintf(stderr, "Query failed: %s\n", x.msg);
//				db.close();
//				return EXIT_FAILURE;
//			}
//			ref<Order> order;
//			int n_orders;
//			for (n_orders = 0; (order = cursor.next()) != NULL; n_orders++) {
//				std::cout << order->item << std::endl;;
//				assert(order->price >= 1000 && order->supplier->addr.city == "Boston" && order->supplier->rating > 1);
//			}
//			printf("Elapsed time for filtering %d orders: %d seconds\n", n_orders, (int)(time(NULL) - start));
//
//
//			try {
//				root->suppliers->filter(cursor, "addr.city='Boston' and orders contains (price >= 1000 and item like '#%')", queryBufSize);
//			}
//			catch (QueryException const& x) {
//				fprintf(stderr, "Query failed: %s\n", x.msg);
//				db.close();
//				return EXIT_FAILURE;
//			}
//			ref<Supplier> supplier;
//			int n_suppliers;
//			for (n_suppliers = 0; (supplier = cursor.next()) != NULL; n_suppliers++) {
//				assert(supplier->addr.city == "Boston");
//			}
//			printf("Elapsed time for filtering %d suppliers: %d seconds\n", n_suppliers, (int)(time(NULL) - start));
//
//			for (auto mbr = root->suppliers->first; !mbr.is_nil(); mbr = mbr->next)
//			{
//				ref<Supplier> sup = mbr->obj;
//				std::cout << sup->name << std::endl;
//			}
//		}
//		db.close();
//		return EXIT_SUCCESS;
//	}
//	else {
//		fprintf(stderr, "Failed to open detabase\n");
//		return EXIT_FAILURE;
//	}
//}