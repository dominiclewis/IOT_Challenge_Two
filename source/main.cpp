/*
* File: main.cpp
* Author: Dominic Lewis
* Date: 20180304
* Desc: IOT Assignment 02
* Note: Encode as a summative int eg. A  = DOT + DASH etc
 */
#include "MicroBit.h"

#define DASH 1
#define DOT 0
#define BREAK 2
#define NUMBITS 4

//Prototypes
void on_button_a(MicroBitEvent);
void on_button_b(MicroBitEvent);
void listen();
void send();
void sendingMessage();
void broadCastBitString(int*);
void broadcastNewMarker();



struct message{
int buffer [100]; //Big
int tail = 0; //tracks the index
};

uint64_t messageTmp[200];




MicroBit uBit; //Our instantiation
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL); //Send
MicroBitPin P1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL); // Listen
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A); //Can use to get button A time
int64_t buttonLastPressedTime = -1; //default value
message userMessage;
//
int dashBitString [NUMBITS] = {1,0,1,1}; // -
int dotBitString [NUMBITS] = {1,1,0,1}; //  .
int breakBitString [NUMBITS] = {1,0,0,1}; //Break
int markerBitString [NUMBITS] = {1,1,0,0}; //Beging of a string or end`

bool readMode = true; //If false then it's in send mode
bool firstValPass = false;
int valCount = 1;
bool newMessage = true;
bool lock = false;


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
*Note: //Detect next 8 changes from first 1
*/
void listen(){
  int value = P1.getDigitalValue();
  if ((value == 1) && (firstValPass == false)){
    firstValPass = true;
    uBit.display.print(value);
  } else if(firstValPass == true){
    valCount++;
    if(valCount == (NUMBITS + 1)){
      firstValPass = false;
      valCount = 1;
      //uBit.display.print("E",50);
    }else{
    uBit.display.print(value,30);
    }
  }

  uBit.sleep(50);
  uBit.display.clear();
  uBit.sleep(50);

}

void broadcastNewMarker(){
  for (int y = 0; y < NUMBITS; y++){ //One off loop through the markerBStreak

    P0.setDigitalValue(markerBitString[y]);
    //uBit.display.print(markerBitString[y]);
    uBit.sleep(49);
    uBit.display.clear();
    //uBit.sleep(100);

    if (y + 1 == NUMBITS){ //if we're about to finish the new marker bit String
      newMessage = false;
      P0.setDigitalValue(0);
      uBit.sleep(49);

    }
  }
}

void broadcastBitString(int *arr){ //arr is a pointer at which integers can be found
  for(int i = 0; i < NUMBITS; i++){
    //Loop through references array
    P0.setDigitalValue( *(arr + i)); //refrence array through pointer
    uBit.sleep(100);
    if (i + 1 == NUMBITS){
      P0.setDigitalValue(0);
      uBit.sleep(100);
      //Check if there's a break
      if (arr != breakBitString){
        //No break
        newMessage = true;

      }
    }
  }
}

void sendingMessage(){

  //Loop through the userMessageContent
  for (int i = 0; i < userMessage.tail; i++){
    //Loop through userMessageContent[0]'s corresponding BitString
      if (newMessage){//First output the markerBitString
        broadcastNewMarker();
      }
        //Find the corresponding userMessagebuffer[i] bit string
        switch(userMessage.buffer[i]){
          case (DASH):
            broadcastBitString(dashBitString); //ARR's are * to &[0] anyway
            break;
        case (DOT):
            broadcastBitString(dotBitString);
            break;
        case (BREAK):
            broadcastBitString(breakBitString);
            break;

        }
  }
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
    uBit.display.scroll("Listening");
    uBit.sleep(200);
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
