#include "espRCControls.h"

espRCControls::controlData_t* espRCControlsIn::getChannels(){
	return &_data;
}

int16_t espRCControlsIn::getChannel(uint8_t channel){
	if(channel > _data.numChannel) return 0;
	return _data.channel[channel];
}

uint8_t espRCControlsIn::getNumberChannels(){
	return _data.numChannel;
}
