/*
* File: main.cpp
* Author: Dominic Lewis
* Date: 20180304
* Desc: IOT Assignment 02
*/

#include "MicroBit.h";

MicroBit uBit; //Instantiate the uBit object

int main(){
  uBit.init(); //Initialise the scheduler
  uBit.display.scroll("Hello World");
  release_fiber();

}
