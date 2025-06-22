FROM silstechar/arduino-cli-esp32:latest

# For esptool.py, due: "ModuleNotFoundError: No module named 'serial'"
RUN pip install pyserial

# All libs install
RUN arduino-cli lib update-index
RUN arduino-cli lib install WiFi HTTPClient AsyncTCP ArduinoJson 

# Config
#	wi-fi ssid and password !!!
ENV A0S_SSID=***
ENV A0S_PASSWORD=***
#	software building version
ENV A0S_SW_VER=v1.0.0
#	path to mapping usb serial device
ENV A0S_USBNAME=/dev/ttyUSB0
 
# Default location from 'solarbotics/arduino-cli-esp32' image
WORKDIR /home/circleci/project

# Copy sources
COPY Arduino.ino project.ino
COPY partitions.csv partitions.csv
COPY --link --chmod=755 build-flashing-monitor.sh /usr/local/bin/build-flashing-monitor

ENTRYPOINT ["build-flashing-monitor"]
