/****************************************************************************
Name:        	Luan Nguyen - masc0638
        	Rene Placido - masc0620
        	Christian White - masc0621
Class:        	CS530, Spring 2015
Project:    	Assignment 2
File:        	converter.h
Note:        	Header file for functions to convert between different variable
        	types.
****************************************************************************/

#ifndef CONVERTER_H
#define CONVERTER_H

#include <sstream>
#include <string>
#include <bitset>

int convertDecStringToInt(std::string inString);
std::string convertIntToString(int inInt);
std::string convertStringHexToBin(std::string hexString);
std::string convertStringHexToDec(std::string hexString);

#endif
