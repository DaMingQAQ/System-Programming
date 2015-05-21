/****************************************************************************
Name:        	Luan Nguyen - masc0638
        	Rene Placido - masc0620
        	Christian White - masc0621
Class:        	CS530, Spring 2015
Project:    	Assignment 2
File:        	Optab.cpp
Note:        	Implementation file for Optab.h. All instructions are in XE
        	(last 2 bits set to 1)
****************************************************************************/

#include "Optab.h"

using namespace std;

Optab::Optab() {
    opcode.insert(pair<string,string>("1B","ADD"));
    opcode.insert(pair<string,string>("1B","3/4"));
    opcode.insert(pair<string,string>("5B","ADDF"));
    opcode.insert(pair<string,string>("5B","3/4"));
    opcode.insert(pair<string,string>("93","ADDR"));
    opcode.insert(pair<string,string>("93","2"));
    opcode.insert(pair<string,string>("43","AND"));
    opcode.insert(pair<string,string>("43","3/4"));
    opcode.insert(pair<string,string>("B7","CLEAR"));
    opcode.insert(pair<string,string>("B7","2"));
    opcode.insert(pair<string,string>("2B","COMP"));
    opcode.insert(pair<string,string>("2B","3/4"));
    opcode.insert(pair<string,string>("8B","COMPF"));
    opcode.insert(pair<string,string>("8B","3/4"));
    opcode.insert(pair<string,string>("A3","COMPR"));
    opcode.insert(pair<string,string>("A3","2"));
    opcode.insert(pair<string,string>("27","DIV"));
    opcode.insert(pair<string,string>("27","3/4"));
    opcode.insert(pair<string,string>("67","DIVF"));
    opcode.insert(pair<string,string>("67","3/4"));
    opcode.insert(pair<string,string>("9F","DIVR"));
    opcode.insert(pair<string,string>("9F","2"));
    opcode.insert(pair<string,string>("C7","FIX"));
    opcode.insert(pair<string,string>("C7","1"));
    opcode.insert(pair<string,string>("C3","FLOAT"));
    opcode.insert(pair<string,string>("C3","1"));
    opcode.insert(pair<string,string>("F7","HIO"));
    opcode.insert(pair<string,string>("F7","1"));
    opcode.insert(pair<string,string>("3F","J"));
    opcode.insert(pair<string,string>("3F","3/4"));
    opcode.insert(pair<string,string>("33","JEQ"));
    opcode.insert(pair<string,string>("33","3/4"));
    opcode.insert(pair<string,string>("37","JGT"));
    opcode.insert(pair<string,string>("37","3/4"));
    opcode.insert(pair<string,string>("3B","JLT"));
    opcode.insert(pair<string,string>("3B","3/4"));
    opcode.insert(pair<string,string>("4B","JSUB"));
    opcode.insert(pair<string,string>("4B","3/4"));
    opcode.insert(pair<string,string>("03","LDA"));
    opcode.insert(pair<string,string>("03","3/4"));
    opcode.insert(pair<string,string>("6B","LDB"));
    opcode.insert(pair<string,string>("6B","3/4"));
    opcode.insert(pair<string,string>("53","LDCH"));
    opcode.insert(pair<string,string>("53","3/4"));
    opcode.insert(pair<string,string>("73","LDF"));
    opcode.insert(pair<string,string>("73","3/4"));
    opcode.insert(pair<string,string>("0B","LDL"));
    opcode.insert(pair<string,string>("0B","3/4"));
    opcode.insert(pair<string,string>("6F","LDS"));
    opcode.insert(pair<string,string>("6F","3/4"));
    opcode.insert(pair<string,string>("77","LDT"));
    opcode.insert(pair<string,string>("77","3/4"));
    opcode.insert(pair<string,string>("07","LDX"));
    opcode.insert(pair<string,string>("07","3/4"));
    opcode.insert(pair<string,string>("D3","LPS"));
    opcode.insert(pair<string,string>("D3","3/4"));
    opcode.insert(pair<string,string>("23","MUL"));
    opcode.insert(pair<string,string>("23","3/4"));
    opcode.insert(pair<string,string>("63","MULF"));
    opcode.insert(pair<string,string>("63","3/4"));
    opcode.insert(pair<string,string>("9B","MULR"));
    opcode.insert(pair<string,string>("9B","2"));
    opcode.insert(pair<string,string>("CB","NORM"));
    opcode.insert(pair<string,string>("CB","1"));
    opcode.insert(pair<string,string>("47","OR"));
    opcode.insert(pair<string,string>("47","3/4"));
    opcode.insert(pair<string,string>("DB","RD"));
    opcode.insert(pair<string,string>("DB","3/4"));
    opcode.insert(pair<string,string>("AF","RMO"));
    opcode.insert(pair<string,string>("AF","2"));
    opcode.insert(pair<string,string>("4F","RSUB"));
    opcode.insert(pair<string,string>("4F","3/4"));
    opcode.insert(pair<string,string>("A7","SHIFTL"));
    opcode.insert(pair<string,string>("A7","2"));
    opcode.insert(pair<string,string>("AB","SHIFTR"));
    opcode.insert(pair<string,string>("AB","2"));
    opcode.insert(pair<string,string>("F3","SIO"));
    opcode.insert(pair<string,string>("F3","1"));
    opcode.insert(pair<string,string>("EF","SSK"));
    opcode.insert(pair<string,string>("EF","3/4"));
    opcode.insert(pair<string,string>("0F","STA"));
    opcode.insert(pair<string,string>("0F","3/4"));
    opcode.insert(pair<string,string>("7B","STB"));
    opcode.insert(pair<string,string>("7B","3/4"));
    opcode.insert(pair<string,string>("57","STCH"));
    opcode.insert(pair<string,string>("57","3/4"));
    opcode.insert(pair<string,string>("83","STF"));
    opcode.insert(pair<string,string>("83","3/4"));
    opcode.insert(pair<string,string>("D7","STI"));
    opcode.insert(pair<string,string>("D7","3/4"));
    opcode.insert(pair<string,string>("17","STL"));
    opcode.insert(pair<string,string>("17","3/4"));
    opcode.insert(pair<string,string>("7F","STS"));
    opcode.insert(pair<string,string>("7F","3/4"));
    opcode.insert(pair<string,string>("EB","STSW"));
    opcode.insert(pair<string,string>("EB","3/4"));
    opcode.insert(pair<string,string>("87","STT"));
    opcode.insert(pair<string,string>("87","3/4"));
    opcode.insert(pair<string,string>("13","STX"));
    opcode.insert(pair<string,string>("13","3/4"));
    opcode.insert(pair<string,string>("1F","SUB"));
    opcode.insert(pair<string,string>("1F","3/4"));
    opcode.insert(pair<string,string>("5F","SUBF"));
    opcode.insert(pair<string,string>("5F","3/4"));
    opcode.insert(pair<string,string>("97","SUBR"));
    opcode.insert(pair<string,string>("97","2"));
    opcode.insert(pair<string,string>("B3","SVC"));
    opcode.insert(pair<string,string>("B3","2"));
    opcode.insert(pair<string,string>("E3","TD"));
    opcode.insert(pair<string,string>("E3","3/4"));
    opcode.insert(pair<string,string>("FB","TIO"));
    opcode.insert(pair<string,string>("FB","1"));
    opcode.insert(pair<string,string>("2F","TIX"));
    opcode.insert(pair<string,string>("2F","3/4"));
    opcode.insert(pair<string,string>("BB","TIXR"));
    opcode.insert(pair<string,string>("BB","2"));
    opcode.insert(pair<string,string>("DF","WD"));
    opcode.insert(pair<string,string>("DF","3/4"));
}

pair<string,string> Optab::getOp(string opCode) {    //Retrieve both mnemonic and format using iterator
    if(opcode.count(opCode) == 0)
        return make_pair("","");
    pair<multimap<string,string>::iterator, multimap<string,string>::iterator> itr;
    itr = opcode.equal_range(opCode);
    string maskedOp;
    string opFormat;
    pair<string,string> opData;
    multimap<string,string>::iterator it = itr.first;
    maskedOp = it->second;
    it++;
    opFormat = it->second;
    opData = make_pair(maskedOp,opFormat);
    return opData;
}
