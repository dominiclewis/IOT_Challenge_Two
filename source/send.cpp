/*
* File: main.cpp
* Author: Dominic Lewis
* Date: 20180304
* Desc: IOT Assignment 02
* Note: Encode as a summative int eg. A  = DOT + DASH etc
 */
#include "Shared.h"

/*
* Purpose: Gets the chars from the pending buffer, valides and sends
* Accepts: ced
* Returns:  c
*/
void getChars(){
  string tmp;

  userMessage.tail = userMessage.tail - 1;
  for (int bufferChars = 0; bufferChars <=userMessage.tail; bufferChars++){
    //read till delimited
    if(userMessage.buffer[bufferChars] != BREAK){
    tmp.push_back(userMessage.buffer[bufferChars]);
    continue;
  } else{
    //Delimiter found so try to look up temp
    userMessage.charBuffer[userMessage.charBuffTail] = morseMap[tmp.c_str()];
    tmp.clear();
    //Store the value in the string
    //uBit.display.print(userMessage.charBuffTail);
    uBit.sleep(400);
    uBit.display.clear();
    userMessage.charBuffTail++; //incre by one
  }
  //See if there's anothe index in aray

  }
}
/*
* Purpose: Encrypts with a Caesaer Cypher. Shifts chars 7 places right
* Accepts: char that needs to be encryped
* Returns:  encrypted char ready for transmission
*/
char encrypt(char charToChange){
int shiftRight = 7;
//find chars index in our alphabet array
for(int i = 0; i < 37; i++){
  if(charToChange == alphabet[i]){
    while(shiftRight != 0){
      if(i + 1 > MAX){
        i = MIN;
      } else{
        i++;
      }
      shiftRight -=1;
    }
    return alphabet[i];
  }
}
}

/*
* Purpose: Decrypt with a Caesaer Cypher. Shifts chars 7 places left
* Accepts: char that needs to be Decrypteed
* Returns:  char ready for display
*/
char decrypt(char charToChange){
int shiftLeft = 7;
//find chars index in our alphabet array
for(int i = 0; i < 37; i++){
  if(charToChange == alphabet[i]){
    while(shiftLeft != 0){
      if(i -1 < MIN){
        i = MAX;
      } else{
        i--;
      }
      shiftLeft -=1;
    }
    return alphabet[i];
  }
}
}


/*
*Purpose: Sends one char at a time
*Returns: void
*Accepts: N/A
*/
void send(){
  uBit.sleep(100);
  if(uBit.serial.isWriteable() ==1 ){
    for(int i  = 0; i <= userMessage.charBuffTail; i++){
      uBit.serial.sendChar(encrypt(userMessage.charBuffer[i]),SYNC_SPINWAIT);//Send and block CPU
      uBit.sleep(1000);
    }
} else{
  uBit.display.print("Not printable");
  uBit.sleep(100);
}
userMessage.charBuffTail = 0;
}

/*
*Purpose: reads out one char at a time
*Returns: void
*Accepts: N/A
*/
void listen(){
//if(uBit.serial.isReadable() == 0){//Data waiting? API is wrong
  char val = decrypt(uBit.serial.read(ASYNC));
  uBit.sleep(200);
  uBit.display.print(val);
  uBit.sleep(1000);
  uBit.display.clear();
  uBit.sleep(200);

//}

}
