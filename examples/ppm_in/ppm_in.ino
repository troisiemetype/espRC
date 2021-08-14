#include "espRCPpm.h"

const uint8_t PIN_PPM = 16;

uint8_t numChannels = 0;

espRCPpmIn ppmIn(PIN_PPM, 0);

//espRCControls controls;

void ppmISR(){
	ppmIn.isr();
}

void setup(){
	Serial.begin(115200);

	numChannels = ppmIn.getNumberChannels();
//
	attachInterrupt(PIN_PPM, ppmISR, RISING);

}

void loop(){
	if(ppmIn.update()){
		for(uint8_t i = 0; i < numChannels; ++i){
			Serial.printf("%i\t", ppmIn.getChannel(i));
		}
		Serial.println();
	}
}