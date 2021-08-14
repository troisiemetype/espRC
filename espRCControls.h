#ifndef ESP_RC_CONTROLS_H
#define ESP_RC_CONTROLS_H

#include <Arduino.h>

class espRCControls{
public:

	struct controlData_t{
		int16_t *channel;
		uint8_t numChannel;
	};

	virtual bool update() = 0;

protected:
	controlData_t _data;
	int16_t _resolution;
	int16_t _neutral;
	uint8_t _pin;
	int16_t *_tempCh;
	volatile bool _hasNew;
};

class espRCControlsIn : public espRCControls{
public:
	virtual bool update() = 0;

	controlData_t* getChannels();
	int16_t getChannel(uint8_t channel);
	uint8_t getNumberChannels();

private:

};

class espRCControlsOut : public espRCControls{
public:
	virtual bool update() = 0;

	void setChannels(controlData_t *data);
	void setChannel(uint8_t channel, int16_t value);
	void setNumberChannels(int16_t numberChannel);

private:

};

#endif