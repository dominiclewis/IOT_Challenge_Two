#!/bin/bash
echo "Build Begins"
yt build
echo "Build Finished"
sleep 3.5
echo "Attempting to copy build to Microbit 0"
cp build/bbc-microbit-classic-gcc/source/iot-example-combined.hex /media/student/MICROBIT/
echo "Copy 0 finished"
sleep 3.5
echo "Attemping to copy build to Microbit 1"
cp build/bbc-microbit-classic-gcc/source/iot-example-combined.hex /media/student/MICROBIT1/
echo "Copy 1 finihsed"
sleep 5
