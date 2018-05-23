/*
 * Name: Arman Khondker
 * EID: aak2464
 * Project 7, CRM part 2
 * EE 312, Spring 2018
 *
 */
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;
const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

Customer& CustomerDB::operator[](String name)
{
    if(isMember(name) == false)       //if it isn't a member then you need to check capacity and add the new customer
    {
        if (this->capacity <= this->length)
        {
            this->capacity = this->capacity * 2;

            Customer *biggerDatabase = new Customer[this->capacity];      //need this to have twice the capacity

            for (int i = 0; i < this->length; i++)
            {
                biggerDatabase[i] = this->data[i];         //copy over current data
            }

            delete[] this->data;
            this->data = biggerDatabase;

        }

        Customer newCustomer(name);                    //create the new customer with the name as the string name
        this->length++;
        int lastIndex = this->length - 1;
        this->data[lastIndex] = newCustomer;
        return this->data[lastIndex];

    }
    else            // can only reach here if the item is a member already, in that case case just return it
    {
        int z=0;

        while( z < this->length)
      {
          if (this->data[z].name == name)
          {
              return this->data[z];
          }

          z++;
      }

    }

}

bool CustomerDB::isMember(String name)
{
   for (int i = 0; i < this->length; i++)
    {
        if (this->data[i].name == name)
        {
            return true;
        }
    }
    return false;

}
