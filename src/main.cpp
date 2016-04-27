#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <time.h>
#include <stdbool.h>

const uint8_t _PWM_MOTOR_PIN = 14;
const uint8_t _PWM_UP_BUTTON = 4;
const uint8_t _PWM_DOWN_BUTTON = 5;

//default PWM range its 1024 but let make things easier
const int _PWM_LEVELS = 11;
const int _PWM_VALUES[_PWM_LEVELS] =
{0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};

int currentPWMLevel = 0;
bool buttonPressed = false;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  //don't need wifi anyway
  WiFi.mode(WIFI_OFF);
  
  pinMode(_PWM_UP_BUTTON, INPUT);
  pinMode(_PWM_DOWN_BUTTON, INPUT);
  pinMode(_PWM_MOTOR_PIN, OUTPUT);
  Serial.printf("\nEverything working...\n");
  
  analogWrite(_PWM_MOTOR_PIN, _PWM_VALUES[currentPWMLevel]);
}

void loop() {
	//if button is not pressed from previous loop
	if (!buttonPressed)
	{
		if (digitalRead(_PWM_UP_BUTTON))
		{
			currentPWMLevel++;
			Serial.println("UP");
		}
		
		if (digitalRead(_PWM_DOWN_BUTTON))
		{
			currentPWMLevel--;
			Serial.println("DOWN");
		}
		
		//level become out of bounds
		if (currentPWMLevel > _PWM_LEVELS - 1)
		{
			currentPWMLevel = _PWM_LEVELS - 1;
		}
		else if (currentPWMLevel < 0)
		{
			currentPWMLevel = 0;
		}
		
		analogWrite(_PWM_MOTOR_PIN, _PWM_VALUES[currentPWMLevel]);
	}
	
	buttonPressed = digitalRead(_PWM_UP_BUTTON) || digitalRead(_PWM_DOWN_BUTTON);
	
	delay(50);
}
