#include "espRCPpm.h"

espRCPpmIn::espRCPpmIn(uint8_t pin, uint8_t timer, uint8_t numChannel, uint16_t neutral){
	if(numChannel > 16) return;
	if(timer > 3) return;

	_data.channel = new int16_t[numChannel];
	_tempCh = new int16_t[numChannel];
	_data.numChannel = numChannel;

	memset(_data.channel, 0, sizeof(int16_t) * numChannel);
	memset(_tempCh, 0, sizeof(int16_t) * numChannel);

	_neutral = neutral;
	_resolution = 1024;
	_currentCh = 0;

	_mux = portMUX_INITIALIZER_UNLOCKED;

	pinMode(_pin, INPUT);

	_timer = timerBegin(timer, 40, true);
}

espRCPpmIn::~espRCPpmIn(){
	delete[] _data.channel;
	delete[] _tempCh;
}

bool espRCPpmIn::update(){
	if(!_hasNew) return false;
	_hasNew = false;

	for (uint8_t i = 0; i < _data.numChannel; ++i){
		portENTER_CRITICAL_ISR(&_mux);
		_data.channel[i] = _tempCh[i] - _neutral;
		portEXIT_CRITICAL_ISR(&_mux);
	}

	return true;
}

void espRCPpmIn::isr(){
	uint64_t time = timerRead(_timer);
	timerRestart(_timer);
	if(time > 6000){
		_currentCh = 0;
		_hasNew = true;
	} else {
		portENTER_CRITICAL_ISR(&_mux);
		_tempCh[_currentCh] = (uint16_t)time;
		portEXIT_CRITICAL_ISR(&_mux);
		if(++_currentCh >= _data.numChannel){
			_currentCh--;
		}
	}

}