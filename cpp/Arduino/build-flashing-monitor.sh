#!/bin/sh
set -e
echo "Start building..."
arduino-cli compile --build-property build.defines=\"" -DA0S_BUILT_VERSION="\\\"$A0S_SW_VER\\\"" -DA0S_SSID="\\\"$A0S_SSID\\\"" -DA0S_PASSWORD="\\\"$A0S_PASSWORD\\\" \" -b esp32:esp32:esp32
echo "end building"
echo "Start flashing..."
arduino-cli upload -p $A0S_USBNAME -b esp32:esp32:esp32 .
echo "end flashing"
echo "Start monitoring..."
arduino-cli monitor -p $A0S_USBNAME -b esp32:esp32:esp32 -c baudrate=115200
echo "end monitoring"
