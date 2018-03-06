/*
* File: main.cpp
* Author: Dominic Lewis
* Date: 20180304
* Desc: IOT Assignment 02
* Note: Encode as a summative int eg. A  = DOT + DASH etc
 */
#include "MicroBit.h"

//Analog value
#define DASH 002
#define DOT 003
#define BREAK 004

//Prototypes
void on_button_a(MicroBitEvent);
void on_button_b(MicroBitEvent);
void listen();
void send();
void sendingMessage();
int getSendAnalogValue(int);

struct message{
int buffer [100]; //Big
int tail = 0; //tracks the index
};

MicroBit uBit; //Our instantiation
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL); //Send
MicroBitPin P1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL); // Listen
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A); //Can use to get button A time
int64_t buttonLastPressedTime = -1; //default value
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
  uBit.display.print(P1.getAnalogValue());
  uBit.sleep(500);
  uBit.display.print("Out",200);
      uBit.sleep(100);
  if (P1.getAnalogValue() == BREAK){ //Listen on p1
    uBit.display.print("2");
  } else if (P1.getAnalogValue() == DASH ){
    uBit.display.print("1");
  } else if (P1.getAnalogValue() == DOT){
    uBit.sleep(100);
    uBit.display.print("0");
  }
  uBit.sleep(500);
}
/*
*Purpose: Logic for getting swapping an integer for an anlog
*Accepts: integer from the buffer
*Returns:integer corresponding to the analog value
*Note:
*/
int getSendAnalogValue(int bufferValue){

  switch (bufferValue){
    case (2)://BREAK
      return BREAK;
    case (1): //DASH
      return DASH;
    case (0): //DOT
      return DOT;
  }
return -1;
}
/*
*Purpose: Logic for sending a message
*Accepts: N/A
*Returns:(void)
*Note: Send on pin 0
*/
void sendingMessage(){
  for(int i= 0; i <= userMessage.tail; i++){ //loop throught everything
    int value = getSendAnalogValue(userMessage.buffer[i]); //get the val
    //uBit.display.scroll("Sending",50);

    uBit.sleep(200);
    P0.setAnalogValue(value);//Set the pin to be the analog value
    uBit.sleep(500);
    uBit.display.scroll(P0.getAnalogValue());
    uBit.sleep(1000);
  }
  uBit.sleep(1000);

}
/*
*Purpose: Logic for the microbit while it's transmitting a message
*Accepts: N/A
*Returns:(void)
*Note: Send on pin 0
*/
void getMessage(){
  //Toggle LED
/*  P0.setDigitalValue(1);
  uBit.sleep(500);
  P0.setDigitalValue(0);
  */
  bool pressed = false;

  while(buttonA.isPressed()){
    uint64_t startTime = system_timer_current_time(); //Get start time
    buttonLastPressedTime = startTime;//Set the last pressed
    while(buttonA.isPressed()){
      pressed = true;
    }
    //Get the delta (the difference)
    uint64_t delta = system_timer_current_time() - startTime;
    //uBit.display.print((int)delta);
    if (pressed){
      if( (delta >= 300) && (delta <= 1000)){
        //long press
        userMessage.buffer[userMessage.tail] = 1; //dash
        userMessage.tail += 1;
        uBit.display.print("-"); //1
        uBit.sleep(500);
      } else if(delta < 300){
        //short press
        userMessage.buffer[userMessage.tail] = 0;//dot
        userMessage.tail += 1;
        uBit.display.print(".");//0
        uBit.sleep(500);
      }else if(delta > 4000){
      userMessage.buffer[userMessage.tail] = 2; //break
      userMessage.tail += 1;
      uBit.display.scroll("Break");
      uBit.sleep(1000);
    }
    }
    pressed = false;
    uBit.display.clear();
  }

}


int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
    P0.setAnalogValue(1);
    uBit.sleep(10000);
    //Listeners below
    //uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, on_button_a);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, on_button_b);

    while(1){
        if (readMode){
          //Read
          listen();
        } else{
          //Sending
          getMessage();
          if ( (system_timer_current_time() - buttonLastPressedTime > 6000)&&
        buttonLastPressedTime != -1){
            //Time to send it has been a while
          //  uBit.display.scroll("Sending");
        //    uBit.sleep(1000);
            sendingMessage();
            buttonLastPressedTime = -1; //default value
            userMessage.tail = 0; //Reset the tail

          }
        }
    uBit.sleep(500);
    }
    release_fiber();
    }
