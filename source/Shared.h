#include "MicroBit.h"
#include <map>

//This is extern because the memory is allocated in our shard.h
//this means that it is effectivly shared between any .h file that also declares
//extern uBit has 'extern' (pls be true). ps. it's because it's .init elsewhere

#define DASH '-'
#define DOT '.'
#define BREAK 'B'

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
const int alphabet[36] = {
  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
  'W','X','Y','Z','1','2','3','4','5','6','7','8','9','0'
};



extern MicroBit uBit; //Our instantiation
extern message userMessage;

extern map<string,char> morseMap;
