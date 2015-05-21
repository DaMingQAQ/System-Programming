/***************************************************************
Name:         	Luan Nguyen
username:     	masc0638
Class:     	CS530, Spring 2015
Project:     	Assignment 3
File:        	myParser.c
Note:        	Simple parser for CS 530 Assignment 3 Spring 2015.
        	Grammar:
          		<Z> ::= <S> { <S> } $
          		<S> ::= char = <E>;
          		<E> ::= <V> {( + | - ) <V>}
          		<V> ::= <P> {( * | / ) <P>}
          		<P> ::= <C> ^ <P> | <C>
          		<C> ::= char | ( <E> ) | digit
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char next;
void S(void);
void E(void);
void V(void);
void P(void);
void C(void);
void scan(void);
void enter(char);
void leave(char);
void spaces(int);
void error(int);
int level = 0;

void S(void)    //<S>
{
    enter('S');
    if(isalpha(next)) {
        scan();
    if(next == '=') {
        scan();
            E();
        if(next == ';')
            scan();
        else
            error(1);
    }
    else {
            error(2);
    }
    }
    else {
        error(3);
    }
    leave('S');
}

void E(void)    //<E>
{
  enter('E');
  V();
  while (next == '+' || next == '-') {
      scan();
      V();
  }
  leave('E');
}

void V(void)    //<V?
{
  enter('V');
  P();
  while (next == '*' || next == '/') {
      scan();
      P();
  }
  leave('V');
}

void P(void)    //<P>
{
  enter('P');
  C();
  if (next == '^') {
      scan();
      P();
  }
  leave('P');
}

void C(void)    //<C>
{
  enter('C');
  if (isalpha(next)) {
      scan();
  }
  else if (next == '(') {
      scan();
      E();
      if (next == ')')
          scan();
      else
          error(4);
  }
  else if(isdigit(next)) {
      scan();
  }
  else {
      error(5);
  }
  leave('C');
}

void scan(void)        //Skip any space and read next token
{
  while (isspace(next = getchar()))
      ;
}

void enter(char name)    //Print out message when entering a grammar
{
  spaces(level++);
  printf("+-%c: Enter, \t", name);
  printf("Next == %c\n", next);
}

void leave(char name)    //Print out message when leaving a grammar
{
  spaces(--level);
  printf("+-%c: Leave, \t", name);
  printf("Next == %c\n", next);
}

void spaces(int local_level)    //Help clarify where the parsing process is currently at
{
  while (local_level-- > 0)
      printf("| ");
}

void error(int n)
{
  printf("\n*** ERROR: %i\n", n);
  exit(1);
}

void main(void)        //<Z>
{
  scan();
  S();
  while(next != '$')
      S();
  printf("Successful parse\n");
}
