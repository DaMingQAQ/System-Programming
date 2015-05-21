/***************************************************************
 Name: 		Luan Nguyen – masc0638 (ALL FILES WILL BE IN THIS ACCOUNT)
		Rene Placido – masc0620
		Christian White – masc0621
 Class: 	CS530, Spring 2015
 Project: 	Assignment 2
 File:		README
 Note:		README file for assignment 2
***************************************************************/

Files:			Makefile, README, Disassembler.cpp, Symtab.cpp, Symtab.h, Optab.cpp, Optab.h, 
			printRec.h, printRec.cpp, calcAddress.h, calcAddress.cpp, converter.h, converter.cpp
Compile Instructions:	Run Makefile
Operating Instructions:	dasm <filename>.obj
Design Decisions:	Use of multiple files and standard library

The program main function is Disassembler.cpp. This function will use multiple files to help parsing the input object file:
	Symtab.cpp:
		The class that will be responsible for storing symbols and literals and their types from .sym file.
	Optab.cpp:
		The class that will be responsible for storing instruction code, mnemonic, and format. 
	printRec.cpp:
		This file will be responsible for printing out all three records from object file. It will also print 
		any data between each text record.
	calcAddress.cpp:
		This file will be responsible for calculating address for symbol during instruction.
	converter.cpp:
		This file will be responsible for converting between different variable types.

All methods in these files are designed to perform the task related to their name and file. Because of the ambiguity of 
disassembling, if a set of bytes cannot be determined as either instruction or data, then the program will print NULL in
all three fields and move on to the next set of bytes. Some data and address symbols may also be incorrect due to this
problem, and the source program might look different from the original source file.

The program structure will look like the following:
	Open and check if input file is correct (including .sym file).
		Populate the internal SYMTAB using .sym file, then load OPTAB.
		Retrieve and store modification record from file for determining whether operand is constant or an address.
		Retrieve and store only text record from file for calculating base register.
		Retrieve and store only the instruction code from text record (no starting address and length) for determining EQU symbols.
	Send to output stream header record.
	Send to output stream any EQU symbols.
	Get one Text Record and loop till there is no more.
