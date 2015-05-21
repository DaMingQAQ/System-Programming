/***************************************************************
Name:         Luan Nguyen
username:     masc0638
Class:        CS530, Spring 2015
Project:      Assignment 1
File:         hexdump.cpp
Note:         Main function for printing hex dump
***************************************************************/

#include <fstream>
#include <unistd.h>
#include "print.h"

using namespace std;

void printUsage() {
    cout << "Usage: xsd <filename> or xxd -b <filename>" << endl;
}
   
int main(int argc, char* argv[]) {
    extern int optind;    /* Use optind to determine the index of the file */
    int opt;
    int binFlag = 0;    /* Use flag to determine what mode to print */
    unsigned long address = 0;
   
    if(argc <= 1 || argc > 3) {
        printUsage();
        exit(1);
    }
   
    while((opt = getopt(argc, argv, "b")) != -1) {
        switch (opt) {
        case 'b':
            binFlag = 1;
            break;
        default:
            printUsage();
            exit(1);
        }
    }
   
    if(argc == 3 && binFlag == 0) {
        printUsage();
        exit(1);
    }

    ifstream inFile(argv[optind], ios::binary | ios::in);
   
    if(!inFile) {
        cout << "File not found!" << endl;
        exit(1);
    }
   
    if(inFile.peek() == istream::traits_type::eof()) {    /* Check if file is empty by going to the end and check for eof */
        cout << "File is empty!" << endl;
        exit(1);
    }
   
    if(!binFlag) {
        while(inFile) {
            char hexBuf[HEX_LENGTH] = {};
            inFile.read(hexBuf,HEX_LENGTH);
            int charCount = inFile.gcount();
            printHex(hexBuf,address,charCount);
            address += HEX_LENGTH;
        }
    }
    else {
        while(inFile) {
            char binBuf[BIN_LENGTH] = {};
            inFile.read(binBuf,BIN_LENGTH);
            int charCount = inFile.gcount();
            printBin(binBuf,address,charCount);
            address += BIN_LENGTH;
        }
    }
   
    inFile.close();
    return 0;
}
