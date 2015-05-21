/****************************************************************************
Name:        	Luan Nguyen - masc0638
        	Rene Placido - masc0620
        	Christian White - masc0621
Class:        	CS530, Spring 2015
Project:    	Assignment 2
File:        	Symtab.h
Note:        	Header file for class Symtab for storing and retrieving
        	symbols. Use multimap to store an address and its symbol name
        	and type.
****************************************************************************/

#ifndef SYMTAB_H
#define    SYMTAB_H

#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <iomanip>
#include <sstream>
#include <algorithm>

class Symtab {
private:
    std::multimap<std::string,std::string> symTab;
    std::multimap<std::string,std::string> litTab;
    std::multimap<std::string,std::string> regTab;
   
public:
    Symtab(std::ifstream& inSym);
    std::string getRelSym(std::string inSym);
    std::string getAbsSym(std::string inSym);
    std::string getReverseRel(std::string inSym);
    std::pair<std::string, std::string> getLit(std::string litAdr);
    std::multimap<std::string, std::string> getSymTab();
    std::multimap<std::string, std::string> getAbsTab();
    std::string getReg(std::string regNum);
};

#endif
