#ifndef _Header.h
#define Header
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Product
{
private:
	string productName;
	unsigned int price;
	unsigned int quantity;
	unsigned int quantityOrderd;
	bool premium;
public:
	Product* next;
	Product(string name, unsigned int quant, unsigned int price, bool premium);
	unsigned int getPrice() const {
		return price;
	}
	string getName() const {
		return productName;
	}
	unsigned int getQuantity() const {
		return quantity;
	}
	unsigned int getQuantityOrderd() const {
		return quantityOrderd;
	}
	bool getPremium() const {
		return premium;
	}
	string toString();
	void addQuant(int x);
	void addOrdered(int x);
};

class Order {
private:
	string productName;
	unsigned int price;
	unsigned int quantity;
public:
	Order* next;
	Order* prev;
	Order(string name, unsigned int quant, unsigned int price);
	unsigned int getPrice() const {
		return price;
	}
	string getName() const {
		return productName;
	}
	unsigned int getQuantity() const {
		return quantity;
	}
	void setQuantity(int x);
	string toString();
};

class Table {
private:
	unsigned int tableNumber;
	Order* tableOrders;
	unsigned int sum;
public:
	Table();
	void cleanTable();
	Order* getTableOrders() const {
		return tableOrders;
	}
	void addOrderToTable(Order* order);
	void addPremiumToSum();
	void setTableNumber(int i);
	bool removeOrder(string productName, unsigned int quant);
	//void removeAllOrders();
	string toString();
};

class MyRestaurant
{
private:
	Product* productList;
	unsigned int tableAmount;
	Table* tables;
public:
	MyRestaurant() {};
	MyRestaurant(int tableAmount, Product* productList);
	Product* getProductList() const {
		return productList;
	}
	Table* getTables() const {
		return tables;
	}
	~MyRestaurant();
	void setProductList(Product* pl);
	bool addItems(string productName, int quantity);
	bool orderItem(unsigned int tableNumber, string productName, unsigned int quantity);
	bool removeItem(unsigned int tableNumber, string productName, unsigned int quantity);
	void removeTable(unsigned int tableNumber);
	void reports(char a,unsigned int i);
};

Product* createProducts();

#endif
