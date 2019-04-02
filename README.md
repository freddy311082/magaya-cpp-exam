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
- Customer’s Phone as well as customer's email must be unique.
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

## Configuration file
The configuration file should look like this:

demo-config.cfg
```
1
0:localhost:6110
```

## What is GOODS?
GOODS is a distributed Generic Object Oriented Database System with an active-client model where all application logic is implemented, interpreted and executed at client side.

### GOODS Database Files
- WH.CFG: Specifies how many storages are used and the connection point for each storage. 
- WH.IDX: Contains information about each class and object stored in the database except its content.
- WH.ODB: Contains the data that describes classes and the content of each object.
- WH.MAP: This is the bitmap allocator, it is used to determine the location in the OBJ file for a new or relocated object or class. It also has the information about the fragmented spaces of the OBJ file.
- WH.LOG: Contains all committed transactions between checkpoints. Its main purpose is to restore the database to a consistent state after a system crash.
- WH.HIS: It is used for coordination of distributed transactions across multiple storages. 
- WH.IBM: It is used to support incremental backups. It contains the last timestamp for each modified page in the storage.
- WH.PWD: Contains authorized users and passwords. When this file is present the server enforces authentication.


## GOODS hints
- every database class must derived from `object`
- `wstring_t`: used for text fields
- `set_owner`: used for sequential containers
- `B_tree`: used for creating indexes

## Some useful links
You can find the full source code of GOODS database [here](https://sourceforge.net/projects/goods-oodbms/) as well as some examples of how to use it following this [link](https://sourceforge.net/p/goods-oodbms/code/HEAD/tree/examples/)

The full documentation written by GOODS author Konstantin Knizhnik can be found [here](http://www.garret.ru/goods/readme.htm#See%20GOODS%20documentation)
