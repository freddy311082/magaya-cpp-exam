# Magaya C++ Exam

## C++ Exam for applicants

The purpose of this exam is to measure the developer’s technical knowledge and creativity to build an application across the different architectural layers.

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

## Some useful links
You can find the full source code of GOODS database [here](https://sourceforge.net/projects/goods-oodbms/) as well as some examples of how to use it following this [link](https://sourceforge.net/p/goods-oodbms/code/HEAD/tree/examples/)

The full documentation written by GOODS author Konstantin Knizhnik can be found [here](http://www.garret.ru/goods/readme.htm#See%20GOODS%20documentation)
