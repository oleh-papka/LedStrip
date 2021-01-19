/*
	Menu for remote control of addressable LED strip
	Static and dynamic effects

	Based on: 
		• Car_mp3 remote
		• vs1838b IR receiver
		• Addres LED strip ws2812b
		• Arduino Nano

	Oleg Papka 2021
*/


//==================== Libraries ====================

#include <Arduino.h>
#include "IRLremote.h"
#include <FastLED.h>


//==================== Settings ====================

//----- Remote Buttons definition 
#define CH1 0x4E5BA3AD
#define CH2 0xE51CA6AD
#define CH3 0xE207E1AD

#define PREVIOUS 0x517068AD
#define NEXT 0x1B92DDAD
#define PLAY 0xAC2A56AD

#define PLUS 0xD22353AD
#define MINUS 0x5484B6AD
#define EQ 0xDF3F4BAD

#define BUTT_0 0x68E456AD
#define BUTT_100 0xF08A26AD
#define BUTT_200 0x151CD6AD

#define BUTT_1 0x18319BAD
#define BUTT_2 0xF39EEBAD
#define BUTT_3 0x4AABDFAD

#define BUTT_4 0xE25410AD
#define BUTT_5 0x297C76AD
#define BUTT_6 0x14CE54AD

#define BUTT_7 0xAF3F1BAD
#define BUTT_8 0xC089F6AD
#define BUTT_9 0x38379AD

#define BUTT_PRESSED 0x117697CD


//----- Pins definition
#define IR_PIN 2
#define LEDS_PIN 3


//----- LED strip settings
#define NUM_LEDS 30
#define CURRENT_LIMIT 2000
CRGB leds[NUM_LEDS];
byte brightness = 100;
byte current_effect = 1;
unsigned long timer_delay;		// Var for millis delay
boolean play_flag = true;
boolean eq_flag = false;
byte channel = 0;		// Cahnnel for three_param class  


//----- IR settings
CHashIR IRLremote;		// IR protocol of my remote
uint32_t ir_data;		// Current info from IR sensor
uint32_t last_butt;		// Stores last pressed button
boolean ir_flag;		// IR signal received 
boolean butt_held_flag = false;		// Button currently held down
byte adj = 5;		// Standard adjustment value


//==================== Effects ====================

//----- Main effects on remote by buttons
#define SET_COLOR_HSV 1
#define SET_GRADIENT_HSV 2

#define RAINBOW 3
#define POLICE_SIREN 4
#define STROBE 5
#define MATRIX 6

#define PRESET_COLOR 7
#define PRESET_GRADIENT 8
#define PRESET_RAINBOW 9


//----- The delay function
void Debounce_delay(int delay){
	ir_flag = false;		// Stop receiving 
	timer_delay = millis();
	while(millis() < timer_delay + delay){
		// Wait approximately [delay] ms
	}
}


//----- Additional functions
void fill_half(boolean first_half, CRGB color){
	if(first_half){
		for(int i = 0; i < NUM_LEDS/2; i++) {
			leds[i] = color;
		}
	}
	else{
		for(int i = NUM_LEDS/2; i < NUM_LEDS; i++) {
			leds[i] = color;
		}
	}
}

void fill_few(boolean first_half, CRGB color, byte amount = 10){
	if(first_half){
		for(int i = 0; i < amount; i++) {
			leds[i] = color;
		}
	}
	else{
		for(int i = (NUM_LEDS - amount); i < NUM_LEDS; i++) {
			leds[i] = color;
		}
	}
}


//----- Show animation on startup
void Start_up(){
	for(byte i = 0; i < NUM_LEDS*2; i++){
		if(i < NUM_LEDS){
			leds[i] = CRGB::Lime;
		}
		FastLED.show();
		Debounce_delay(30);
		fadeToBlackBy(leds, NUM_LEDS, 40);
	}

	Debounce_delay(500);
}


//----- Show animation on mode change
void Mode_change(){
	FastLED.clear();
	FastLED.show();
	Debounce_delay(300);

	fill_solid(leds, NUM_LEDS, CRGB::Aqua);
	FastLED.show();
	Debounce_delay(200);
	
	FastLED.clear();
	FastLED.show();
	Debounce_delay(300);
}


//----- Set color (RGB)
byte set_rgb_color[3] = {0, 255, 0};		// Array of colors (default green in RGB)

void Set_Colour_RGB(byte ch1, byte ch2, byte ch3){
	fill_solid(leds, NUM_LEDS, CRGB(ch1, ch2, ch3));
}


//----- Show color (HSV)
byte set_hsv_color[3] = {0, 255, 255};		// Array of colors (default red in HSV)

void Set_Colour_HSV(byte ch1, byte ch2, byte ch3){
	fill_solid(leds, NUM_LEDS, CHSV(ch1, ch2, ch3));
}


//----- Gradient
byte gradient_color_1[3] = {0, 255, 255};		// Array of colors (default red in HSV)
byte gradient_color_2[3] = {0, 255, 255};		// Array of colors (default red in HSV)
boolean gradient_mode_flag = true;		// Choose which color should be changed (first or second) (default true - first color)
boolean gradient_reverse_flag = false;		// Changes direction of "Gradient" effect (default false)

void Gradient(boolean mode, boolean reverse){
	if(mode){
		if(!reverse){
			fill_gradient(leds, NUM_LEDS, CHSV(gradient_color_1[0], gradient_color_1[1], gradient_color_1[2]), CHSV(gradient_color_2[0], gradient_color_2[1], gradient_color_2[2]), FORWARD_HUES);
		}
		else{
			fill_gradient(leds, NUM_LEDS, CHSV(gradient_color_2[0], gradient_color_2[1], gradient_color_2[2]), CHSV(gradient_color_1[0], gradient_color_1[1], gradient_color_1[2]), FORWARD_HUES);
		}
	}
	else{
		if(!reverse){
			fill_gradient(leds, NUM_LEDS, CHSV(gradient_color_1[0], gradient_color_1[1], gradient_color_1[2]), CHSV(gradient_color_2[0], gradient_color_2[1], gradient_color_2[2]), BACKWARD_HUES);
		}
		else{
			fill_gradient(leds, NUM_LEDS, CHSV(gradient_color_2[0], gradient_color_2[1], gradient_color_2[2]), CHSV(gradient_color_1[0], gradient_color_1[1], gradient_color_1[2]), BACKWARD_HUES);
		}
	}
}


//----- Rainbow (HSV)
byte rainbow_delta_hue;
byte rainbow_size = 7;		// Size of rainbow on the strip, "255/NUM_LEDS" - full transition over the length of strip (default 7 merely full strip)
byte rainbow_delay = 20;		// Speed of "rainbow" transition, delay between strip updates (default 20 ms)

void Rainbow(byte size, byte delay){
	fill_rainbow(leds, NUM_LEDS, rainbow_delta_hue, size);

	if(millis() - timer_delay > delay){
		timer_delay = millis();
		rainbow_delta_hue++;
	}
}


//----- Police siren
byte siren_counter = 0;
byte siren_delay = 40;		// Speed of "police siren" transition, delay between strip updates (default 10 ms)
boolean siren_reverse = false;		// Changes direction of "police siren" animation (default false)
boolean siren_on_flag = false;		// Leds are currently on (default false - off)

void Police_siren(byte delay){
	if(siren_reverse){
		if(siren_counter < 4){
			if(siren_on_flag){
				Debounce_delay(delay);
				FastLED.clear();
				siren_on_flag = false;
			}
			else{
				Debounce_delay(delay);
				fill_half(false, CRGB::Red);
				siren_on_flag = true;
			}
		}
		else{
			if(siren_on_flag){
				Debounce_delay(delay);
				FastLED.clear();
				siren_on_flag = false;
			}
			else{
				Debounce_delay(delay);
				fill_half(true, CRGB::Blue);
				siren_on_flag = true;
			}
		}
	}
	if(!siren_reverse){
		if(siren_counter < 4){
			if(siren_on_flag){
				Debounce_delay(delay);
				FastLED.clear();
				siren_on_flag = false;
			}
			else{
				Debounce_delay(delay);
				fill_half(true, CRGB::Blue);
				siren_on_flag = true;
			}
		}
		else{
			if(siren_on_flag){
				Debounce_delay(delay);
				FastLED.clear();
				siren_on_flag = false;
			}
			else{
				Debounce_delay(delay);
				fill_half(false, CRGB::Blue);
				siren_on_flag = true;
			}
		}
	}
	siren_counter++;

	if(siren_counter >= 8){
		siren_counter = 0;
	}
}


//----- Strobe
byte strobe_color[3] = {0, 255, 255};		// Array of colors (default red in HSV)
byte strobe_delay = 100;	// Speed of "strobe" transition, delay between strip updates (default 100 ms)
boolean strobe_on_flag = false;		// Leds are currently on (default false - off)

void Strobe(byte ch1, byte ch2, byte ch3, byte delay){
	if (strobe_on_flag){
		Debounce_delay(delay);
		FastLED.clear();
		strobe_on_flag = false;
	}
	else{
		Debounce_delay(delay);
		fill_solid(leds, NUM_LEDS, CHSV(ch1, ch2, ch3));
		strobe_on_flag = true;
	}
}


//----- Matrix
byte matrix_color[3] = {127, 255, 255};		// Array of colors (default IDK, looks like aqua in HSV)
byte matrix_delay = 20;	// Speed of "matrix" transition, delay between strip updates (default 20 ms)

void Matrix(byte ch1, byte ch2, byte ch3, byte delay){
	fadeToBlackBy(leds, NUM_LEDS, random(5, 50));

	leds[random(0, NUM_LEDS)] = CHSV(ch1, ch2, ch3);
	Debounce_delay(delay);	
}



//==================== Functions ====================

void PlayPause(){
	if(play_flag){
		play_flag = false;
		Serial.println(F("===== On Pause ====="));		// DEBUG
		Debounce_delay(1000);
	}
	else {
		play_flag = true;
		Serial.println(F("===== Now Playing ====="));		// DEBUG
		Debounce_delay(1000);
	}
}


void EQ_active(){
	if(eq_flag == false){
		eq_flag = true;
		Serial.println(F("===== Now EQ active ====="));		// DEBUG
		Debounce_delay(1000);
	}
	else{
		eq_flag = false;
		Serial.println(F("===== EQ disabled ====="));		// DEBUG
		Debounce_delay(1000);
	}
}


void Set_value(byte &parameter, byte val){
	byte *ptr = &parameter;
	*ptr = val;

	Serial.println(*ptr);		// DEBUG
}


void Adjust_parameter(byte &parameter, int val, byte min = 0, byte max = 255){
	byte *ptr = &parameter;

	if ((*ptr + val) >= max){
		*ptr = max;
	}
	else if ((*ptr + val) <= min) {
		*ptr = min;
	}
	else {
		*ptr += val;
	}

	Serial.println(*ptr);		// DEBUG
}


void Process_received(){
	if(eq_flag){
		switch (last_butt){
			case MINUS: Adjust_parameter(brightness, -adj); break;
			case PLUS: Adjust_parameter(brightness, adj);	break;
			case BUTT_0: Set_value(brightness, 0); break;
			case BUTT_100: Set_value(brightness, 127);break;
			case BUTT_200: Set_value(brightness, 255); break;
			
			default: break;
		}
		FastLED.setBrightness(brightness);
	}
	else{
		switch (current_effect){
			case SET_COLOR_HSV:
				switch (last_butt){
					case MINUS: Adjust_parameter(set_hsv_color[channel], -adj);	break;
					case PLUS: Adjust_parameter(set_hsv_color[channel], adj);	break;
					case BUTT_0: Set_value(set_hsv_color[channel], 0); break;
					case BUTT_100: Set_value(set_hsv_color[channel], 127); break;
					case BUTT_200: Set_value(set_hsv_color[channel], 255); break;
					
					default: break;
				}
				break;

			case SET_GRADIENT_HSV:
				if (gradient_mode_flag){
					switch (last_butt){
						case MINUS:	Adjust_parameter(gradient_color_1[channel], -adj); break;
						case PLUS: Adjust_parameter(gradient_color_1[channel], adj); break;
						case BUTT_0: Set_value(gradient_color_1[channel], 0);	break;
						case BUTT_100: Set_value(gradient_color_1[channel], 127); break;
						case BUTT_200: Set_value(gradient_color_1[channel], 255); break;

						default:	break;
					}
				}
				else{
					switch (last_butt){
						case MINUS:	Adjust_parameter(gradient_color_2[channel], -adj); break;
						case PLUS: Adjust_parameter(gradient_color_2[channel], adj); break;
						case BUTT_0: Set_value(gradient_color_2[channel], 0);	break;
						case BUTT_100: Set_value(gradient_color_2[channel], 127); break;
						case BUTT_200: Set_value(gradient_color_2[channel], 255); break;

						default:	break;
					}
				}

				switch (last_butt){
					case PREVIOUS: gradient_mode_flag = true; break;
					case NEXT: gradient_mode_flag = false; break;
					
					default:	break;
				}
				break;

			case RAINBOW:
				switch (last_butt){
					case MINUS: Adjust_parameter(rainbow_size, -1, 1, 20); break;
					case PLUS: Adjust_parameter(rainbow_size, 1, 1, 20); break;
					case BUTT_0: Set_value(rainbow_size, 1); break;
					case BUTT_100: Set_value(rainbow_size, 5); break;
					case BUTT_200: Set_value(rainbow_size, 20); break;
					case PREVIOUS: Adjust_parameter(rainbow_delay, -adj, 10); break;
					case NEXT: Adjust_parameter(rainbow_delay, adj, 10); break;

					default: break;
				}
				break;

			case POLICE_SIREN:
				switch (last_butt){
					case MINUS:	Adjust_parameter(siren_delay, -adj, 40); break;
					case PLUS: Adjust_parameter(siren_delay, adj, 40); break;
					case BUTT_0: Set_value(siren_delay, 40);	break;
					case BUTT_100: Set_value(siren_delay, 127); break;
					case BUTT_200: Set_value(siren_delay, 255); break;
					case PREVIOUS: siren_reverse = false; break;
					case NEXT: siren_reverse = true; break;
					
					default:	break;
				}
				break;

			case STROBE:
				switch (last_butt){
					case MINUS:	Adjust_parameter(strobe_color[channel], -adj); break;
					case PLUS: Adjust_parameter(strobe_color[channel], adj); break;
					case BUTT_0: Set_value(strobe_color[channel], 0);	break;
					case BUTT_100: Set_value(strobe_color[channel], 127); break;
					case BUTT_200: Set_value(strobe_color[channel], 255); break;
					case PREVIOUS: Adjust_parameter(strobe_delay, -15); break;
					case NEXT: Adjust_parameter(strobe_delay, 15); break;
					
					default:	break;
				}
				break;

			case MATRIX:
				switch (last_butt){
					case MINUS:	Adjust_parameter(matrix_color[channel], -adj); break;
					case PLUS: Adjust_parameter(matrix_color[channel], adj); break;
					case BUTT_0: Set_value(matrix_color[channel], 0);	break;
					case BUTT_100: Set_value(matrix_color[channel], 127); break;
					case BUTT_200: Set_value(matrix_color[channel], 255); break;
					case PREVIOUS: Adjust_parameter(matrix_delay, -15, 5); break;
					case NEXT: Adjust_parameter(matrix_delay, 15); break;
					
					default: break;
				}
				break;

			case PRESET_COLOR:
				break;
			
			case PRESET_GRADIENT:
				break;
			
			case PRESET_RAINBOW:
				break;
			
			default:
				current_effect = 1;
				break;
		}
	}	
}


void Remote_receive(){
	butt_held_flag = false;

	if (IRLremote.available()){   // Check for a signal from remote
		auto data = IRLremote.read();
		ir_data = data.command;
		ir_flag = true;
	}

	if (ir_flag){   // Decode signal
		if(ir_data != BUTT_PRESSED){
			last_butt = ir_data;
			adj = 5;
		}
		
		switch (ir_data){
			case CH1:
				Serial.println(F("CH-"));		// DEBUG
				channel = 0;
				break;
			case CH2:
				Serial.println(F("CH"));		// DEBUG
				channel = 1;
				break;
			case CH3:
				Serial.println(F("CH+"));		// DEBUG
				channel = 2;
				break;
			
			case PREVIOUS:
				Serial.println(F("Previous"));		// DEBUG
				break;
			case NEXT:
				Serial.println(F("Next"));		// DEBUG
				break;
			case PLAY:
				Serial.println(F("Play"));		// DEBUG
				PlayPause();
				break;

			case MINUS:
				Serial.println(F("-"));		// DEBUG
				break;
			case PLUS:
				Serial.println(F("+"));		// DEBUG
				break;
			case EQ:
				Serial.println(F("EQ"));		// DEBUG
				EQ_active();
				break;
			
			case BUTT_0:
				Serial.println(F("0"));		// DEBUG
				break;
			case BUTT_100:
				Serial.println(F("100"));		// DEBUG
				break;
			case BUTT_200:
				Serial.println(F("200"));		// DEBUG
				break;

			case BUTT_1:
				Serial.println(F("1"));		// DEBUG
				current_effect = SET_COLOR_HSV;
				Mode_change();
				break;
			case BUTT_2:
				Serial.println(F("2"));		// DEBUG
				current_effect = SET_GRADIENT_HSV;
				Mode_change();
				break;
			case BUTT_3:
				Serial.println(F("3"));		// DEBUG
				current_effect = RAINBOW;
				Mode_change();
				break;

			case BUTT_4:
				Serial.println(F("4"));		// DEBUG
				current_effect = POLICE_SIREN;
				Mode_change();
				break;
			case BUTT_5:
				Serial.println(F("5"));		// DEBUG
				current_effect = STROBE;
				Mode_change();
				break;
			case BUTT_6:
				Serial.println(F("6"));		// DEBUG
				current_effect = MATRIX;
				Mode_change();
				break;

			case BUTT_7:
				Serial.println(F("7"));		// DEBUG
				current_effect = PRESET_COLOR;
				Mode_change();
				break;
			case BUTT_8:
				Serial.println(F("8"));		// DEBUG
				current_effect = PRESET_GRADIENT;
				Mode_change();
				break;
			case BUTT_9:
				Serial.println(F("9"));		// DEBUG
				current_effect = PRESET_RAINBOW;
				Mode_change();
				break;

			case BUTT_PRESSED:
				if(last_butt == MINUS){
					Serial.print(F(" \"-\" "));		// DEBUG
				}
				if(last_butt == PLUS){
					Serial.print(F(" \"+\" "));		// DEBUG
				}
				Serial.println(F("held"));		// DEBUG
				if(last_butt == MINUS || last_butt == PLUS){
					butt_held_flag = true;
					adj = 10;
				}
				break;
		
			default:
				break;
		}
		ir_flag = false;
		// Debounce_delay(80);
		Process_received();
	}
}


void Show_effect(){
	if(play_flag){
		switch (current_effect){
			case SET_COLOR_HSV: Set_Colour_HSV(set_hsv_color[0], set_hsv_color[1], set_hsv_color[2]); break;
			case SET_GRADIENT_HSV: Gradient(gradient_mode_flag, gradient_reverse_flag); break;
			case RAINBOW: Rainbow(rainbow_size, rainbow_delay); break;
			case POLICE_SIREN: Police_siren(siren_delay); break;
			case STROBE: Strobe(strobe_color[0], strobe_color[1], strobe_color[2], strobe_delay); break;
			case MATRIX: Matrix(matrix_color[0], matrix_color[1], matrix_color[2], matrix_delay); break;

			case PRESET_COLOR: fill_solid(leds, NUM_LEDS, CRGB::Aqua); break;
			case PRESET_GRADIENT: fill_gradient(leds, NUM_LEDS, CHSV(180, 255, 255), CHSV(60, 255, 255), FORWARD_HUES); break;
			case PRESET_RAINBOW: Rainbow(3, 30); break;
			
			default: current_effect = 1; break;
		}
	}
	if(eq_flag){
		fill_few(true, CRGB::Black);
		fill_few(true, CRGB::White, 3);
	}
	if(!play_flag){
		fill_few(true, CRGB::Black);
		fill_few(true, CRGB::Red, 3);
	}

	FastLED.show();
}


//==================== Main ====================

void setup() {
	Serial.begin(9600);
	Serial.println(F("Startup"));   // DEBUG

	Debounce_delay(2000);		// Startup delay

	pinMode(IR_PIN, INPUT);
	pinMode(LEDS_PIN, INPUT);

	if (!IRLremote.begin(IR_PIN)){		// DEBUG
		Serial.println(F("You did not choose a valid pin."));
	}
		
	FastLED.addLeds <WS2812B, LEDS_PIN, GRB> (leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	FastLED.setBrightness(brightness);

	 Start_up();
}

void loop() {
	if (!IRLremote.receiving()){
		Show_effect();
  }

	Remote_receive();

	if (ir_flag){
		Process_received();
	}
}