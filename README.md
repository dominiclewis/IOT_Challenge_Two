# Building Instructions
### Files to Download
1. _/source/_
    1. _main.cpp_ - Main application code
    1. _player.h_ - Header file containing my player class definition
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
