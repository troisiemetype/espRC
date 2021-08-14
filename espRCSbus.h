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