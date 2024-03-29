// goods-demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
//#include "db-root.h"
//#include "database-guard.h"
#include "wstring.h"
#include "src/datasource/db/DBDatasource.h"
#include "src/datasource/DataSourceFactory.h"
#include <sstream>
#include <ctime>
#include "src/middleware/model/Order.h"
#include "src/middleware/model/OrderItem.h"
#include "src/middleware/model/Customer.h"

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
		/*{
			auto ds = DataSourceFactory::newInstance("C:\\goods\\server");

			string str{ "aa" };
			ShippingAddress addr = ShippingAddress{ str, str, str, str, 11 };

			for (size_t i = 0; i < 3; ++i)
			{
				std::stringstream mail, custname;
				custname << "cust name " << i;
				mail << "cut" << i << "@cust.com";
				CustomerPtr cust = make_unique<Customer>(custname.str(), "234345345", mail.str(), addr);
				try
				{
					ds->addCustomer(cust);
				}
				catch (const std::exception& error)
				{
					cout << "**** Error ****: " << error.what() << endl;
				}
				custname.clear();
				mail.clear();
			}
		}*/

		/*{
			DBDataSource ds("C:\\goods\\server");

			for (const auto& cutomer: ds.allCustomers())
			{
				cout << cutomer->info() << endl << endl;
			}
		}*/

		/*{
			DBDataSource ds("C:\\goods\\server");

			auto customer = ds.getCustomerByName("cust name 0");

			assert(customer != nullptr);
			cout << "Customer found !!" << endl << customer->info() << endl;

			customer = ds.getCustomerByName("unknown customer");
			assert(customer == nullptr);
			cout << "No customer found !" << endl;
			
		}*/

		/*{
			DBDataSource ds("C:\\goods\\server");
			try
			{
				ds.deleteCustomer(ds.getCustomerByName("unknown customer"));
			}
			catch (std::exception& err)
			{
				cout << err.what() << endl;
			}

			for (const auto& cutomer : ds.allCustomers())
			{
				cout << cutomer->info() << endl << endl;
			}
		}*/

		/*{
			try
			{
				auto ds = DataSourceFactory::newInstance("C:\\goods\\server");
				string prodSKU = "SKU 1";
				string prodDesc = "Producto 1";
				auto product = make_unique<Product>(prodSKU, prodDesc, 45);
				ds->addProduct(product);

				auto prodSearch = ds->getProductBySKU(prodSKU);

				if (prodSearch != nullptr)
					cout << "**** FOUND IT ****" << prodSearch->info() << endl;
				else
					cout << "Product not found !!" << endl;
			}
			catch (const std::exception& error)
			{
				cout << error.what() << endl;
			}
		}*/

		/*{
			auto ds = DataSourceFactory::newInstance("C:\\goods\\server");

			for (const auto& prod: ds->allProducts())
			{
				cout << prod->info() << endl;
			}
		}*/

		{
			try
			{
				auto ds = DataSourceFactory<DataSourceType_DATABASE>::newInstance("C:\\goods\\server");

				// string prodSKU1 = "SKU 1";
				// string prodDesc1 = "Producto 1";
				// auto product1 = make_unique<Product>(prodSKU1, prodDesc1, 45);
				// ds->addProduct(product1);
				//
				// string prodSKU2 = "SKU 2";
				// string prodDesc2 = "Producto 2";
				// auto product2 = make_unique<Product>(prodSKU2, prodDesc2, 90, 3.9);
				// ds->addProduct(product2);
				//
				// string prodSKU3 = "SKU 3";
				// string prodDesc3 = "Producto 3";
				// auto product3 = make_unique<Product>(prodSKU3, prodDesc3, 21, 17.3);
				// ds->addProduct(product3);
				//
				// string prodSKU4 = "SKU 4";
				// string prodDesc4 = "Producto 4";
				// auto product4 = make_unique<Product>(prodSKU4, prodDesc4, 78);
				// ds->addProduct(product4);
				//
				//
				// string str{ "aa" };
				// ShippingAddress addr = ShippingAddress{ str, str, str, str, 11 };
				// CustomerPtr cust = make_unique<Customer>("Customer 1", "234345345", "cut@cust.com", addr);
				// ds->addCustomer(cust);

				// CustomerPtr customer = ds->getCustomerByEmail("cut@cust.com");
				// ProductPtr product1, product2, product3;
				// product1 = ds->getProductBySKU("SKU 1");
				// product2 = ds->getProductBySKU("SKU 2");
				// product3 = ds->getProductBySKU("SKU 3");
				//
				// std::time_t t = std::time(nullptr);
				// std::tm tm = *std::localtime(&t);

				// OrderPtr order = std::make_unique<Order>(
				// 	ds->getNextOrderNumber(),
				// 	tm,
				// 	PaymentType::CASH,
				// 	ShippingAddress{
				// 		"Desaguadero 2619",
				// 		"Villa Devoto",
				// 		"Buenos Aires",
				// 		"Argentina",
				// 		1419
				// 	}
				// );
				//
				// auto item1 = make_unique<OrderItem>(345.56, move(product1));
				// auto item2 = make_unique<OrderItem>(345.56, move(product1));
				// auto item3 = make_unique<OrderItem>(345.56, move(product1));
				// order->addItem(move(item1));
				// order->addItem(move(item2));
				// order->addItem(move(item3));
				
				// ds->registerOrder({
				// 	"cut@cust.com",
				// 	PaymentType::CHECK,
				// 	ShippingAddress{
				// 		"Desaguadero 2619",
				// 		"Villa Devoto",
				// 		"Ciudad Autonoma de Buenos Aires",
				// 		"Argentina",
				// 		1419
				// 	},
				// 	{
				// 		{45.7, "SKU 4"},
				// 		{431.4, "SKU 2"},
				// 		{100, "SKU 1"},
				// 		{321, "SKU 3"}
				// 	}
				// });

				// for (const auto& order: ds->allOrdersByCustomer("cut@cust.com"))
				// {
				// 	cout << order->info() << endl;
				// }

				// for (const auto& order: ds->allOrders())
				// {
				// 	cout << order->info() << endl;
				// }

				string str{ "aa" };
				ShippingAddress addr = ShippingAddress{ str, str, str, str, 11 };
				CustomerPtr cust = make_unique<Customer>("Customer 1", "234345345", "cusst@cust.com", addr);
				ds->addCustomer(cust);
				
				ds->deleteCustomer("cut@cust.com");
			}
			catch (const std::exception& error)
			{
				cout << error.what() << endl;
			}
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