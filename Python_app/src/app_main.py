"""
	Main app for sending data to available serial ports

	Raises:
		EnvironmentError: ['Unsupported platform']

	Returns:
		None	
"""
# from get_ports import serial_ports
import serial
import time

arduino = serial.Serial(port='COM5', baudrate=9600, timeout=.1)

arduino.write(bytes("10 0 0 0 255 0 0 0 ", 'utf-8'))		# Sample put strip blue 
time.sleep(0.15)

arduino.close()