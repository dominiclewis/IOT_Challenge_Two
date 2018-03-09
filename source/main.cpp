/*
* File: main.cpp
* Author: Dominic Lewis
* Date: 20180304
* Desc: IOT Assignment 02
* Note: Encode as a summative int eg. A  = DOT + DASH etc
 */
#include "Shared.h"

#define DASH '-'
#define DOT '.'
#define BREAK 'B'

MicroBit uBit;
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
message userMessage; //our struct

int64_t buttonLastPressedTime = -1; //default value
bool mode = false;
/*
*Purpose: Event handler for a button
*Accepts: Event object
*Returns: N/A
*/
void on_button_a(MicroBitEvent e) //Move left
{

}

/*
*Purpose: Event handler for b button
*Accepts: Event object
*Returns: N/A
*/
void on_button_b(MicroBitEvent e)
{

  mode = !mode; //change between send and listen
  if(mode){
    uBit.display.scroll("SENDING",100);
  } else{
    uBit.display.scroll("RECIEVING",100);
  }
  uBit.sleep(100);
}



/*
*Purpose: Logic for the microbit while it's transmitting a message
*Accepts: N/A
*Returns:(void)
*Note: Send on pin 0
*/
void getMessage(){
  bool pressed = false;
  while(buttonA.isPressed()){
    uint64_t startTime = system_timer_current_time(); //Get start time
    buttonLastPressedTime = startTime;//Set the last pressed
    while(buttonA.isPressed()){
      pressed = true;
    }
    //Get the delta (the difference)
    uint64_t delta = system_timer_current_time() - startTime;//button let go
    //uBit.display.print((int)delta);
    if (pressed){
      if( (delta >= 300) && (delta <= 1000)){
        //long press
        userMessage.buffer[userMessage.tail] = DASH; //dash
        userMessage.tail += 1;
        uBit.display.print("-"); //1
        uBit.sleep(500);
      } else if(delta < 300){
        //short press
        userMessage.buffer[userMessage.tail] = DOT;//dot
        userMessage.tail += 1;
        uBit.display.print(".");//0
        uBit.sleep(500);
      }else if(delta > 4000){
      userMessage.buffer[userMessage.tail] = BREAK; //break
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
    uBit.display.scroll("MORSE CODE",100);
    uBit.sleep(500);

    uBit.serial.redirect(MICROBIT_PIN_P0,MICROBIT_PIN_P1);// tx,rx (redirect here so global)

    //Default buffer size is fine as circular I think
    //Listeners below
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, on_button_a);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, on_button_b);

    while(1){
      uBit.sleep(100);
      if (mode == false){ //Reciever
        listen();
      } else{
        getMessage();
        if ( (system_timer_current_time() - buttonLastPressedTime > 6000)&&
            buttonLastPressedTime != -1){
            //Time to send it has been a while
              uBit.display.scroll("Sending");
                uBit.sleep(300);
                send();
          /*  for (int i = 0; i <= userMessage.tail; i++){
              uBit.display.print(userMessage.buffer[i]);
              uBit.sleep(500);
              uBit.display.clear();
              uBit.sleep(500);
            }
            */ //Debug

            buttonLastPressedTime = -1; //default value
            userMessage.tail = 0; //Reset the tail

            }
      uBit.sleep(100);
      }
    }
    release_fiber();
    }
