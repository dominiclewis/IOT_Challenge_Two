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

struct message{
int buffer [100]; //Big
int tail = 0; //tracks the index
};

MicroBit uBit; //Our instantiation
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_DIGITAL); //Send
MicroBitPin P1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL); // Listen
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A); //Can use to get button A time
message userMessage;
bool readMode = true; //If false then it's in send mode


/*
*Purpose: Event handler for a button
*Accepts: Event object
*Returns: N/A
*/
void on_button_a(MicroBitEvent e) //Move left
{

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
/*  P0.setDigitalValue(1);
  uBit.sleep(500);
  P0.setDigitalValue(0);
  */
  bool pressed = false;

  while(buttonA.isPressed()){
    uint64_t startTime = system_timer_current_time(); //Get start time
    while(buttonA.isPressed()){
      pressed = true;
    }
    //Get the delta (the difference)
    uint64_t delta = system_timer_current_time() - startTime;
    //uBit.display.print((int)delta);
    if (pressed){
      if( (delta >= 300) && (delta <= 1000)){
        //long press
        userMessage.buffer[userMessage.tail] = 1;
        userMessage.tail += 1;
        uBit.display.print("-"); //1
        uBit.sleep(500);
      } else if(delta < 300){
        //short press
        userMessage.buffer[userMessage.tail] = 0;
        userMessage.tail += 1;
        uBit.display.print(".");//0
        uBit.sleep(500);
      }else if(delta > 4000){
      //Send Yo
      uBit.display.print(userMessage.tail);
      uBit.sleep(2000);
        uBit.display.clear();
        if(userMessage.tail != 0){ //if the tail is 0 then it has never been incre
          //so the buffer has never ben used
      for (int i = 0; i <= userMessage.tail; i++){
        uBit.display.print(userMessage.buffer[i]);
        uBit.sleep(500);
        uBit.display.clear();
        uBit.sleep(1000);
      }
    }
      userMessage.tail = 0; //Reset the tail

    }

    pressed = false;
    uBit.display.clear();
  }

}
}

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
    //Listeners below
    //uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, on_button_a);
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
