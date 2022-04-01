#!/usr/bin/env python3

# This is a very basic latency test program. Whenever it gets a value
# between 0-5 it immediately sends it back.  It then prints out all
# characters it receives. This is intended to be used with a
# corresponding arduino program that measures how long it takes
# between sending and receiving the character. It then prints out
# the corresponding latency back over the serial before trying again.
#
# Carrick Detweiler 2022
#

from serial.tools.list_ports import comports
import serial

ser = serial.Serial()
#Serial port being used
ser.port="/dev/tty_serial_bridge"
ser.baudrate=115200
#timeout in seconds, 0 to return immediately, don't set to do blocking
ser.timeout = 0

try:
    ser.open()

    print("Successfully opened port " + ser.name)
    print("  Baud:",ser.baudrate)
except:
    print("Cannot open port")
    exit()

while True:
    data = ser.read(1)
    if len(data) != 0:
        if int.from_bytes(data,"big") <= 5:
            if int.from_bytes(data,"big") >= 0:
                ser.write(data)
                #print("Echoed Back", data)
        else:
            print(str(data,'UTF-8'),end="")
        
