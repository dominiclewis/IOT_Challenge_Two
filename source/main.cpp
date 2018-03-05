/*

*/
/*
*/
/*
* File: main.cpp
* Author: Dominic Lewis
* Date: 20180304
* Desc: IOT Assignment 02
 */
#include "MicroBit.h"

void togglePint();
MicroBit uBit; //Our instantiation
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_DIGITAL); //Send
MicroBitPin P1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL); // Listen
void togglePin(){
  uBit.display.print("X");

}
int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    // we use asunc here, to allow the led to start flashing straight away,
    // i.e. not have to wait for message to be displayed
    //uBit.display.scrollAsync("Blinky");
    while(1){

        // turn LED on
        P0.setDigitalValue(1);
        if (P1.getDigitalValue() == 1){
          togglePin();
        }
        uBit.sleep(5000);
        P0.setDigitalValue(0);
        if (P1.getDigitalValue() == 0 ){
          uBit.display.print("L");
        }
        uBit.sleep(5000);

        // turn LED off
        //P1.setDigitalValue(0);
        //uBit.sleep(500);
    }
    }

    //release_fiber();
