#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <time.h>
#include <stdbool.h>

const uint8_t _PWM_MOTOR_PIN = 14;

int _pot_read = 0;
int _count = 0;

void setup() {
  pinMode(_PWM_MOTOR_PIN, OUTPUT);
  analogWrite(_PWM_MOTOR_PIN, 0);
  
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  //don't need wifi anyway
  WiFi.mode(WIFI_OFF);
  
  Serial.printf("\nEverything working...\n");
}

void loop() {

	//read potentiometer values from ADC - esp8266 just have one
	//IMPORTANT: use a voltage divider to drop 0 - 3.3v to 0 - 1v
	
	//pot_output-------220ohms--------100ohms------GND
	//                           |
	//                        ESP ADC
	//example on schematic.png
	
	_pot_read = analogRead(A0); //ranges from 0 to 1023
	
	//roundings
	if (_pot_read < 30) _pot_read = 0;
	
	if (_pot_read > 900) _pot_read = 1023;
		
	analogWrite(_PWM_MOTOR_PIN, _pot_read);
	
	//a counter to debug analog read
	if (_count == 10)
	{
		Serial.printf("Analog read: %i \n", _pot_read);
		_count = 0;
	}
		
	delay(100);
	_count++;
}
