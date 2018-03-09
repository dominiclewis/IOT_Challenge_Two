# Building Instructions
### Files to Download
1. _/source/_
    1. _main.cpp_ - Main application code
    2. _send.cpp_ - Contains application code handling sending, receiving and     encryption
    3. Shared.h - Contains useful imports and declarations to reduce redundancy

2. _module.json_ - Contains instructions for yotta on how to build
3. **Optional** _.yotta.json_ - Specifies the target and that is was explicitly set

### Commands Required Initially
**Note**. Step 1 only needs top be done if _.yotta.json_ has not downloaded.
1. yt target bbc-microbit-classic-gcc
2. yt build

# Running Instructions
The executable can be found inside _/build/bbc-microbit-classic-gcc/source_,
with the executable being named _project_name-combined.hex_

Copy this file to _/media/student/MICROBIT_

# GPIO Setup
The sending pin we use is P0 while P1 is the recieving one.

# Instructions
The two MicroBits be connected with a crocodile clip. We are using the GPIO PIN0 to send and GPIO PIN1 to receive. As such the Microbit which has the clip attached to
GPIO Pin 0 must be put into 'Send mode' and the one with the GPI01 attached clip in 'receive mode'.


## Modes
The two MicroBits can be toggled into the corresponding listen and transmitting mode using
the B Button.
### Listen
In listen mode the MicroBit will wait for an input from the transmitting MicroBit.

### Transmitting
In transmit mode the MicroBit will detected the duration of BUTTON_A presses.

Dot < 500ms

Dash >= 500ms && <=1500ms

Same Word Limit <= 3000ms

Insert Word Break > 3000ms && <= 6000ms

Transmit > 6000ms

#Protocol
I'm using the serial Microbit library to transfer characters, this allows me to abstract away some details. I initially accept in the Morse code characters (. / -) then I convert it before it has been sent to Alpha Numerics. The default baud rate for the Microbit across serial is 115200 which is extremely useful.

#Encryption
I've implemented a Caesar Cipher on the input characters shifting them right 7 bits to encrypt the chars then carrying out the inverse operation to decrypt. This is easily managed in C++ by storing the alphabet in an array and monitoring the characters during the encryption to almost ensure that the array is circular.

### Note
The microbits enter into listen mode by default so the sender will need to be toggled out 


Dominic Lewis

Casey Cheung
