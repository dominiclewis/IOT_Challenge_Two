#include "Shared.h"

void send(){
  if(uBit.serial.isWriteable() ==1 ){
    uBit.sleep(1000);
    uBit.serial.sendChar('a');
    uBit.sleep(500);

} else{
  uBit.display.print("Not printable");
  uBit.sleep(100);
}
}
