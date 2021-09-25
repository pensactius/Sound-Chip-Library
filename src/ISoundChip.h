#pragma once
#include <stdint.h>

class ISoundChip
{

public:
	~ISoundChip();

	virtual void begin() = 0;
	virtual void writeData(uint8_t data) const = 0;
	virtual void writeData(uint8_t reg, uint8_t data) const = 0;

	// Silence all channels in the sound chip
	virtual void muteAll() const = 0;
};
