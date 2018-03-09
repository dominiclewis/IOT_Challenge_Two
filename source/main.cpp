/*
* File: main.cpp
* Author: Dominic Lewis
* Date: 20180304
* Desc: IOT Assignment 02
* Note: Encode as a summative int eg. A  = DOT + DASH etc
 */
#include "Shared.h"
MicroBit uBit;
//MicroBitSerial serial = MicroBitSerial(MICROBIT_PIN_P0, MICROBIT_PIN_P1);


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
  mode = !mode;
}

/*
*Purpose: Logic for the microbit while it's listening
*Accepts: N/A
*Returns: (void)
*Note: //Detect next 8 changes from first 1
*/
void listen(){

  uBit.display.print("X");
  uBit.sleep(500);
  char read = uBit.serial.read(ASYNC);
  uBit.sleep(200);
  uBit.display.print(read);
uBit.sleep(500);

}
void tst(){
  uBit.display.printAsync(uBit.serial.txBufferedSize());
  uBit.sleep(5000);
}

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
    //uBit.display.print(serial.getTxBufferSize());
    //uBit.sleep(500);
    uBit.serial.redirect(MICROBIT_PIN_P0,MICROBIT_PIN_P1);// tx,rx (redirect here so global)
    //=create_fiber(tst);

    //Default buffer size is fine as circular I think
    //Listeners below
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, on_button_a);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, on_button_b);

    while(1){

      uBit.sleep(100);
      if (mode == false){
     uBit.display.scroll("Listening",50);
        uBit.sleep(500);
        listen();
      } else{
      uBit.display.scroll("Writing",50);
        uBit.sleep(500);
        send();
      }
      uBit.sleep(100);

    }
    release_fiber();
    }
