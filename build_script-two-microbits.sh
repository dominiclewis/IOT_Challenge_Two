#!/bin/bash
echo "Build Begins"
yt build
echo "Build Finished"
echo "Attempting to copy build to Microbit 0"
cp build/bbc-microbit-classic-gcc/source/iot-example-combined.hex /media/student/MICROBIT/
echo "Copy 0 finished"
echo "Attemping to copy build to Microbit 1"
cp build/bbc-microbit-classic-gcc/source/iot-example-combined.hex /media/student/MICROBIT1/
echo "Copy 1 finished"
