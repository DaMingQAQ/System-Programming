/****************************************************************************
Name:        	Luan Nguyen - masc0638
        	Rene Placido - masc0620
        	Christian White - masc0621
Class:        	CS530, Spring 2015
Project:    	Assignment 2
File:        	printRec.cpp
Note:        	Implementation file for functions to print out all records.
****************************************************************************/

#include "printRec.h"

using namespace std;

void printHeader(string label, string beginAdr,ofstream& inStream) { //Header record
    if(beginAdr.compare("000000") == 0)    //If operand is 0, only print out one "0"
        inStream << setw(6) << label << setw(3) << " " << "START" << "  " << "0" << endl;
    else    //Delete leading zero and print
        inStream << setw(6) << label << setw(3) << " " << "START" << "  " << beginAdr.erase(0,beginAdr.find_first_not_of('0')) << endl;
}

void printText(string label, string mnemonic, string operand, ofstream& inStream, bool xFlag, bool eFlag, bool nFlag, bool iFlag) { //Text record
    string tempMne = mnemonic; //Formatting the output
    mnemonic = " " + mnemonic;
    string tempOp = operand;
    operand = " " + operand;
    if(operand.compare("0") == 0 || operand.compare("00") == 0 || operand.compare("000") == 0|| operand.compare("0000") == 0 || operand.compare("00000") == 0 || operand.compare("000000") == 0)
        operand = "0";
    if(eFlag)
        mnemonic = "+"+tempMne;
    if(operand.compare("0") != 0)
        operand = operand.erase(0,operand.find_first_not_of('0'));   
    if(nFlag)
        operand = "@"+tempOp;
    else if(iFlag)
        operand = "#"+tempOp;
    if(xFlag)
        operand = operand+",X";
    inStream << label << setw(8-label.size()) << " "  << mnemonic << setw(8-mnemonic.size()) << " " << operand << endl;
}

void printEnd(string endRec, ofstream& inStream) {    //End record
    if(endRec.size() > 0)    //Operand in END directive
        inStream << "        " << "END    " << endRec.substr(1,6) << endl;
    else    //No operand
        inStream << "        " << "END" << endl;
}

void printRes(Symtab& inSymTab, string lastTxtRec, string textRecAdr, ofstream& inStream) { //Calculate and print RESB/W after each text record
    multimap<string,string> resSymTab = inSymTab.getSymTab();
    multimap<string,string>::iterator it = resSymTab.begin();
    multimap<string,string>::iterator tempIt;
    while((it->first).compare(lastTxtRec) < 0){    //Skip to current location from beginning of symbol table
        it++;
        it++;
    }
    tempIt = it;
    while(((++tempIt)->second).compare("A") == 0) {        //Skip absolute symbols at the start
        it++;
        it++;
        tempIt=it;
    }
    string prevSym = it->first;
    it++;
    it++;       
    bool orgFlag = false;
    string orgStop = "";
    int remainLen=0;
    string symName="";
    int resLength=0;
    while((it->first).compare(textRecAdr) <= 0) {
        tempIt = it;
        if(((++tempIt)->second).compare("A") == 0) {        //Skip similar absolute symbols during RESB/W
            it++;
            it++;
            if(it==resSymTab.end() || (it->first).compare(textRecAdr) > 0) {
                if(prevSym.compare(textRecAdr) != 0) {
                    symName = inSymTab.getRelSym(prevSym);
                    resLength = subtractAdr(prevSym,textRecAdr);
                    if(resLength%3==0)
                        inStream << symName << "  RESW    " << convertIntToString(resLength/3) << endl;
                    else
                        inStream << symName << "  RESB    " << convertIntToString(resLength) << endl;   
                }
                if(orgStop.compare("") != 0)
                    inStream << "        ORG    " << orgStop << endl;
                break;   
            }
            continue;
        }
        resLength = subtractAdr(prevSym,it->first);
        if(orgFlag) {
            symName = inSymTab.getReverseRel(prevSym);
            orgFlag=false;
        }
        else
            symName = inSymTab.getRelSym(prevSym);       
        if(resLength == 0) {    //If two relative symbols that have same address, then it's ORG
            remainLen = subtractAdr(prevSym,textRecAdr);
            if(remainLen%3==0)
                inStream << symName << "  RESW    " << convertIntToString(remainLen/3) << endl;
            else
                inStream << symName << "  RESB    " << convertIntToString(remainLen) << endl;
            inStream << "        ORG    " << symName << endl;
            orgFlag = true;
            orgStop = symName+"+"+convertIntToString(remainLen);
        }
        else {    //Otherwise just RESB/W
            if(resLength%3==0)
                inStream << symName << "  RESW    " << convertIntToString(resLength/3) << endl;
            else
                inStream << symName << "  RESB    " << convertIntToString(resLength) << endl;
        }
        prevSym = it->first;
        it++;
        it++;
        if(it==resSymTab.end() || (it->first).compare(textRecAdr) > 0) {    //If pass the end of symbol table and max length of current text record,
                                                                            //calculate the remaining data.
            if(prevSym.compare(textRecAdr) != 0) {
                symName = inSymTab.getRelSym(prevSym);
                resLength = subtractAdr(prevSym,textRecAdr);
                if(resLength%3==0)
                    inStream << symName << "  RESW    " << convertIntToString(resLength/3) << endl;
                else
                    inStream << symName << "  RESB    " << convertIntToString(resLength) << endl;   
            }
            if(orgStop.compare("") != 0)
                inStream << "        ORG    " << orgStop << endl;
            break;   
        }       
    }   
}
