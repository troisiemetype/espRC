#include "espRCSbus.h"

const uint8_t PIN_SBUS = 16;

uint8_t numChannels = 0;

espRCSbusIn sbusIn(PIN_SBUS, 1);

void setup(){
	Serial.begin(115200);

	numChannels = sbusIn.getNumberChannels();
}

void loop(){
	if(sbusIn.update()){
		for(uint8_t i = 0; i < numChannels; ++i){
			Serial.printf("%i\t", sbusIn.getChannel(i));
		}
		Serial.println();
	}
}