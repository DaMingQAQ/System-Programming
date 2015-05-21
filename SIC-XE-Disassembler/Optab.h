/****************************************************************************
Name:        	Luan Nguyen - masc0638
        	Rene Placido - masc0620
        	Christian White - masc0621
Class:        	CS530, Spring 2015
Project:    	Assignment 2
File:        	Optab.h
Note:        	Header file for class Optab for storing and retrieving
        	instruction. Use multimap to store an opcode and its mnemonic
        	and format.
****************************************************************************/

#ifndef OPTAB_H
#define OPTAB_H

#include <map>
#include <string>
#include <utility>
#include <sstream>

class Optab {
private:
    std::multimap<std::string,std::string> opcode;
   
public:
    Optab();
    std::pair<std::string,std::string> getOp(std::string opCode);
};

#endif
