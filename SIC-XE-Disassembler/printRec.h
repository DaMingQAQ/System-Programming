/****************************************************************************
Name:        	Luan Nguyen - masc0638
        	Rene Placido - masc0620
        	Christian White - masc0621
Class:        	CS530, Spring 2015
Project:    	Assignment 2
File:        	printRec.h
Note:        	Header file for functions to print out all records.
****************************************************************************/

#ifndef PRINTREC_H
#define PRINTREC_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include "Symtab.h"
#include "calcAddress.h"
#include "converter.h"

void printHeader(std::string label, std::string beginAdr,std::ofstream& inStream);
void printText(std::string label, std::string mnemonic, std::string operand, std::ofstream& inStream, bool xFlag, bool eFlag, bool nFlag, bool iFlag);
void printEnd(std::string endRec, std::ofstream& inStream);
void printRes(Symtab& inSymTab, std::string lastTxtRec, std::string textRecAdr,std::ofstream& inStream);

#endif
