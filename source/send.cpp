#include "Shared.h"

/*
*Purpose: Sends one char at a time
*Returns: void
*Accepts: N/A
*/


void send(){

  uBit.sleep(100);
  if(uBit.serial.isWriteable() ==1 ){
    for(int i  = 0; i <=userMessage.tail; i++){
      uBit.serial.sendChar(userMessage.buffer[i],SYNC_SPINWAIT);//Send and block CPU
      uBit.sleep(1000);
    }
} else{
  uBit.display.print("Not printable");
  uBit.sleep(100);
}
}

/*
*Purpose: reads out one char at a time
*Returns: void
*Accepts: N/A
*/
void listen(){
//if(uBit.serial.isReadable() == 0){//Data waiting? API is wrong
  char val = uBit.serial.read(ASYNC);
  uBit.sleep(200);
  uBit.display.print(val);
  uBit.sleep(1000);
  uBit.display.clear();
  uBit.sleep(200);

//}

}
