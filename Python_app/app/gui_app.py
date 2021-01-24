import eel
import serial
import time

arduino = serial.Serial(port='COM5', baudrate=9600, timeout=.1)

eel.init('D:\Arduino\LedStrip\Python_app\web') # Needed full path to folder

data = [0, 0, 0, 0, 0, 0, 0, 0]

def gether_data(data):
	data_string = ''
	for i in range(8):
		data_string += str(data[i]) + ' '
	print("{" + data_string + "}")
	arduino.write(bytes(data_string, 'utf-8'))		# Sample put strip blue 
	time.sleep(0.15)


@eel.expose
def get_set_color(color):
	global data
	data[0] = 10
	data[2] = int(color[1:3], 16)
	data[3] = int(color[3:5], 16)
	data[4] = int(color[5:7], 16)
	gether_data(data)
	data = [0, 0, 0, 0, 0, 0, 0, 0]


@eel.expose
def get_rainbow(speed, size):
	global data
	data[0] = 3
	data[1] = speed
	data[2] = size
	gether_data(data)
	data = [0, 0, 0, 0, 0, 0, 0, 0]



@eel.expose
def get_gradient(color1, color2):
	global data
	data[0] = 2
	data[2] = int(color1[1:3], 16)
	data[3] = int(color1[3:5], 16)
	data[4] = int(color1[5:7], 16)
	data[5] = int(color2[1:3], 16)
	data[6] = int(color2[3:5], 16)
	data[7] = int(color2[5:7], 16)
	gether_data(data)
	data = [0, 0, 0, 0, 0, 0, 0, 0]



@eel.expose
def get_strobe(color, speed):
	global data
	data[0] = 11
	data[1] = speed
	data[2] = int(color[1:3], 16)
	data[3] = int(color[3:5], 16)
	data[4] = int(color[5:7], 16)
	gether_data(data)
	data = [0, 0, 0, 0, 0, 0, 0, 0]



@eel.expose
def get_police_siren(speed, siren_type):
	global data
	data[0] = 4
	data[1] = speed
	data[2] = siren_type
	gether_data(data)
	data = [0, 0, 0, 0, 0, 0, 0, 0]


@eel.expose
def get_matrix(color, speed):
	global data
	data[0] = 12
	data[1] = speed
	data[2] = int(color[1:3], 16)
	data[3] = int(color[3:5], 16)
	data[4] = int(color[5:7], 16)
	gether_data(data)
	data = [0, 0, 0, 0, 0, 0, 0, 0]


@eel.expose
def get_brightness(val):
	global data
	data[0] = 0
	data[1] = val
	gether_data(data)
	data = [0, 0, 0, 0, 0, 0, 0, 0]

try:
	eel.start('html/index.html', host='localhost', size=(500, 620))
except:
	arduino.close()
	print("End of program")