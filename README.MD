# Arduino LedStrip v0.2.1

**Simple LED strip controls (remote and from PC)**

Inspiration for the project by [AlexGyver](https://github.com/AlexGyver/ColorMusic), everything else was found in Google)

This basically is simple "menu" with effects for addressable LED strip ws2812b. Controlled via remote or PC (GUI app). 


**Supported:**
- PC control (via my app or via serial port Arduino IDE sending raw comands)
- Remote control

**Based on:**
- Addres LED strip ws2812b
- Arduino Nano
- vs1838b IR receiver
- Car_mp3 remote
- For PC control you need to connect it to PC (so also needed USB cable)

## About

**There is:**
- 2 - static effects + settings for them
- 4 - dynamic effects + settings for them
- 3 - presets + settings for them

**Effects:**
- Static:
	- Set color (HSV mode - only for remote)
	- Set 2 color linear gradient (HSV mode - only for remote)
- Dynamic:
	- Rainbow (Set rainbow speed and size)
	- Police siren (Set speed and type: blue or red&blue)
	- Strobe (HSV mode - only for remote)
- Presets (Currently supported only for remote):	
	- Preset color (Quickly set 1 color from settings, 3 available)
	- Preset gradient (Quickly set static rainbow from settings, 2 available)
	- Preset rainbow (Quickly set rainbow animation from settings, 2 available)

**Used:**
- [IRLremote](https://github.com/NicoHood/IRLremote) Arduino library
- [FastLED](https://github.com/FastLED/FastLED) Arduino library
- [Eel](https://github.com/ChrisKnott/Eel) Python library
- [pySerial](https://github.com/pyserial/pyserial) Python library


Now you can control LED strip as you want. 


## Upgrade Steps & Installation
- Just download new version from [GitHub Releases tab](https://github.com/OlegPapka2/LedStrip/releases/tag/v0.2.1) (app.rar) or [here (direct download link)](https://github.com/OlegPapka2/LedStrip/releases/download/v0.2.1/app.rar) 
- Extract files from archive to folder you want
- Find in that folder "gui_app.exe" - run program or right-click the program name, and then click Send To > Desktop (Create shortcut), forget about that folder, and then run it via shortcut all the time
- Done ✔
	- Now you can go and do magic with LED strip  

## In future:

Changes on the horizon. New releases, new updates and of course new features will be added as soon as I can make them (or if I want to). Project becomes bigger, and now it's looking a little bit more practical in use, and much more user friendly. 

Know other methods, or want me to add something new please write me [here (Mail)](mailto:olegpapka2@gmail.com) or [here (Telegram)](https://t.me/oleg_folder).

- [ ] New effects
- [ ] New functions for app


## :octocat: Contributing

Pull requests are welcome. For huge changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
