#include "MicroBit.h"
#include <map>

//This is extern because the memory is allocated in our shard.h
//this means that it is effectivly shared between any .h file that also declares
//extern uBit has 'extern' (pls be true). ps. it's because it's .init elsewhere

void send();
void listen(); //prototypes
void on_button_a();
void on_button_b();
void getMessage();


//Messagestruct
struct message{
char buffer [200]; //Big
int tail = 0; //tracks the index
};
//Vars
const int alphabet[26] = {
  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
  'W','X','Y','Z'
};



extern MicroBit uBit; //Our instantiation
extern message userMessage;

extern map<string,char> morseMap;
