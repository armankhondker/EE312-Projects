// Set <Project5.cpp>
// EE 312 Project 5 submission by
// <Arman Khondker>
// <aak2464>
// Slip days used: <0>
// Spring 2018


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }

	destroySet(self);
	createCopySet(self, other);
}
bool binarySearch(int *set, int len, int n)
{
    int start = 0;
    int end = len - 1;
    int mid = 0;

    while (start <= end)
    {
        mid = (start + end) / 2;  //reset the middle everytime

        if (set[mid] == n)      // if you find the item then you are done with the function
        {
            return true;
        }
        if (set[mid] > n)
        {
            end = mid - 1;          //change the end value
        }
        else
        {
            start = mid + 1;           //change the start value
        }
    }

    return false;
}
/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x)
{
    if (isEmptySet(self))
    {
        return false;
    }
    int length = self->len;
    int* a = self->elements;
    bool flag = binarySearch(a, length, x);  //search the set for x and assign flag to its value;
    return flag;        //returns whether or not x is an element in self

}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x)
{
    int* insertedSet = (int*)malloc(4 + (self->len) * sizeof(int));

    if (isEmptySet(self))
    {
        insertedSet[0] = x;      //insert the item into the set
        self->len++;            //set the appropriate length
        free(self->elements);
        self->elements=insertedSet;          //reassign the elements to the malloced insertedSet
        return;
    }
    else
    {
        int counter = 0;        //this variable will be used to see if x is greater than all of the elements

        for(int i=0; i<self->len; i++)
        {
            if (self->elements[i] == x)     //if the element already exists then break this function
            {
                free(insertedSet);
                return;
            }

            else if (self->elements[i] < x)                 //if x is greater than ith element then keep going
            {
                insertedSet[i] = self->elements[i];         //copy the ith element into insertedSet
                counter++;
                if(counter==self->len)      //this means that this else statement has been taken everytime thus we need to insert
                {
                    insertedSet[self->len] = x;     //insert x at the end of insertedSet
                    self->len++;
                    free(self->elements);
                    break;                  //stop the for loop from continuing
                }

            }
            else if(self->elements[i] > x)          //this means that we are in the correct position to insert x
            {
                insertedSet[i] = x;
                int j=i+1;          //variable used to access the ith + 1 element of the array
                for (i; i < self->len; i++)         //used to copy the rest of the elements
                {
                    insertedSet[j] = self->elements[i];
                    j++;           //must also increment j here
                }
                self->len += 1;
                free(self->elements);
                break;
            }

        }
        self->elements = insertedSet;

    }


}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x)
{
    if(isEmptySet(self))            //if empty then nothing to remove
    {
        return;
    }
    for(int i=0; i<self->len; i++)
    {
        if(self->elements[i]==x)            //if we have reached the element we want to remove
        {
            int j= i+1;        //set this variable to access the next element
            for(i; i< self->len-1; i++)         //needs to be len-1 because we are removing an element
            {
                self->elements[i]=self->elements[j];
                j++;

            }
            self->len=self->len-1;
            break;

        }

    }

}

/* done for you already */
void displaySet(const Set* self)
{
	int k;

	printf("{");

	if (self->len == 0) {
		printf("}");
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other)
{
    if (self->len == other->len)        //lengths have to be same if they are going to have same elements
    {
        for (int i = 0; i< self->len; i++)
        {
            if (other->elements[i] != self->elements[i])            //if any element not the same then return false
            {
                return false;
            }
        }
        return true;

    }
    else    //can only reach here if lengths aren't the same thus must return false
    {
        return false;
    }

}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other)
{
    if (isEmptySet(self))                  //if self is empty then it will always be subset
    {
        return true;
    }
    if (self->len > other->len)        //if self len is bigger then can't be a subset
    {
        return false;
    }

    int j=0;

   for(int i=0; i<self->len; i++)
   {

       if(j>=other->len)
       {
           return false;
       }

       if(self->elements[i]==other->elements[j])
       {
           j++;
       }

       else if(self->elements[i] < other->elements[j])  //if the jth element of other is bigger than self then every element of self isn't an element of other
           {
               return false;
           }
       else             //in this case only increment the j index and keep i index the same
           {
               j++;
               i--;
           }
   }
    return true;

}

/* done for you */
bool isEmptySet(const Set* self)
{
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other)
{
    if (self->len == 0)  //if length is 0 then function has to do nothing
    {
        return;
    }
    if(isEqualToSet(self,other)) //if they are equal then no elements need to be removed
    {
        return;
    }

    int* intersection = (int*)malloc(sizeof(int)*self->len);

    if (isEmptySet(other))
    {
        free(self->elements);
        self->elements = intersection;
        self->len = 0;
        return;
    }

        int intersectionIndex=0;
        int intersectionLength=0;
        int j=0;
        int i=0;


        for(i=0; i<self->len; i++)
        {   if(j >= other->len)  //this means you have gone through all elements of other, thus you can stop looping
            {
                break;
            }
            else
            {
                if (self->elements[i] == other->elements[j])        //we have an intersection
                {
                    intersection[intersectionIndex] = self->elements[i];        //put the ith element into intersection
                    intersectionIndex++;
                    intersectionLength++;
                    j++;
                }
                else if (self->elements[i] > other->elements[j])        //in this case only increment the other index but keep i index the same
                {
                    j++;            //keep searching for intersection
                    i--;
                }
                else   //only reach this if jth element of other is bigger than ith element of self, in this case do nothing
                {
                    continue;
                }
            }
        }
    free(self->elements);
    self->elements = intersection;
    self->len = intersectionLength;

}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other)
{
    int* subtraction = (int*)malloc(sizeof(int)*(self->len));
    int subtractionIndex =0;
    int subtractionLength=0;  //variable to store the length of the subtraction

    if (isEmptySet(self))
    {
        free(subtraction);
        return;
    }
    if(isEmptySet(other))
    {
        free(subtraction);
        return;
    }

    int j=0;
    int i=0;

   while(i < self->len)
   {
        if(j>=other->len)   //in this case copy the ith element and increment indexes
        {
            subtraction[subtractionIndex]=self->elements[i];    //copy rest of elements
            subtractionIndex++;
            subtractionLength++;
            i++;
        }
        else
        {
            if (self->elements[i] < other->elements[j])         //if ith element of self is less than other than copy element and increase indexes
            {
                subtraction[subtractionIndex] = self->elements[i];
                subtractionIndex++;
                subtractionLength++;
                i++;
            }
            else if (self->elements[i] > other->elements[j])        // in this case only increment j index
            {
                j++;
            }
            else        //in this case they are equal so just increment the indexes
            {
                j++;
                i++;
            }
        }
    }

    free(self->elements);
    self->elements = subtraction;
    self->len = subtractionLength;

}



/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other)
{
    int* unionOfSets= (int*)malloc((self->len + other->len) * sizeof(int)); // must be combined size of self and other

    if (isEmptySet(other))
    {
        free(unionOfSets);      //unused so free it
        return;
    }

    int j=0;
    int unionOfSetsIndex=0;
    int unionOfSetsLength=0;
    int i=0;

    while(i < other->len)
    {
        if (j < self->len)
        {
            if (other->elements[i] == self->elements[j])
            {
                unionOfSets[unionOfSetsIndex] = other->elements[i];  //copy the ith element of other into the union
                j++;
                unionOfSetsIndex++;
                unionOfSetsLength++;
                i++;

            }
            else if (other->elements[i] > self->elements[j])    //can't skip over the jth element of self
            {
                unionOfSets[unionOfSetsIndex] = self->elements[j];  //copy the jth element of self
                j++;
                unionOfSetsIndex++;
                unionOfSetsLength++;

            }
            else  //this means ith element of other is greater than jth element of self
            {
                unionOfSets[unionOfSetsIndex] = other->elements[i]; //copy the ith element of other
                unionOfSetsIndex++;
                unionOfSetsLength++;
                i++;
            }

        }
        else if(j >= self->len)   //this means stop incrementing j because we reached the end of self
        {
            unionOfSets[unionOfSetsIndex] = other->elements[i]; //copy rest of the elements
            unionOfSetsIndex++;
            unionOfSetsLength++;
            i++;
        }
    }

    if (j < self->len)      //this means we havent copied all of the elements from self
    {
        while(j < self->len)
        {
            unionOfSets[unionOfSetsIndex] = self->elements[j];  //copy the rest of the self elements
            unionOfSetsIndex++;
            unionOfSetsLength++;
            j++;
        }
    }
    free(self->elements);
    self->elements = unionOfSets;
    self->len = unionOfSetsLength;


}
