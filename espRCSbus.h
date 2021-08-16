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

#ifndef ESP_RC_CONTROLS_SBUS_H
#define ESP_RC_CONTROLS_SBUS_H

#include <Arduino.h>

#include "espRCControls.h"

class espRCSbus{
public:
	virtual bool update() = 0;

	const uint8_t FRAME_LENGTH = 25;
	const uint8_t HEADER = 0x0F;
	const uint8_t FOOTER = 0x00;
	const uint16_t NEUTRAL = 992;
	const uint16_t RESOLUTION = 819;
	const uint8_t NUM_CHANNEL = 18;

protected:

};

class espRCSbusIn : public espRCControlsIn, public espRCSbus{
public:
	espRCSbusIn(uint8_t pin, uint8_t serial);
	~espRCSbusIn();

	bool update();

protected:
	void _processChannels();

	HardwareSerial _sbus;
	uint8_t *_input;
	uint8_t _lastByte;
	uint8_t _index;
	
};

class espRCSbusOut : public espRCControlsOut, public espRCSbus{
public:
	espRCSbusOut(uint8_t pin);
	~espRCSbusOut();

	bool update();

protected:
	
};

#endif