#!/bin/bash
echo "Build Begins"
yt build
echo "Build Finished"
echo "Attempting to copy build to Microbit 0"
cp build/bbc-microbit-classic-gcc/source/iot-example-combined.hex /media/student/MICROBIT/
echo "Copy 0 finished"
