#ifndef USEFUL_H
#define USEFUL_H

#include <string>
using namespace std;

bool isNumber(const string& target);


bool isNumber(const char& target);

bool isNegative(const string& target);

//converts string to unsigned integers.
unsigned int stoui(const string& str);

//converts char to unsigned integers.
unsigned int stoui(const char& ch);

string reverseStr(string str);

//converts unsigned integers to strings.
string uitos(const unsigned int& ui);

template<typename type, unsigned int N>
size_t sizeArray(type (&a)[N]);

bool detectedSpace(string s);


#include "../src/useful.cpp"


#endif

