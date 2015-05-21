/********************************************************************
Name:         Luan Nguyen
username:     masc0638
Class:        CS530, Spring 2015
Project:      Assignment 1
File:         print.cpp
Note:         Implementation of header file for printing hex dump
********************************************************************/

#include <bitset>
#include "print.h"

using namespace std;

void printHex(const char* hexBuf,unsigned long &address,int &charCount) {
    cout << hex << setw(ADDRESS_L) << setfill('0') << address;
    cout << ":";
    for(int i=0; i<HEX_LENGTH; i++) {
        if(i%2 == 0)
            cout << " ";    /* Add space between each 2-byte */
        if(i >= charCount)
            cout << "  ";    /* Output blank space to fit the format */
        else {
            unsigned int hexChar = static_cast<unsigned char>(hexBuf[i]);    /* Cast to unsigned char to get 0-255 value range. Then cast to unisgned int to output hex value */
            cout << setfill('0') << setw(2) << hexChar;
        }
    }
    cout << "  ";
    for(int i=0; i<charCount; i++) {
        if(hexBuf[i] < 32)    /* Human-readable range is > 32 */
            cout << '.';
        else
            cout << hexBuf[i];
    }
    cout << endl;
}

void printBin(const char* binBuf,unsigned long &address,int &charCount) {
    cout << hex << setw(ADDRESS_L) << setfill('0') << address;
    cout << ":";
    for(int i=0; i<BIN_LENGTH; i++) {
        if(i >= charCount)
            cout << "        ";
        else {
            bitset<8> binChar(binBuf[i]);    /* Use bitset to store 8 bits of one char */
            cout << " " << binChar;
        }
    }
    cout << "  ";
    for(int i=0; i<charCount; i++) {
        if(binBuf[i] < 32)
            cout << '.';
        else
            cout << binBuf[i];
    }
    cout << endl;
}
