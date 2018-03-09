#include "Shared.h"

/*
*Purpose: Swaps our morse to chars
*Returns: void
*Accepts: N/A
*/
void getChars(){
  int charStartIndex =-1;
  int charEndIndex = -1;
  bool newRun = true;
  string tmp;

  //string tmp;
for (int i = 0; i<= userMessage.tail; i++){
  if(newRun){
    charStartIndex = 0;
    newRun = false;
  }
  if((i + 1 > userMessage.tail) || (userMessage.buffer[i+1] == BREAK)){
    charEndIndex = i;
    tmp.clear();
    for(int x = charStartIndex; x<=charEndIndex; x++){
      uBit.display.print(userMessage.buffer[x]);
      uBit.sleep(500);
      uBit.display.clear();
      uBit.sleep(500);
      tmp.push_back(userMessage.buffer[x]);
    }
    //Look up tmp
    uBit.display.print(tmp.c_str());
    uBit.sleep(1000);
    uBit.display.print("tst");
    uBit.sleep(500);
    uBit.display.clear();
    uBit.sleep(100);
    uBit.display.print(morseMap[tmp.c_str()]);
    uBit.sleep(500);
    userMessage.charBuffer[userMessage.charBuffTail] = morseMap[tmp];

    userMessage.charBuffTail += 1;

    if( (i+1) < userMessage.tail){
      i +=2;
      charStartIndex = i;
    }
  }
}
for (int z =0; z<= userMessage.charBuffTail; z++){
  uBit.display.print(userMessage.charBuffer[z]);
  uBit.sleep(5000);
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
    for(int i  = 0; i <=userMessage.tail; i++){
      uBit.serial.sendChar(userMessage.buffer[i],SYNC_SPINWAIT);//Send and block CPU
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
  char val = uBit.serial.read(ASYNC);
  uBit.sleep(200);
  uBit.display.print(val);
  uBit.sleep(1000);
  uBit.display.clear();
  uBit.sleep(200);

//}

}
