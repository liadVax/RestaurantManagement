#include "Header.h"

void main()
{
	MyRestaurant* myRes=NULL;
	int numberOfTables, inputZero;
	string line;
	
	do{
		cout << "Enter positive number of tables: ";
		cin >> numberOfTables;
		_flushall();
	} while (numberOfTables <= 0);
	printf("\nFunction 1 creates the products in the kitchen from the file Manot.");
	printf("\nFunction 2 adds quantity to an existed product.");
	printf("\nFunction 3 transfer a product from the kitchen to a table.");
	printf("\nFunction 4 returns a product from a table to the kitchen.");
	printf("\nFunction 5 close a table, prints all the products that was ordered to the table and the bill of the table.");
	printf("\nFunction 6 can show 3 types of report:");
	printf("\n\tA: Print the stock of the products in the kitchen.");
	printf("\n\tB: Print the number of times a product was ordered.");
	printf("\n\tC: Print the products that was ordered for a specific table.\n");

	//Open the file Instructions.txt.
	ifstream infile("Instructions.txt");
	if (!infile.is_open()) {
		printf("Failed to open file!");
		exit(1);
	}
	while (getline(infile, line)){
		int functionNum;
		istringstream iss(line);
		if (!(iss >> functionNum)) {
			cout << "Error reading";
			exit(1);
		}
		//Printing the functions tasks.
		do {
			cout << endl;
			printf("Please enter '0' to receive the next instruction to execute from the file \"Instructions.txt\" : ");
			cin >> inputZero;
			_flushall();
			if (inputZero != 0)
				printf("\tWrong input! please enter '0': ");
		} while (inputZero != 0);
		switch (functionNum)
		{
		case 1: //Function 1, "CreateProducts"
		{
			cout << "Function 1"<<endl;
			myRes =new MyRestaurant(numberOfTables, createProducts());
			break;
		}
		case 2: //Function 2, "Add_Items"
		{
			cout << "Function 2" << endl;
			string productName;
			int quantity;
			if (!(iss >> productName>>quantity)) {
				cout << "Error reading";
				exit(1);
			}
			myRes->addItems(productName, quantity);
			break;
		}
		case 3: //Function 3, "OrderItem"
		{
			cout << "Function 3" << endl;
			string productName;
			int quantity;
			unsigned int tableNumber;
			if (!(iss >> tableNumber>> productName >> quantity)) {
				cout << "Error reading";
				exit(1);
			}
			myRes->orderItem(tableNumber, productName, quantity);
			break;
		}
		case 4: //Function 4, "RemoveItem"
		{
			cout << "Function 4" << endl;
			string productName;
			unsigned int quantity;
			unsigned int tableNumber;
			if (!(iss >> tableNumber >> productName >> quantity)) {
				cout << "Error reading";
				exit(1);
			}
			myRes->removeItem(tableNumber, productName, quantity);
			break;
		}
		case 5: //Function 5, "RemoveTable"
		{
			cout << "Function 5" << endl;
			unsigned int tableNumber;
			if (!(iss >> tableNumber)) {
				cout << "Error reading";
				exit(1);
			}
			myRes->removeTable(tableNumber);
			break;
		}
		case 6: //Function 6, "Report"
		{
			cout << "Function 6" << endl;
			char report;
			int tableNumber;
			if (!(iss >> report >> tableNumber)) {
				cout << "Error reading";
				exit(1);
			}
			myRes->reports(report, tableNumber);
			break;
		}
		default: //In case function_num != 1-6
		{
			printf("Wrong function input!");
			break;
		}
		}
	}
	infile.close();
	myRes->~MyRestaurant();
	free(myRes);
	cin >> inputZero;
}

