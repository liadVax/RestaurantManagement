#include "Header.h"

Product::Product(string name, unsigned int quant, unsigned int price, bool premium) {
	productName = name;
	quantity = quant;
	quantityOrderd = 0;
	this->price = price;
	this->premium = premium;
}
void Product::addOrdered(int x) {
	quantityOrderd += x;
}
void Product::addQuant(int x) {
	this->quantity += x;
}
string Product::toString() {
	return "Product: " + productName + "\nQuantity: " + to_string(quantity) +
		"\nPrice: " + to_string(price) + "\nPremium: " + to_string(premium);
}
	
Order::Order(string name, unsigned int quant, unsigned int x):productName(name),quantity(quant),price(x) {}
void Order::setQuantity(int x) {
	quantity += x;
}
string Order::toString() {
	return "[Product: " + productName + " Quantity: " + to_string(quantity) +
		" Price: " + to_string(price) + "]";
}

Table::Table() {
	tableOrders = NULL;
	sum = 0;
	tableNumber = 0;
}
void Table::cleanTable() {
	sum = 0;
	Order* temp = tableOrders;
	while(temp!=NULL){
		Order* del = temp;
		temp = temp->next;
		delete del;
	}
	delete temp;
	tableOrders = NULL;
}
void Table::addOrderToTable(Order* order) {
	if (tableOrders == NULL) {
		tableOrders = order;
	}
	else {
		order->next = tableOrders;
		tableOrders->prev = order;
		tableOrders = order;
	}
	sum += (order->getPrice() * order->getQuantity());
}
void Table::addPremiumToSum() {
	sum += floor((sum * 0.1));
}
void Table::setTableNumber(int i) {
	tableNumber = i;
}
bool Table::removeOrder(string productName, unsigned int quant) {
	Order* temp = tableOrders;
	while (temp != NULL) {
		if ((temp->getName()).compare(productName) == 0)
			if (temp->getQuantity() >= quant) {
				temp->setQuantity(-1 * quant);
				sum -= ((temp->getPrice()) * quant);
				if (temp->getQuantity() == 0) {
					(temp->prev)->next = temp->next;
					(temp->next)->prev = temp->prev;
					delete temp;
				}
				return true;
			}
		temp = temp->next;
	}
	return false;
}

string Table::toString() {
	Order* temp = tableOrders;
	string str = "Table number " + to_string(tableNumber);
	if (temp == NULL)
		return str.append(" is free\n");
	str.append(" Orders:\n");
	while (temp != NULL) {
		str.append(temp->toString() + '\n');
		temp = temp->next;
	}
	str.append("the check is: " + to_string(sum) + '\n');
	return str;
}

MyRestaurant::MyRestaurant(int tAmount, Product* pl) :productList(pl),tableAmount(tAmount){
	tables = new Table[tableAmount];
	for (int i = 0; i < tableAmount; i++) {
		tables[i].setTableNumber(i + 1);
	}
}
MyRestaurant::~MyRestaurant() {
	for(int i=0;i<tableAmount;i++){
		removeTable(i+1);
	}
	Product* temp = productList;
	while(temp!=NULL){
		Product* del = temp;
		temp = temp->next;
		delete del;
	}
	tableAmount = 0;
	delete[] tables;
	cout << "Restaurant is closed";
}
void MyRestaurant::setProductList(Product* pl) {
	productList = pl;
}
bool MyRestaurant::orderItem(unsigned int tableNumber, string productName, unsigned int quantity) {
	if (tableAmount >= tableNumber) {
		Product* temp = productList;
		while (temp != NULL) {
			string name = temp->getName();
			if ((temp->getName()).compare(productName) == 0 && temp->getQuantity() >= quantity) {
				Order* order = new Order(name, quantity, temp->getPrice());
				tables[tableNumber - 1].addOrderToTable(order);
				temp->addQuant(quantity * -1);
				temp->addOrdered(quantity);
				cout << "Oreder accepted for table " + to_string(tableNumber) + "\n"+ to_string(quantity)+ " " + productName <<endl;
				return true;
			}
			temp = temp->next;
		}
	}
	cout << "something went wrong";
	return false;
}
bool MyRestaurant::removeItem(unsigned int tableNumber, string productName, unsigned int quantity) {
	Product* temp = productList;
	if (tableAmount >= tableNumber) {
		while (temp != NULL) {
			if (temp->getName().compare(productName) == 0)
				if (tables[tableNumber - 1].removeOrder(productName, quantity)){
					cout << "removed " + to_string(quantity) + " " + productName + " from table " + to_string(tableNumber) + " oreder"<<endl;
					return true;
				}
			temp = temp->next;
		}
	}
	cout << "something went wrong";
	return false;
}
void MyRestaurant::removeTable(unsigned int tableNumber) {
	int flag = 0;
	if (tableAmount >= tableNumber) {
		Order* orders = tables[tableNumber - 1].getTableOrders();
		Product* products = productList;
		while (orders != NULL && flag == 0) {
			while (products != NULL && flag == 0) {
				if (orders->getName().compare(products->getName()) == 0) {
					if (products->getPremium()) {
						tables[tableNumber - 1].addPremiumToSum();
						flag = 1;
						break;
					}
				}
				products = products->next;
			}
			orders = orders->next;
			products = productList;
		}
		cout << tables[tableNumber - 1].toString();
		cout << "The table is free now";
		tables[tableNumber - 1].cleanTable();
	}
}
void MyRestaurant::reports(char a, unsigned int i) {
	string str;
	Product* pl;
	switch (a)
	{
	case 'A':
		str = "[Kitchen Report]\nProduct list:\n";
		pl = productList;
		if (pl == NULL) {
			str.append("is empty");
			cout<< str;
		}
		while (pl != NULL) {
			str.append(pl->toString() + '\n');
			pl = pl->next;
		}
		cout << str;
		break;

	case 'B':
		str = "[Total Orderd Report]\nTotal of products orderd today\n";
		pl = productList;
		while (pl != NULL) {
			str.append(pl->getName() + ": ");
			int x = pl->getQuantityOrderd();
			str.append(to_string(x) + '\n');
			pl = pl->next;
		}
		cout << str;
		break;

	case 'C':
		cout <<"[Table Status Report]\n" <<tables[i - 1].toString()<<"(not include premium tax)"<<endl;
		break;

	default:
		break;
	}
}
bool MyRestaurant::addItems(string productName, int quantity) {
	if (productList != NULL) {
		Product* head = productList;
		while ((head != NULL)) {
			string name = head->getName();
			if (name.compare(productName) == 0) {
				head->addQuant(quantity);
				cout << to_string(quantity)+" "+productName + " added to the kitchen "<<endl;
				return true;
			}
			head = head->next;
		}
	}
	cout << "something went wrong";
	return false;
}

Product* createProducts() {
	ifstream infile("Manot.txt");
	if (infile.is_open()) {
		string pName;
		unsigned int pQuant;
		unsigned int pPrice;
		char pPrem;
		bool prem;
		Product* head = NULL;
		Product* tail = NULL;
		while (infile >> pName >> pQuant >> pPrice >> pPrem) {
			if (pPrem == 'Y')
				prem = true;
			else
				prem = false;
			Product* temp = new Product(pName, pQuant, pPrice, prem);
			if (head != NULL) {
				tail->next = temp;
				tail = temp;
			}
			else {
				head = temp;
				tail = head;
			}
		}
		infile.close();
		cout << "product list created" << endl;
		return head;
	}
	cout << "something went wrong"<<endl;
	return NULL;
}
