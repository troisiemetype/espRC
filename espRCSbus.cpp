#include "espRCSbus.h"

espRCSbusIn::espRCSbusIn(uint8_t pin, uint8_t serial) : _sbus(serial){
	if(serial > 2) return;

	_sbus.begin(100000, SERIAL_8E2, pin, -1, true);
	pinMode(pin,INPUT);

	_pin = pin;
	_neutral = NEUTRAL;
	_resolution = RESOLUTION;
	_lastByte = 0xff;
	_index = 0;

	_data.channel = new int16_t[NUM_CHANNEL];
	_tempCh = new int16_t[NUM_CHANNEL];
	_input = new uint8_t[FRAME_LENGTH];

	memset(_data.channel, 0, sizeof(int16_t) * NUM_CHANNEL);
	memset(_tempCh, 0, sizeof(int16_t) * NUM_CHANNEL);
	memset(_input, 0, sizeof(int8_t) * FRAME_LENGTH);
	_data.numChannel = NUM_CHANNEL;
}

espRCSbusIn::~espRCSbusIn(){
	delete[] _data.channel;
	delete[] _tempCh;

}

bool espRCSbusIn::update(){
	while(_sbus.available()){
		uint8_t b = _sbus.read();

		if(b == HEADER && _lastByte == FOOTER){
			_index = 0;
		} else if(_index >= FRAME_LENGTH){
			_index = 0;
		} else {
			_index++;
		}

		_input[_index] = b;
		_lastByte = b;

		if(_index == (FRAME_LENGTH - 1) && b == FOOTER){
			_processChannels();
			return true;
		}
	}
	return false;
}

void espRCSbusIn::_processChannels(){
	memset(_tempCh, 0, sizeof(int16_t) * NUM_CHANNEL);

	for (uint8_t i = 0; i < 176; ++i){
		uint8_t outBitIndex = i % 11;
		uint8_t inBitIndex = i % 8;
		_tempCh[i / 11] |= (((uint16_t)_input[(i / 8) + 1] >> inBitIndex) & 0x1) << outBitIndex;
	}

	_data.channel[16] = (_input[23] >> 7) & 0x1;
	_data.channel[17] = (_input[23] >> 6) & 0x1;

	_data.channel[16] = _neutral - _resolution + 2 * _data.channel[16];
	_data.channel[17] = _neutral - _resolution + 2 * _data.channel[17];

	for(uint8_t i = 0; i < NUM_CHANNEL; ++i){
		_data.channel[i] = (int16_t)_tempCh[i] - _neutral;
	}

}
