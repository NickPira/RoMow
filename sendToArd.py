
import serial
import time as t
import sys
    
def sendData(data):
    serial.write(data.encode()) #send data encoded into bytes



if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    sendData(sys.argv[0])
    