serial_data = [0, 0, 0, 0, 0, 0, 0, 0]
stringData = ""



def Make_string(data):
	my_string = ""
	for i in range(8):
		my_string += str(data[i]) + " "
		# stringData += 
	print("[" + my_string + "]")


def Get_effect_num():
	effect_num = int(input("Print effect num: "))
	return effect_num


def Get_delay():
	delay = int(input("Print delay in ms: "))
	return delay


def Get_color1():
	color1 = []
	for i in range(3):
		color1.append(int(input("Print first col " + str(i + 1) + ": ")))
	return color1


def Get_color2():
	color2 = []
	for i in range(3):
		color2.append(int(input("Print second col " + str(i + 1) + ": ")))
	return color2