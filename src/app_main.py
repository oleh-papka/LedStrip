"""
	Main app for sending data to available serial ports

	Raises:
		EnvironmentError: ['Unsupported platform']

	Returns:
		None	
"""
# from get_ports import serial_ports
from serial import *
import time


arduino = Serial()
arduino.baudrate = 9600
arduino.port = "COM5"
arduino.open()

# ports = serial_ports()

# ser = Serial("COM5", 9600, timeout=0, parity=PARITY_EVEN, rtscts=1)

# print("Used port: " + ser.name)
print("10 0 0 255 0 0 0 0 ".encode("utf-8"))
time.sleep(5)

arduino.write("10 0 0 255 0 0 0 0 ".encode())


# ser.write(b"1 0 0 255 0 0 0 0 \n")

arduino.close()