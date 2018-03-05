/*
* File: main.cpp
* Author: Dominic Lewis
* Date: 20180304
* Desc: IOT Assignment 02
 */
#include "MicroBit.h"

//Prototypes
void on_button_a(MicroBitEvent);
void on_button_b(MicroBitEvent);

MicroBit uBit; //Our instantiation
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_DIGITAL); //Send
MicroBitPin P1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL); // Listen
//buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);

/*
*Purpose: Event handler for a button
*Accepts: Event object
*Returns: N/A
*/
void on_button_a(MicroBitEvent e) //Move left
{

if (buttonA.isPressed()){


  uBit.display.scrollAsync("Test");
}
}
/*
*Purpose: Event handler for b button, moves the player right
*Accepts: Event object
*Returns: N/A
*/
void on_button_b(MicroBitEvent e)
{

}

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    //Listeners below
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, on_button_a);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, on_button_b);

    // we use asunc here, to allow the led to start flashing straight away,
    // i.e. not have to wait for message to be displayed
    //uBit.display.scrollAsync("Blinky");
    while(1){

        // turn LED on
        P0.setDigitalValue(1);
        if (P1.getDigitalValue() == 1){
          uBit.display.print("D");
        }
        uBit.sleep(5000);
        P0.setDigitalValue(0);
        if (P1.getDigitalValue() == 0 ){
          uBit.display.print("L");
        }
        uBit.sleep(5000);

    }
    release_fiber();
    }
