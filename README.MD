# Arduino LedStrip menu

Inspiration for the project by [AlexGyver](https://github.com/AlexGyver/ColorMusic), everyhting else was found in Google)

This basically is pretty simple "menu" with some effects for remote control of addressable LED strip.

Also added control from the PC via serial port

**Based on:**
- Addres LED strip ws2812b
- Arduino Nano
- vs1838b IR receiver
- Car_mp3 remote

## About

**There is:**
- 2 - static effects + settings for them
- 4 - dynamic effects + settings for them
- 3 - presets 

**Effects:**
- Static:
	- Set color (HSV mode)
	- Set 2 color linear gradient (HSV mode)
- Dynamic:
	- Rainbow
	- Police siren
	- Strobe (HSV mode)
- Presets:
	- Preset color
	- Preset gradient
	- Preset rainbow

**Used:**
- [IRLremote](https://github.com/NicoHood/IRLremote) library
- [FastLED](https://github.com/FastLED/FastLED) library

> Somebody: *So, how it works?*
> Me: *Magic*

## In future:
- [ ] Add new presets and settings
- [ ] Add display
- [x] Add PC data input
- [ ] Add audio spectrum analyzer
- [ ] Add auto brightness
- [ ] Add new features to desktop app

## :octocat: Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
