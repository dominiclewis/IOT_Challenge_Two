#include "Shared.h"

/*
*Purpose: Swaps our morse to chars
*Returns: void
*Accepts: N/A
*/
/*
void getChars(){
  int charStartIndex =0;
  int charEndIndex = -1;
  //bool newRun = true;
  userMessage.tail = userMessage.tail -2;

  string tmp;
  for (int i =0;i <=userMessage.tail; i++){
    uBit.display.print(userMessage.buffer[i]);
    uBit.sleep(1000);
    uBit.display.clear();
    uBit.sleep(2000);
  }
  uBit.display.print(userMessage.tail);
  uBit.sleep(1000);

  //string tmp;
for (int i = 0; i<= userMessage.tail; i++){
  if((i + 1 >= userMessage.tail) || (userMessage.buffer[i+1] == BREAK)){
    charEndIndex = i;
    tmp.clear();

    for(int x = charStartIndex; x<=charEndIndex; x++){
    //  uBit.display.clear();
  //    uBit.sleep(500);
      tmp.push_back(userMessage.buffer[x]);
    }
    //lOOK UP TMP
    uBit.display.print("Here",20);
    uBit.sleep(400);
    uBit.display.print(morseMap[tmp.c_str()]);
    uBit.sleep(5000);
    userMessage.charBuffer[userMessage.charBuffTail] = morseMap[tmp.c_str()];
    userMessage.charBuffTail += 1;

    if( (i+1) < userMessage.tail){
      i +=1;
      charStartIndex = i+=1;
    }
  }
}
for (int z =0; z<= userMessage.charBuffTail; z++){
  uBit.display.print(userMessage.charBuffer[z]);
  uBit.sleep(1000);
}
}
*/
void getChars(){
  string tmp;
  uBit.display.print(userMessage.tail);
  uBit.sleep(1000);

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
    uBit.display.print(userMessage.charBuffTail);
    uBit.sleep(1000);
    uBit.display.clear();
    userMessage.charBuffTail++; //incre by one
  }
  //See if there's anothe index in aray

  }
}
/*
Encrypts with a Caesaer Cypher. Shifts chars 7 places right
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
decrypt with a Caesaer Cypher. Shifts chars 7 places left
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
