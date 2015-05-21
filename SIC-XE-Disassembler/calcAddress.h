/****************************************************************************
Name:		Luan Nguyen - masc0638
        	Rene Placido - masc0620
        	Christian White - masc0621
Class:        	CS530, Spring 2015
Project:    	Assignment 2
File:        	calAddress.h
Note:        	Header file for functions to calculate address and location
        	of symbols and instructions.
****************************************************************************/

#ifndef CALCADDRESS_H
#define CALCADDRESS_H

#include <sstream>
#include <string>
#include <bitset>
#include <iomanip>
#include <map>

std::string incrementAdr(std::string loc, std::string incLength, int pcOpt);
int subtractAdr(std::string lower, std::string upper);
std::string calcBase(std::string tempAdr, std::map<std::string,std::string> baseTxtRec, bool iFlag);

#endif
