# Arduino LedStrip menu

Inspiration for the project by [AlexGyver](https://github.com/AlexGyver/ColorMusic), everyhting else was found in Google)

This basically is pretty simple "menu" with some effects for remote control of addressable LED strip. 

Also added control from the PC via serial port, now it's more like a project with different control types for addres LED strip. So now you can do almost everything via your PC as via remote.

**Supported:**
- PC control (via my app, via serial port Arduino IDE sending raw comands)
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
- 3 - presets + settings for them (currently in opened session)

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

> Somebody: *So, how it works?*
>
> Me: *Magic*

**But seriously**

Everything works... at least works without problems) for now you can control your LED strip as you want. Know other variants for controlling it, please write me [here (Mail)](mailto:olegpapka2@gmail.com) or [here (Telegram)](https://t.me/oleg_folder).

## In future:

Changes on the horizon. New releases, new updates and of course new features will be added as soon as I can make them. Project becomes bigger, and now it's looking a little bit more practical in use, and much more user friendly.

- [x] ~~Added settings~~
- [x] ~~Added auto port detecting and in app settings port changing~~
- [x] ~~Added PC data input~~
- [x] ~~Added presets, and their customization~~
- [ ] Add writing to memory
- [ ] Add auto brightness
- [ ] Add display (OLED)
- [ ] Add audio spectrum analyzer (maybe)


## :octocat: Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
