/*Arman Khondker
 *EID: aak2464
 *EE 312 - Project 8
 *
 */
#ifndef PROJECT_8_PROJECT8_H
#define PROJECT_8_PROJECT8_H
#include <iostream>
#include "String.h"
#include <vector>
#include <cstdlib>
#include "Parse.h"
#include <map>
using namespace std;

void run();
void initVar();
void setVar();
int polishRecursively(vector<String>& expr);
int operations(String op, int inputA, int arg2);
void blipGenerator();



#endif //PROJECT_8_PROJECT8_H
