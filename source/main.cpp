/*
* File: main.cpp
* Author: Dominic Lewis
* Date: 20180304
* Desc: IOT Assignment 02
* Note: Encode as a summative int eg. A  = DOT + DASH etc
 */
#include "Shared.h"


MicroBit uBit;
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
message userMessage; //our struct
int64_t buttonLastPressedTime = -1; //default value
bool mode = false;
std::map<string,char> morseMap;//Map for DASH



/*
*Purpose: Event handler for b button
*Accepts: Event object
*Returns: N/A
*/
void on_button_b(MicroBitEvent e)
{
  if(mode){
    uBit.reset();
  }
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
      }else if(delta > 2500){
      userMessage.buffer[userMessage.tail] = BREAK; //break
      userMessage.tail += 1;
      uBit.display.print("_");
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
    morseMap[".-"] = (char)alphabet[0]; // A
    morseMap["-..."] = (char)alphabet[1]; //B
    morseMap["-.-."] = (char)alphabet[2]; //C
    morseMap["-.."] = (char)alphabet[3];//D
    morseMap["."] = (char)alphabet[4]; //E
    morseMap["..-."] = (char)alphabet[5];//F
    morseMap["--."] = (char)alphabet[6]; //G
    morseMap["...."]= (char)alphabet[7];//H
    morseMap[".."] = (char)alphabet[8];//I
    morseMap[".---"] = (char)alphabet[9];//J
    morseMap["-.-"] = (char)alphabet[10];//K
    morseMap[".-.."] = (char)alphabet[11]; //L
    morseMap["--"] = (char)alphabet[12]; //M
    morseMap["-."]= (char)alphabet[13]; //N
    morseMap["---"] = (char)alphabet[14];//O
    morseMap[".--."]= (char)alphabet[15]; //P
    morseMap["--.-"]= (char)alphabet[16]; //Q
    morseMap[".-."] = (char)alphabet[17];//R
    morseMap["..."] = (char)alphabet[18];//S
    morseMap["-"] = (char)alphabet[19];//T
    morseMap["..-"] = (char)alphabet[20]; //U
    morseMap["...-"] = (char)alphabet[21]; //V
    morseMap[".--"] = (char)alphabet[22]; //W
    morseMap["-..-"] = (char)alphabet[23]; //X
    morseMap["-.--"] = (char)alphabet[24]; //Y
    morseMap["--.."] = (char)alphabet[25]; //Z
    morseMap[".----"] = (char)alphabet[26]; //1
    morseMap["..---"] = (char)alphabet[27]; //2
    morseMap["...--"] = (char)alphabet[28]; //3
    morseMap["....-"] = (char)alphabet[29]; //4
    morseMap["....."] = (char)alphabet[30]; //5
    morseMap["-...."] = (char)alphabet[31]; //6
    morseMap["--..."] = (char)alphabet[32];//7
    morseMap["---.."] = (char)alphabet[33];//8
    morseMap["----."] = (char)alphabet[34];//9
    morseMap["-----"] = (char)alphabet[35];//0
    //morseMap["tst"] = 's';
    //uBit.display.print(morseMap["tst"]);
    //uBit.sleep(5000);
    uBit.serial.redirect(MICROBIT_PIN_P0,MICROBIT_PIN_P1);// tx,rx (redirect here so global)

    //Default buffer size is fine as circular I think
    //Listener below
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, on_button_b);

    while(1){
      uBit.sleep(100);
      if (mode == false){ //Reciever
        listen();
      } else{
        getMessage();
        if ( (system_timer_current_time() - buttonLastPressedTime > 10000)&&
            buttonLastPressedTime != -1){
            //Time to send it has been a while
              uBit.display.scroll("Sending");
                uBit.sleep(300);
                getChars();
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
