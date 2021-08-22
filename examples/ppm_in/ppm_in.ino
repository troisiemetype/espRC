/*
 * This program is part an esp32 library to read and write RC protocols
 * Copyright (C) 2021  Pierre-Loup Martin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "espRCPpm.h"

const uint8_t PIN_PPM = 16;

uint8_t numChannels = 0;

RCPpmIn ppmIn(PIN_PPM, 0);

//espRCControls controls;
/*
void ppmISR(){
	ppmIn.isr();
}
*/
void setup(){
	Serial.begin(115200);

	numChannels = ppmIn.getNumberChannels();

//	attachInterrupt(PIN_PPM, ppmISR, RISING);

}

void loop(){
	if(ppmIn.update()){
		for(uint8_t i = 0; i < numChannels; ++i){
			Serial.printf("%i\t", ppmIn.getChannel(i));
		}
		Serial.println();
	}
}