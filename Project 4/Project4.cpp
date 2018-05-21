// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// <Arman Khondker>
// <aak2464>
// Slip days used: <0>
// Spring 2018


#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"
#include <stdlib.h>


#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
Customer store;                 //The store will be global variable for inventory
int rattleFlag = 0;          //flag to let us know a rattle has been purchased
int diaperFlag = 0;          // flag to let us know a diaper has been purchased
int bottleFlag= 0;          //flag to let us know a bottle has been purchased

bool isOurCustomer(String* customer);
int currentCustomerIndex(String* customer);
int indexOfMostBottles();
int indexOfMostDiapers();
int indexOfMostRattles();

/* clear the inventory and reset the customer database to empty */
void reset(void)
{

    store.bottles=0;
    store.diapers=0;
    store.rattles=0;
    num_customers = 0;
    bottleFlag=0;
    rattleFlag=0;
    diaperFlag=0;

    int i =1;                     //start at 1 because index 0 is the store inventory itself which will be cleared later
    while( i <= num_customers)
    {
        customers[i].bottles = 0;
        customers[i].diapers = 0;
        customers[i].rattles = 0;
        customers[i].name.ptr[0] = 0;
        StringDestroy(&customers[i].name);
        i++;
    }


}

void processSummarize()
{
    int bottleIndex = indexOfMostBottles();
    int rattleIndex = indexOfMostRattles();
    int diaperIndex = indexOfMostDiapers();
    printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", store.bottles, store.diapers, store.rattles);
    printf("we have had a total of %d different customers\n", num_customers);

    if(bottleFlag==1)
    {   StringPrint(&customers[bottleIndex].name);
        printf(" has purchased the most Bottles (%d)\n", customers[bottleIndex].bottles);
    }

    else
    {
        printf("no one has purchased any Bottles\n");
    }

    if(diaperFlag==1)
    {
        StringPrint(&customers[diaperIndex].name);
        printf(" has purchased the most Diapers (%d)\n", customers[diaperIndex].diapers);
    }

    else
    {
        printf("no one has purchased any Diapers\n");
    }

    if(rattleFlag==1)
    {
        StringPrint(&customers[rattleIndex].name);
        printf(" has purchased the most Rattles (%d)\n", customers[rattleIndex].rattles);

    }

    else
    {
        printf("no one has purchased any Rattles\n");
    }

}

void processPurchase()
{
    String Name;	                    //the name of the customer from the file
    String item;		                //the type of item they are purchasing from the file
    int quantity = 0;                   //the amount they are going to purchase if able to
    readString(&Name);
    readString(&item);
    readNum(&quantity);

    if (quantity == 0)
    {
        StringDestroy(&Name);
        StringDestroy(&item);
        return;  //stop the function
    }
    else
    {


        if (item.ptr[0] == 'B')
        {
            if (store.bottles != 0 && store.bottles >= quantity)
            {
                if (isOurCustomer(&Name) == 0)       //if false then we will create new customer
                {
                    num_customers = num_customers + 1;
                    customers[num_customers].name = StringDup(&Name);
                    customers[num_customers].bottles += quantity;
                    store.bottles = store.bottles - quantity;
                    bottleFlag = 1;
                }
                else
                {
                    int index = currentCustomerIndex(&Name);
                    customers[index].bottles += quantity;
                    store.bottles = store.bottles - quantity;
                    bottleFlag = 1;
                }
            }
            else
            {
                printf("Sorry ");
                StringPrint(&Name);
                printf(", we only have %d ", store.bottles);
                StringPrint(&item);
                printf("\n");
            }
        }
        else if (item.ptr[0] == 'D')
        {
            if (store.diapers != 0 && store.diapers >= quantity)
            {
                if (isOurCustomer(&Name) == 0)       //if false then we will create new customer
                {
                    num_customers = num_customers + 1;
                    customers[num_customers].name = StringDup(&Name);
                    customers[num_customers].diapers += quantity;
                    store.diapers = store.diapers - quantity;
                    diaperFlag = 1;
                }
                else
                {
                    int index = currentCustomerIndex(&Name);
                    customers[index].diapers += quantity;
                    store.diapers = store.diapers - quantity;
                    diaperFlag = 1;
                }

            }
            else
            {
                printf("Sorry ");
                StringPrint(&Name);
                printf(", we only have %d ", store.diapers);
                StringPrint(&item);
                printf("\n");
            }
        }
        else if (item.ptr[0] == 'R')
        {
            if (store.rattles != 0 && store.rattles >= quantity)
            {
                if (isOurCustomer(&Name) == 0)       //if false then we will create new customer
                {
                    num_customers = num_customers + 1;
                    customers[num_customers].name = StringDup(&Name);
                    customers[num_customers].rattles += quantity;
                    store.rattles = store.rattles - quantity;
                    rattleFlag = 1;
                }
                else
                {
                    int index = currentCustomerIndex(&Name);
                    customers[index].rattles += quantity;
                    store.rattles = store.rattles - quantity;
                    rattleFlag = 1;
                }
            }
            else
            {
                printf("Sorry ");
                StringPrint(&Name);
                printf(", we only have %d ", store.rattles);
                StringPrint(&item);
                printf("\n");
            }
        }
    }

    StringDestroy(&Name);
    StringDestroy(&item);

}

void processInventory()
{
    String item;		               //name of the item
    int num;		                //num of item to add
    readString(&item);
    readNum(&num);

    if(item.ptr[0]=='B')    //if it is a bottle
    {
        store.bottles = store.bottles + num;
    }

    if(item.ptr[0]=='D')   //if it is a diaper
    {
        store.diapers = store.diapers + num;
    }

    if(item.ptr[0]=='R')  //if it is a rattle
    {
        store.rattles = store.rattles + num;
    }

    StringDestroy(&item);
}

/* Returns true if the pointer to the String ADT passed is a previous customer and false if a new customer */
bool isOurCustomer(String* customer)
{
    for (int i = 0; i <= num_customers; i++)
    {
        if (StringIsEqualTo(&customers[i].name, customer))  //checks to see if name has been recorded already
        {
            return true;
        }
    }
    return false;
}

/*Returns the index of the customer when passed a pointer to a String ADT*/
int currentCustomerIndex(String* customer)
{   int index=1;
    for (int i = 1; i <= num_customers; i++)
    {
        if (StringIsEqualTo(&customers[i].name, customer))
        {
            index=i;
        }
    }
    return index;
}

/* Returns the index of the customer with the most purchased Bottles*/
int indexOfMostBottles()
{   int index =0;
    int currentMax=0;
    for (int i = 1; i <= num_customers; i++)
    {
        int curIndexValue = customers[i].bottles;
        if (curIndexValue > currentMax) {
            currentMax = curIndexValue;
            index = i;
        }
    }
    return index;
}

/* Returns the index of the customer with the most purchased Diapers*/
int indexOfMostDiapers()
{   int index = 0;
    int currentMax=0;
    for (int i = 1; i <= num_customers; i++)
    {
        int curIndexValue = customers[i].diapers;
        if (curIndexValue > currentMax)
        {
            currentMax = curIndexValue;
            index = i;
        }
    }
    return index;
}

/* Returns the index of the customer with the most purchased Rattles*/
int indexOfMostRattles()
{   int index =0;
    int currentMax=0;
    for (int i = 1; i <= num_customers; i++)
    {
        int curIndexValue = customers[i].rattles;
        if (curIndexValue > currentMax)
        {
            currentMax = curIndexValue;
            index = i;
        }
    }
    return index;
}

