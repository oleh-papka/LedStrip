import eel

eel.init('web') # Needed full path to folder

try:
	eel.start('html/index.html', host='localhost', size=(600, 600))
except:
	print("End of program")

