/****************************************************************************
Name:        	Luan Nguyen - masc0638
        	Rene Placido - masc0620
        	Christian White - masc0621
Class:        	CS530, Spring 2015
Project:    	Assignment 2
File:        	converter.cpp
Note:        	Implementation file for functions to convert between different variable
        	types.
****************************************************************************/

#include "converter.h"

using namespace std;

int convertDecStringToInt(string inString) {
    return atoi(inString.c_str());
}

string convertStringHexToBin(string hexString) {
    unsigned int hexValue = strtoul(hexString.c_str(),NULL,16);
    bitset<4> hexBit(hexValue);
    string binString = hexBit.to_string<char,string::traits_type,string::allocator_type>();
    return binString;
}

string convertStringHexToDec(string hexString) {
    unsigned int decNum;
    stringstream hexStream;
    hexStream << hex << hexString;
    hexStream >> decNum;
    stringstream decStream;
    decStream << decNum;
    return decStream.str();
}

string convertIntToString(int inInt) {
    stringstream intString;
    intString << inInt;
    return intString.str();
}
