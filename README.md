# Magaya C++ Exam

## C++ Exam for applicants

The purpose of this exam is to measure the developer’s technical knowledge and creativity to build an application across the different architectural layers. What we are looking for is Modern C++ code which is well organized and easy to maintain.

The application will be a simple order management system to control orders placed from customers. It must include the following:
- Add, modify or delete customers
- Add, modify or delete products
- Add or delete orders
- Lists of customers, products and orders.
- View order detail

## The information required for each entity:
- Customer: Name, Phone, Email, Main Shipping Address
- Shipping Address: Street and Number, City, State, Zip code, Country
- Product: Part number (SKU), Description, Price, Weight
- Order: Number, Date, Customer, Shipping Address, Payment Type (Cash, Credit Card, Check, Other), List of products with quantities/prices and Total Value. 

## The business logic:
- Customer’s phone number must be unique. 
- Customer's email must be unique.
- Product’s SKU must be unique.
- Order’s Number must be unique.
- An order can contain multiple products. It has to have at least one product.
- Order’s Total Value is the sum of order’s lines amount (amount = quantity * price).
- A product cannot be deleted after it has been used in an order.
- A customer cannot be deleted after it has been used in an order.

## Technology requirements
- Windows OS
- [Microsoft Visual Studio 2017 Community Edition](https://visualstudio.microsoft.com/downloads/)
- Must use GOODS database provided in this project
- Must use Microsoft Foundation Classes (MFC) for client UI

## Steps to build
1. Build client-lib project: This will create a client-lib.lib that is needed to build the server and the demo projects.
2. Build goods-server: This will create a goods-server.exe that is ready to use.
3. Use goods-demo as a template for your project.

## Steps to run the demo project
1. Run the goods-server from command line: `goods-server.exe <path-to-config-file>`
  
  e.g: 
  `goods-server.exe C:\Projects\magaya-cpp-exam\Debug\data\demo-config`
  
2. Run the goods-demo 

The server and the client will use the same configuration file to open and connect to the database.
The server will log any activity from the client in the console.

## GOODS Database

### What is GOODS?
GOODS is a distributed **G**eneric **O**bject **O**riented **D**atabase **S**ystem with an active-client model where all application logic is implemented, interpreted and executed at client side.

## Configuration file
The configuration file should look like this:

demo-config.cfg
```
1
0:localhost:6110
```
## GOODS client fundamentals
### object
`object` is the base class for GOODS persistent objects. 

`ref` is the smart pointer that GOODS uses to control access to every persistable object. 

`write_access` is also a smart pointer that creates a transaction scope for modifying a GOODS object. The `modify()` function can be used to obtain write_access object and thus start a database transaction. 

```
auto w_obj = modify(obj);
```

### Persistent object
GOODS has specific requirements to allow a class to persist:
1. Must inherit from `object` at any level.
2. Use the `METACLASS_DECLARATIONS` macro in the class declaration to bring in the required functions
3. Use the `REGISTER` macro in the class implementation file in the global scope to create the default implementation for the function brought by the `METACLASS_DECLARATIONS` macro
4. Implement the `describe_components()` function for the class specifying the fields that need to persist using predefined macros like `FIELD` or `ARRAY` (see example)

The requirements above qualify a class as *persistable* but to actually persist in the database; an instance of the class must be referred by an object that is already persistent.

The root of the database has a special way of becoming persistent, since it is always the first persistent object. All objects (other than the root itself) are directly or indirectly linked to the root, and reachable from the root.


#### Example class
```cpp
class my_object : public object 
{
private:
    nat4 my_field;
public:
    METACLASS_DECLARATIONS(my_object, object);

    my_object(class_descriptor& desc) : object(desc), my_field(0)
    {
    }    
    static ref<my_object> create() 
    {
	    return NEW my_object(self_class);
    }
};

REGISTER(my_object, object, pessimistic_scheme);

field_descriptor& my_object::describe_components()
{
    return FIELD(my_field);
}
```


### Data field types
The following types are available in GOODS:
#### Integer types
|Data Type     | C++ Type          | Size  |
|------------- |:------------------| -----:|
|int1      	   | char              | 1     |
|nat1      	   | unsigned char     | 1     |
|int2      	   | short             | 2     |
|nat2      	   | unsigned short    | 2     |
|int4      	   | int               | 4     |
|nat4      	   | unsigned int      | 4     |
|int8      	   | long long         | 8     |
|nat8      	   | unsigned long long| 8     |

#### Floating point types
|Data Type     | C++ Type          | Size  |
|------------- |:------------------| -----:|
|real4    	   | float             | 4     |
|real8     	   | double            | 8     |

#### Other types
|Data Type     | Description        | Size  |
|------------- |:-------------------| -----:|
|wstring_t	   | string             |varies |
|raw_binary_t  | bytes array        |varies |
|ref\<T>        | reference to object| 6     |


### Container classes
GOODS provides some built-in containers to store collections of objects.

#### Simple Collection
`set_owner` is provided to store a group of objects without any specific order. Do not get confused with the name of the type: `set_owner` is just a double-linked list of objects and not a set of unique objects as its name implies.

The following example shows how to iterate a `set_owner` 

```cpp
for (auto mbr = list->first; !mbr.is_nil(); mbr = mbr->next)
{
	ref<my_object> obj = mbr->obj;
	// -- do something with obj
}
```

#### Sorted Collection
`B_tree` are provides to stored objects in an specific order. Objects are sorted according to its insertion key.

`B_tree` is a multi-branch balanced tree that provides fast access to objects in the database. This class is derived from `set_owner` and uses  `set_member` instances to connect the inserted objects.

### Meta-objects
Metaobjects handle the interaction of client applications with the database. They allow the programmer to extend the functionality and the behavior of the application depending on specific requirements.

Metaobjects cover the following aspects :
- Inter-task synchronization of object access.
- Synchronization of object access by different database clients.
- Handling of database transactions.
- Management of the client’s object cache

For the scope of this assignment the pessimistic metaobject  (pessimistic_schema) schema will suffice.

    pessimistic_metaobject pessimistic_scheme;
> In our example the metaobject is specified in the line:
> REGISTER(my_object, object, **pessimistic_scheme**);

### Objects and Classes Identifiers
*CPID*: Class persistent identifier

 - The valid range is from 2 to 65535 (0xFFFF). It is a WORD. CPID 1 is
-  Abstract root class when the database is not initialized. Each
-  Different version of a class has a different identifier. Non used
-  Classes are garbage collected.

*OPID*: Object persistent identifier

- The valid range is from 65536 (0x10000) to 4294967295 (0xFFFFFFFF). It is a DWORD.
- Object 0x10000 is the database root.
- Each object in the database knows its CPID.
- Non referenced objects from root are garbage collected.

### GOODS Database Files
- *WH.CFG*: Specifies how many storages are used and the connection point for each storage. 
- *WH.IDX*: Contains information about each class and object stored in the database except its content.
- *WH.ODB*: Contains the data that describes classes and the content of each object.
- *WH.MAP*: This is the bitmap allocator, it is used to determine the location in the OBJ file for a new or relocated object or class. It also has the information about the fragmented spaces of the OBJ file.
- *WH.LOG*: Contains all committed transactions between checkpoints. Its main purpose is to restore the database to a consistent state after a system crash.
- *WH.HIS*: It is used for coordination of distributed transactions across multiple storages. 
- *WH.IBM*: It is used to support incremental backups. It contains the last timestamp for each modified page in the storage.
- *WH.PWD*: Contains authorized users and passwords. When this file is present the server enforces authentication.

## GOODS hints
- every database class must derived from `object`
- `wstring_t`: used for text fields
- `set_owner`: used for sequential containers
- `B_tree`: used for creating indexes

## Some useful links
You can find the full source code of GOODS database [here](https://sourceforge.net/projects/goods-oodbms/) as well as some examples of how to use it following this [link](https://sourceforge.net/p/goods-oodbms/code/HEAD/tree/examples/)

The full documentation written by GOODS author Konstantin Knizhnik can be found [here](http://www.garret.ru/goods/readme.htm#See%20GOODS%20documentation)
