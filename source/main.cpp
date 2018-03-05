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
void listen();
void send();

MicroBit uBit; //Our instantiation
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_DIGITAL); //Send
MicroBitPin P1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL); // Listen
buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A); //Can use to get button A time
bool readMode = true; //If false then it's in send mode

/*
*Purpose: Event handler for a button
*Accepts: Event object
*Returns: N/A
*/
void on_button_a(MicroBitEvent e) //Move left
{

//if (buttonA.isPressed()){
  uBit.display.scrollAsync("Test");
//}
}

/*
*Purpose: Event handler for b button, moves the player right
*Accepts: Event object
*Returns: N/A
*/
void on_button_b(MicroBitEvent e)
{
  readMode = !readMode;//inverts it
  if (readMode){
      uBit.display.scroll("Listen Mode"); //Not async so we don't block main fiber
  } else{
    uBit.display.scroll("Send Mode");
  }

}

/*
*Purpose: Logic for the microbit while it's listening
*Accepts: N/A
*Returns: (void)
*Note: Listen on pin 1
*/
void listen(){
  if (P1.getDigitalValue() == 1){ //Listen on p1
    uBit.display.printAsync("HV");
  } else{
    uBit.display.printAsync("LV");
  }
}

/*
*Purpose: Logic for the microbit while it's transmitting a message
*Accepts: N/A
*Returns:(void)
*Note: Send on pin 0
*/
void send(){
  //Toggle LED
  P0.setDigitalValue(1);

  uBit.sleep(500);
  P0.setDigitalValue(0);

}

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
    //Listeners below
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, on_button_a);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, on_button_b);

    while(1){
        if (readMode){
          //Read
          listen();
        } else{
          //Sending
          send();
        }
    uBit.sleep(500);
    }
    release_fiber();
    }
