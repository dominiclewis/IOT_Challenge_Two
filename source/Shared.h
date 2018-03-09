/*
* File: main.cpp
* Author: Dominic Lewis
* Date: 20180304
* Desc: IOT Assignment 02
* Note: Encode as a summative int eg. A  = DOT + DASH etc
 */
#include "MicroBit.h"
#include <map>

#define DASH '-'
#define DOT '.'
#define BREAK '*'
#define MIN 0
#define MAX 36

void send();
void listen(); //prototypes
void on_button_a();
void on_button_b();
void getMessage();
void getChars();


//Messagestruct
struct message{
char buffer [200]; //Big
int tail = 0; //tracks the index
char charBuffer [200];
int charBuffTail = 0;

};
//Vars
const int alphabet[37] = {
  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
  'W','X','Y','Z','1','2','3','4','5','6','7','8','9','0',' '
};



extern MicroBit uBit; //Our instantiation
extern message userMessage;

extern map<string,char> morseMap;
