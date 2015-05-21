#****************************************************************************
# Name:        	Luan Nguyen - masc0638
#         	Rene Placido - masc0620
#        	Christian White - masc0621
# Class:    	CS530, Spring 2015
# Project:    	Assignment 2
# File:        	Makefile
# Note:        	Makefile to compile all source files
#****************************************************************************

OBJS = Disassembler.o Symtab.o Optab.o printRec.o converter.o calcAddress.o
CC = g++

dasm: $(OBJS)
    $(CC) $(OBJS) -o dasm

Disassembler.o: Disassembler.cpp Optab.h Symtab.h printRec.h converter.h calcAddress.h
    $(CC) -c Disassembler.cpp

converter.o: converter.cpp converter.h
    $(CC) -c converter.cpp

calcAddress.o: calcAddress.cpp calcAddress.h
    $(CC) -c calcAddress.cpp
   
Optab.o: Optab.cpp Optab.h
    $(CC) -c Optab.cpp

Symtab.o: Symtab.cpp Symtab.h
    $(CC) -c Symtab.cpp

printRec.o: printRec.cpp printRec.h
    $(CC) -c printRec.cpp

clean:
    rm *.o out
