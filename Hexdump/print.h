/***************************************************************
Name:         Luan Nguyen
username:     masc0638
Class:        CS530, Spring 2015
Project:      Assignment 1
File:         print.h
Note:         Header file of functions for printing hex dump
***************************************************************/

#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <iomanip>

const int HEX_LENGTH = 16;
const int BIN_LENGTH = 6;
const int ADDRESS_L = 7;

void printHex(const char* hexBuf, unsigned long &address, int &charCount);
void printBin(const char* binBuf, unsigned long &address, int &charCount);

#endif
