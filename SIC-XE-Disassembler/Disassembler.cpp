/****************************************************************************
Name:		Luan Nguyen - masc0638
		Rene Placido - masc0620
		Christian White - masc0621
Class:		CS530, Spring 2015
Project:    	Assignment 2
File:		Disassembler.cpp
Note:		Main function for reading object file and printing source file
****************************************************************************/

#include "Optab.h"
#include "Symtab.h"
#include "printRec.h"
#include "converter.h"
#include "calcAddress.h"
#include <vector>
#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>

using namespace std;

//Turn last 2 bits into 11
string maskOpBit(string opCode) {
    unsigned int opValue;
    stringstream opStream;
    opStream << hex << opCode;
    opStream >> opValue;
    bitset<8> opBin(opValue);
    opBin.set(0);
    opBin.set(1);
    stringstream opString;
    opString << setfill('0') << setw(2) << hex << uppercase << opBin.to_ulong();
    string result = opString.str();
    return result;
}

int main(int argc, char* argv[]) {
    //Open and check for input file
    if(argc <= 1 || argc > 2) {
        cout << "Usage: dasm <filename>.obj" << endl;
        exit(1);
    }
    string inFile = argv[1];
    int extPosition = inFile.find_last_of(".");
    if(inFile.substr(extPosition+1) != "obj") {
        cout << "Wrong file extension!" << endl;
        exit(1);
    }
    ifstream objFile(argv[1], ios::in);
    if(!objFile) {
        cout << "File not found!" << endl;
        exit(1);
    }
    if(objFile.peek() == istream::traits_type::eof()) {
        cout << "File is empty!" << endl;
        exit(1);
    }
    string fileName = inFile.substr(0,extPosition);
    ifstream symFile((fileName + ".sym").c_str(), ios::in);
    if(!symFile) {
        cout << "File not found!" << endl;
        exit(1);
    }
    if(symFile.peek() == istream::traits_type::eof()) {
        cout << "File is empty!" << endl;
        exit(1);
    }
    ofstream outFile((fileName + ".sic").c_str());
   
    Optab thisOpTab;
    Symtab thisSymTab(symFile);
   
    //Retrieving Mod Record to figure out if operand is constant or an address
    vector<string> modRec;
    string modLine;
    while(getline(objFile,modLine)) {
        if(modLine[0] != 'M')
            continue;
        modRec.push_back(modLine.substr(1,6));
    }
    objFile.clear();
    objFile.seekg(0,objFile.beg);
   
    //Retrieving text record for finding LDB
    map<string,string> baseTxtRec;
    string baseTxtLine;
    while(getline(objFile,baseTxtLine)) {
        if(baseTxtLine[0] != 'T')
            continue;
        baseTxtRec.insert(pair<string,string>(baseTxtLine.substr(1,6),baseTxtLine.substr(9)));
    }
    objFile.clear();
    objFile.seekg(0,objFile.beg);

    //Loading text record for finding EQU
    string testEQU;
    string equLine;
    while(getline(objFile,equLine)) {
        if(equLine[0] != 'T')
            continue;
        testEQU = testEQU + equLine.substr(9);
    }
    objFile.clear();
    objFile.seekg(0,objFile.beg);

    //Print header record
    string headRec;
    getline(objFile,headRec);
    string label = headRec.substr(1,6);
    string beginAdr = headRec.substr(7,6);
    string progLength = headRec.substr(13,6);
    printHeader(label,beginAdr,outFile);
   
    //Parsing EQU by loading all absolute symbols and remove any that shows up in object code
    multimap<string,string> absMap = thisSymTab.getAbsTab();
    int pos = 0;
    int tempPos = pos;
    multimap<string,string>::iterator equIt;
    while(pos < testEQU.size()) {
        int equCount = 1;
        try {    //If moving pass the end, stop checking
            while((equIt = absMap.find(testEQU.substr(pos,2))) == absMap.end()) {    //Check each byte (up to 3 bytes)
                if(pos < 4)
                    break;
                pos += 2;
            }
            if(equIt == absMap.end()) {    //Check up to 3 consecutive bytes
                while((equIt = absMap.find(testEQU.substr(tempPos,equCount*2))) == absMap.end()) {
                    if(equCount < 3)
                        break;
                    ++equCount;
                }
            }
        }
        catch(out_of_range& e) {
            break;
        }
        pos += equCount*2;
        tempPos = pos;
        if(equIt != absMap.end())
            absMap.erase(equIt);
    }
    for(multimap<string,string>::iterator it=absMap.begin();it!=absMap.end();++it)    //Any remaining absolute symbols will be EQU
        printText(it->second,"EQU",it->first,outFile,false,false,false,false);
                   
    string textRec;
    string opMnemonic="";
    string operand;
    string baseAdr;
    string lastTxtRec = beginAdr;        //Used for RESB/W at the end of each text record
    string textRecAdr;

    //Read every text record       
    while(getline(objFile,textRec)) {
        if(textRec[0] != 'T') {        //If at the last text record, check for RESB/W
            textRecAdr = progLength;
            if(lastTxtRec.compare(textRecAdr) != 0)
                printRes(thisSymTab,lastTxtRec,textRecAdr,outFile);
            break;
        }
        int counter = 9;
        textRecAdr = textRec.substr(1,6);
        string textRecLength = textRec.substr(7,2);
        string loc = textRecAdr;
        int maxLoc = textRec.length();

        //RESB,RESW at end of record
        if(lastTxtRec.compare(textRecAdr) != 0)    
            printRes(thisSymTab,lastTxtRec,textRecAdr,outFile);
        lastTxtRec = incrementAdr(textRecAdr,textRecLength,0);
   
        while(counter < maxLoc) { //Stop when arriving at the last character in object file
            try{
                label = "";
                //Checking if instruction with symbol or RESB/W
                string relSym = thisSymTab.getRelSym(loc);
                if(relSym.compare("") != 0) {
                    if((textRec.substr(counter,2)).compare("00") == 0) {    //RESB/W in middle of text record
                        int dataCount = 1;                //Check till a non-zero is found
                        string resData = textRec.substr(counter,dataCount*2);
                        string tempResData = resData;
                        while((tempResData.erase(0,tempResData.find_first_not_of('0'))).compare("") == 0) {
                            ++dataCount;
                            resData = textRec.substr(counter,dataCount*2);
                            tempResData = resData;
                        }
                        --dataCount;
                        if(dataCount%3==0)     //Determine exact size of data reserved
                            printText(relSym,"RESW",convertIntToString(dataCount/3),outFile,false,false,false,false);
                        else
                            printText(relSym,"RESB",convertIntToString(dataCount),outFile,false,false,false,false);
                        loc = incrementAdr(loc,convertIntToString(dataCount),0);
                        counter += dataCount*2;
                        continue;
                    }
                    else                            //Otherwise it is instruction
                        label = relSym;
                }
                //Check for literal
                pair<string,string> litData = thisSymTab.getLit(loc);
                if((litData.first).compare("") != 0) {
                    string litLength = litData.second;
                    string literal = litData.first;
                    if((literal.substr(1,1)).compare("X") == 0) { //A hex literal
                        counter += convertDecStringToInt(litLength);
                        loc = incrementAdr(loc,"1",0);
                    }
                    else {    //A character literal
                        counter += convertDecStringToInt(litLength)*2;
                        loc = incrementAdr(loc,litLength,0);
                    }
                    printText("","LTORG","",outFile,false,false,false,false);
                    continue;
                }
                //Determine instruction
                bool eFlag = false;
                bool xFlag = false;
                bool nFlag = false;
                bool iFlag = false;
                bool isInstruction = false;
                string opCode = textRec.substr(counter,2);
                string format = "";
                pair<string,string> opData = thisOpTab.getOp(maskOpBit(opCode)); //Get opcode by masking last 2 bits
                string tempAdr = "";
                if((opData.first).compare("") != 0) {
                    isInstruction = true;        //Parse instruction
                    opMnemonic = opData.first;
                    format = opData.second;
                    if(format.compare("1") == 0)     //Format 1
                        operand = "";
                    else if(format.compare("2") == 0) {    //Format 2
                        string firstRegNum = textRec.substr(counter+2,1);
                        string secondRegNum = textRec.substr(counter+3,1);
                        if(secondRegNum.compare("0") == 0)
                            operand = thisSymTab.getReg(firstRegNum);
                        else
                            operand = thisSymTab.getReg(firstRegNum) + "," + thisSymTab.getReg(secondRegNum);
                        if(operand.compare("") == 0 || operand.compare(",") == 0)
                            isInstruction = false;
                    }
                    else {        //Format 3
                        string niFlags = convertStringHexToBin(opCode.substr(1,1));
                        string xbpeFlags = convertStringHexToBin(textRec.substr(counter+2,1));
                        pair<string,string> symName("","");
                        if(niFlags[2] == '1' && niFlags[3] == '1') {    //Simple
                            if(xbpeFlags[0] == '1')
                                xFlag = true;
                        }
                        else if(niFlags[2] == '0' && niFlags[3] == '1')     //Immediate
                            iFlag = true;
                        else if(niFlags[2] == '1' && niFlags[3] == '0')     //Indirect
                            nFlag = true;
                        if(xbpeFlags[1] == '0' && xbpeFlags[2] == '0' && xbpeFlags[3] == '1') {            //e=1
                            tempAdr = textRec.substr(counter+3,5);
                            eFlag = true;
                        }
                        else if(xbpeFlags[1] == '0' && xbpeFlags[2] == '1' && xbpeFlags[3] == '0') {        //p=1
                            tempAdr = textRec.substr(counter+3,3);   
                            tempAdr = incrementAdr(loc,tempAdr,3);
                        }
                        else if(xbpeFlags[1] == '1' && xbpeFlags[2] == '0' && xbpeFlags[3] == '0') {        //b=1
                            tempAdr = textRec.substr(counter+3,3);
                            tempAdr = incrementAdr(baseAdr,tempAdr,0);
                        }
                        else if(xbpeFlags[1] == '0' && xbpeFlags[2] == '0' && xbpeFlags[3] == '0')        //direct
                            tempAdr = textRec.substr(counter+3,3);
                        else
                            isInstruction = false;
                        //Look for symbol name
                        symName = thisSymTab.getLit(tempAdr);        //operand = literal
                        if((symName.first).compare("") == 0) {        //operand = symbol
                            symName.first = thisSymTab.getRelSym(tempAdr);
                            if((symName.first).compare("") == 0)    //operand = constant
                                symName.first = tempAdr;
                        }
                        operand = symName.first;
                        //If immediate, check if constant or an address by checking mod record
                        if(iFlag && xbpeFlags[1] != '1' && xbpeFlags[2] != '1') {
                            if(find(modRec.begin(),modRec.end(),incrementAdr(loc,"1",0)) == modRec.end())
                                operand = convertStringHexToDec(tempAdr);
                        }
                    }
                }
                //Check if BYTE/WORD
                if(!isInstruction) {
                    int count = 1;
                    string dataValue="";
                    string dataSym="";
                    while(count <= 3) {    //Check up to 3 consecutive bytes
                        dataValue = textRec.substr(counter,count*2);
                        dataSym = thisSymTab.getAbsSym(dataValue);
                        ++count;
                    }
                    if(dataSym.compare("") != 0) {    //Found
                        if(count==3)
                            printText(dataSym,"WORD",dataValue,outFile,false,false,false,false);
                        else
                            printText(dataSym,"BYTE",dataValue,outFile,false,false,false,false);
                        loc = incrementAdr(loc,convertIntToString(count),0);
                        counter += count*2;
                        continue;
                    }
                    else {        //If byte cannot be determined, then it is an error from guessing
                        outFile << "NULL    " << "NULL    " << "NULL" << endl;
                        counter += 2;
                        loc = incrementAdr(loc,"1",0);
                    }
                }   
               
                if(format.size() != 1 && eFlag)        //format 3/4, then 4
                    format = format.substr(2,1);
                else
                    format = format.substr(0,1);    //format 1,2
                //Increment location for next parsing
                loc = incrementAdr(loc,format,0);   
                counter += convertDecStringToInt(format)*2;
           
                if(opMnemonic.compare("RSUB") == 0)
                    operand = "";
                printText(label,opMnemonic,operand,outFile,xFlag,eFlag,nFlag,iFlag);
                //Load Base Register
                if(opMnemonic.compare("LDB") == 0) {
                    baseAdr = calcBase(tempAdr,baseTxtRec,iFlag);   
                    if(nFlag)
                        baseAdr = calcBase(baseAdr,baseTxtRec,false);
                    printText("","BASE",operand,outFile,false,false,false,false);
                }
            }
            catch(out_of_range& e) { //Pass the end of current text record
                outFile << "NULL    " << "NULL    " << "NULL" << endl;
                break;
            }
        }
    }
    //End record
    while(textRec[0]!='E')
        getline(objFile,textRec);
    string endRec = textRec;
    printEnd(endRec,outFile);

    symFile.close();
    objFile.close();
    outFile.close();
    return 0;
}
