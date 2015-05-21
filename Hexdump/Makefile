#***************************************************************
# Name:     	Luan Nguyen
# username:     masc0638
# Class:     	CS530, Spring 2015
# Project:     	Assignment 1
# File:        	Makefile
# Note:        	Makefile to compile source files
#****************************************************************

OBJS = hexdump.o print.o
CC = g++

xsd: $(OBJS)
    $(CC) $(OBJS) -o xsd

hexdump.o: hexdump.cpp print.h
    $(CC) -c hexdump.cpp

print.o: print.cpp print.h
    $(CC) -c print.cpp

clean:
    rm *.o xsd
