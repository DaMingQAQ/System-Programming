/****************************************************************************
Name:        	Luan Nguyen - masc0638
        	Rene Placido - masc0620
        	Christian White - masc0621
Class:        	CS530, Spring 2015
Project:    	Assignment 2
File:        	Symtab.cpp
Note:        	Implementation file for class Symtab for storing and retrieving
        	symbols. Use multimap to store an address and its symbol name
        	and type.
****************************************************************************/

#include "Symtab.h"

using namespace std;

Symtab::Symtab(ifstream& inSym) {    //Loading symbols from input file stream
    inSym.ignore(numeric_limits<streamsize>::max(), '\n');
    inSym.ignore(numeric_limits<streamsize>::max(), '\n');
    string symbol;
    while(getline(inSym,symbol)) {
        if(symbol.empty()) {
            inSym.ignore(numeric_limits<streamsize>::max(), '\n');
            inSym.ignore(numeric_limits<streamsize>::max(), '\n');
            while(getline(inSym,symbol)) {    //Literal
                if(symbol.empty())
                    break;
                string litAddress = symbol.substr(24,6);
                litTab.insert(pair<string,string>(litAddress,symbol.substr(8,7)));
                litTab.insert(pair<string,string>(litAddress,symbol.substr(19,1)));
            }
            break;
        }
        string symAddress = symbol.substr(8,6);    //Symbol
        symAddress.erase(remove(symAddress.begin(),symAddress.end(),' '),symAddress.end());
        symTab.insert(pair<string,string>(symAddress,symbol.substr(0,6)));
        symTab.insert(pair<string,string>(symAddress,symbol.substr(16,1)));
    }
    regTab.insert(pair<string,string>("0","A"));    //Registers
    regTab.insert(pair<string,string>("1","X"));
    regTab.insert(pair<string,string>("2","L"));
    regTab.insert(pair<string,string>("3","B"));
    regTab.insert(pair<string,string>("4","S"));
    regTab.insert(pair<string,string>("5","T"));
    regTab.insert(pair<string,string>("6","F"));
    regTab.insert(pair<string,string>("8","PC"));
    regTab.insert(pair<string,string>("9","SW"));
}

multimap<string,string> Symtab::getSymTab() {    //Get a copy of Symtab
    multimap<string,string> myMap;
    for(multimap<string,string>::iterator it=symTab.begin();it!=symTab.end();++it)
        myMap.insert(pair<string,string>(it->first,it->second));
    return myMap;
}

multimap<string,string> Symtab::getAbsTab() {    //Get a table of only absolute symbols
    multimap<string,string> myAbsMap;
    multimap<string,string>::iterator tempIt;
    for(multimap<string,string>::iterator it=symTab.begin();it!=symTab.end();++it) {
        tempIt = it;
        if(((++it)->second).compare("A") == 0)
            myAbsMap.insert(pair<string,string>(tempIt->first,tempIt->second));
    }
    return myAbsMap;   

}

string Symtab::getRelSym(string inSym) {    //Get only relative symbol name
    stringstream inSymStr;
    inSymStr << setfill('0') << setw(6) << inSym;
    string newInSym = inSymStr.str();
    pair<multimap<string,string>::iterator,multimap<string,string>::iterator> itr;
    itr = symTab.equal_range(newInSym);
    string symName="";
    multimap<string,string>::iterator tempIt;
    for(multimap<string,string>::iterator it=itr.first;it!=itr.second;++it) {
        tempIt = it;
        if(((++it)->second).compare("R") == 0) {
            symName = tempIt->second;
            break;
        }
    }   
    return symName;
}

string Symtab::getReverseRel(string inSym) {    //Get the last relative symbol of the same address(for ORG)
    pair<multimap<string,string>::iterator,multimap<string,string>::iterator> itr;
    itr = symTab.equal_range(inSym);
    multimap<string,string> tempMap;
    for(multimap<string,string>::iterator rit=itr.first;rit!=itr.second;++rit)
        tempMap.insert(pair<string,string>(rit->first,rit->second));
    multimap<string,string>::reverse_iterator rit2;
    for(rit2=tempMap.rbegin();rit2!=tempMap.rend();++rit2) {
        if((rit2++->second).compare("R") == 0) {
            return rit2->second;
            break;
        }
    }
}

string Symtab::getAbsSym(string inSym) {    //Get only absolute symbol name
    pair<multimap<string,string>::iterator,multimap<string,string>::iterator> itr;
    itr = symTab.equal_range(inSym);
    string symName="";
    multimap<string,string>::iterator tempIt;
    for(multimap<string,string>::iterator it=itr.first;it!=itr.second;++it) {
        tempIt = it;
        if(((++it)->second).compare("A") == 0) {
            symName = tempIt->second;
            break;
        }
    }   
    return symName;
}

pair<string,string> Symtab::getLit(string litAdr) {    //Get literal name and its address
    if(litTab.count(litAdr) == 0)
        return make_pair("","");
    if(litAdr.size() != 6) {   
        stringstream newLitAdr;
        newLitAdr << setfill('0') << setw(6) << litAdr;
        litAdr = newLitAdr.str();
    }
    pair<multimap<string,string>::iterator,multimap<string,string>::iterator> itr;
    itr = litTab.equal_range(litAdr);
    string lit;
    string litLength;
    pair<string,string> litData;
    multimap<string,string>::iterator it = itr.first;
    lit = it->second;
    it++;
    litLength = it->second;
    litData = make_pair(lit,litLength);
    return litData;
}

string Symtab::getReg(string regNum) {    //Get name of register
    multimap<string,string>::iterator it = regTab.find(regNum);
    if(it == regTab.end())
        return "";
    return it->second;
}
