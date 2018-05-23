/*
 * Name: Arman Khondker
 * EID: aak2464
 * Project 7, CRM part 2
 * EE 312, Spring 2018
 */

#include <stdio.h>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"
#include<iostream>
using namespace std;

void readString(String&);
void readNum(int&);

CustomerDB database;
int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;


/* clear the inventory and reset the customer database to empty */
void reset(void) {
	database.clear();
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the 
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(String word) {
	if (word == "Bottles") {
		return &num_bottles;
	} else if (word == "Diapers") {
		return &num_diapers;
	} else if (word == "Rattles") {
		return &num_rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
	if (word == "Bottles") {
		return &cust.bottles;
	} else if (word == "Diapers") {
		return &cust.diapers;
	} else if (word == "Rattles") {
		return &cust.rattles;
	}
	
	/* NOT REACHED */
	return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 * 
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the 
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
	Customer* result = 0;
	int max = 0;
	for (int k = 0; k < database.size(); k += 1) {
		Customer& cust = database[k];
		int *p = selectInventItem(type, cust); 
		if (*p > max) {
			max = *p;
			result = &cust;
		}
	}
	
	return result;
}

void processPurchase()
{
    String Name;	                    //the name of the customer from the file
    String item;		                //the type of item they are purchasing from the file
    int quantity = 0;                   //the amount they are going to purchase if able to
    readString(Name);
    readString(item);
    readNum(quantity);

    if (quantity == 0)
    {
        return;
    }

    if (*selectInventItem(item) >= quantity)
    {
        *selectInventItem(item) = *selectInventItem(item) - quantity;              //subtract out the quantity from the inventory of store
        *selectInventItem(item, database[Name]) = *selectInventItem(item, database[Name]) + quantity;   //add the quantity to the customer

    }
    else if (*selectInventItem(item) < quantity)
    {
        cout << "Sorry "<< Name.c_str() << ", we only have " << *selectInventItem(item)<< " " <<item.c_str() << endl;
    }
}

void processSummarize()
{
    cout << "There are "<< num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory" << endl;
    cout << "we have had a total of " << database.size() << " different customers" << endl;

    Customer* mostBottles = findMax("Bottles");      //pointer to customer who purchased the most bottles
    Customer* mostDiapers = findMax("Diapers");      //pointer to customer who purchased the most diapers
    Customer* mostRattles = findMax("Rattles");      //pointer to customer who purchased the most rattles

    if (mostBottles > 0)
    {
        cout <<mostBottles->name.c_str() << " has purchased the most Bottles (" << mostBottles->bottles << ")" << endl;
    }
    else
    {
        cout <<"no one has purchased any Bottles" <<endl;

    }

    if (mostDiapers > 0)
    {
        cout <<mostDiapers->name.c_str() << " has purchased the most Diapers (" << mostDiapers->diapers << ")" << endl;
    }
    else
    {
        cout <<"no one has purchased any Diapers" <<endl;
    }

    if (mostRattles > 0)
    {
        cout <<mostRattles->name.c_str() << " has purchased the most Rattles (" << mostRattles->rattles << ")" << endl;
    }
    else
    {
        cout <<"no one has purchased any Rattles" <<endl;
    }

}

void processInventory()
{
    String item;		                      //name of the item
    int quantity = 0;		                //num of item to add
    readString(item);
    readNum(quantity);

    *selectInventItem(item)= *selectInventItem(item) + quantity;        //add the quantity to the inventory of selected item

}
