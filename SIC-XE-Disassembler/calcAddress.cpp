/****************************************************************************
Name:        	Luan Nguyen - masc0638
        	Rene Placido - masc0620
        	Christian White - masc0621
Class:        	CS530, Spring 2015
Project:    	Assignment 2
File:        	calAddress.cpp
Note:        	Implementation file for functions to calculate address and location
        	of symbols and instructions.
****************************************************************************/

#include "calcAddress.h"

using namespace std;

string incrementAdr(string loc, string incLength, int pcOpt) {    //pcOpt is flag for PC relative mode
    if(pcOpt == 3 && incLength[0] >= '8')    //Negative displacement
        incLength = "FFFFF" + incLength;
    int location;
    unsigned int length;
    stringstream locStream;
    locStream << hex << loc;
    locStream >> location;
    stringstream hexLength;
    hexLength << hex << incLength;
    hexLength >> length;
    stringstream finalLoc;
    finalLoc << hex << uppercase << setfill('0') << setw(6) << static_cast<int>(location)+length+pcOpt;
    return finalLoc.str();
}   

int subtractAdr(string lower, string upper) {
    int firstAdr;
    stringstream address1;
    address1 << hex << lower;
    address1 >> firstAdr;
    int secondAdr;
    stringstream address2;
    address2 << hex << upper;
    address2 >> secondAdr;
    stringstream diff;
    diff << hex << secondAdr - firstAdr;
    int result;
    diff >> result;
    return result;
}

string calcBase(string tempAdr, map<string,string> baseTxtRec, bool iFlag) {    //Calculate base register
    stringstream fullAdr;
    fullAdr << setfill('0') << setw(6) << tempAdr;
    string fullTempAdr = fullAdr.str();
    if(iFlag)    //Immediate operand
        return fullTempAdr;
    map<string,string>::iterator it = baseTxtRec.begin(); //Either simple or indirect
    string lastAdr = it->first;
    string lastCont = it->second;
    while((it->first).compare(fullTempAdr) <= 0) { //Skip to the target address passed in
        lastAdr = it->first;
        lastCont = it->second;
        it++;
        if(it==baseTxtRec.end())
            break;
    }
    if(fullTempAdr.compare(lastAdr) == 0)
        return lastCont.substr(0,6);
    else if(fullTempAdr.compare(lastAdr) > 0)
        return lastCont.substr(2*subtractAdr(lastAdr,fullTempAdr),6);

}
