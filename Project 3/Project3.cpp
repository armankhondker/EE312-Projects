// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Arman Khondker
// aak2464
// Slip days used: <0>
// Spring 2018
// Copy and paste this file at the top of all your submitted source code files.

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "String.h"

#define SIGNATURE (~0xdeadbeef)

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s)
{
    if (CHECK(s) == SIGNATURE)
    { return true;
    }
    else
    { return false;
    }
}

/* 
 * Allocate a utstring on the heap. 
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src)
{
    UTString* String = (UTString*)malloc(sizeof(UTString));              //allocate space for a UT String
    String->string = (char*)malloc(sizeof(char)*(strlen(src)+5));         //1 for null and 4 for 0xdeadbeef
    String->capacity = strlen(src);
    String->length = strlen(src);
    uint32_t length=strlen(src);
    for (uint32_t i = 0; i <= length; i++)             // <= in order to copy the null
    {
        String->string[i] = src[i];
    }
    CHECK(String)=SIGNATURE;       //add 0xdeadbeef to end of string
    return String;

}

/* 
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s)
{

    assert(isOurs(s));
    uint32_t length;
    length = strlen(s->string);
    return length;

}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s. 
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix)
{
    assert(isOurs(s));
    uint32_t length = s->length;
    uint32_t capacity = s-> capacity;
    uint32_t i=0;
    while(capacity>length && suffix[i]!=0)
    {
        s->string[length]=suffix[i];
        length++;
        i++;
    }
    s->length+=i;
    s->string[length]='\0';
    CHECK(s)=SIGNATURE;           //add the 0xdeadbeef
    return s;
}

/* 
 * Copy src into dst.
 *  dst must be a valid UTString. 
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst. 
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src)
{
    assert(isOurs(dst));
    uint32_t capacity= dst->capacity;
    uint32_t sourceLength=strlen(src);
    uint32_t i=0;
    for(i=0; (i < capacity) && (i < sourceLength); i++)            //loop only while i is less than capacity and source length
    {
        dst->string[i] = *(src + i);
    }
    dst->string[i]='\0';                   //append the null
    dst->length=i;                         //set the length because it has been changed
    CHECK(dst)=SIGNATURE;
    return dst;

}

/*
 * Free all memory associated with the given UTString. 
 */
void utstrfree(UTString* self)
{
    assert(isOurs(self));
    free(self->string);         //free the string first because it was allocated last
    free(self);

}

/* 
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity, 
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata. 
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity)
{
    assert(isOurs(s));
    if(s->capacity<new_capacity)
    {
        s->capacity = new_capacity;
        s->string = (char *) realloc(s->string, sizeof(char)*(new_capacity + 5));      //realloc space
        return s;
    }
    else                  //nothing needs to be done so just return the UT string as is
    {
        return s;
    }

}
