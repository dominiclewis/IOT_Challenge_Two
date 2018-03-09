#include "MicroBit.h"

extern MicroBit uBit; //Our instantiation
//This is extern because the memory is allocated in our shard.h
//this means that it is effectivly shared between any .h file that also declares
//extern uBit has 'extern' (pls be true). ps. it's because it's .init elsewhere

void send();
void listen(); //prototypes
void on_button_a();
void on_button_b();

//bool mode = false; //true = send, false = listen
