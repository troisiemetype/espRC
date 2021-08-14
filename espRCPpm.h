#ifndef ESP_RC_CONTROLS_PPM_H
#define ESP_RC_CONTORLS_PPM_H

#include <Arduino.h>

#include "espRCControls.h"

class espRCPpmIn : public espRCControlsIn{
public:
	espRCPpmIn(uint8_t pin, uint8_t timer, uint8_t numChannel = 8, uint16_t neutral = 3000);
	~espRCPpmIn();
	
	bool update();

	void isr();

protected:
	hw_timer_t *_timer;
	portMUX_TYPE _mux;
	int8_t _currentCh;
};

#endif