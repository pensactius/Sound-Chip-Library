#pragma once

#include "ISoundChip.h"


class Sn76489 : ISoundChip
{

public:
	Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we);
	Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we, int ce);
	Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we, int ce, int rdy);
	~Sn76489();

	// Initialize Sn76489 sound chip, mostly pin modes (IN/OUT)
	void begin();
	
	// Write byte of data to Sn76489 sound chip
	void writeData(uint8_t data) const;
	
	// Not used in the Sn76489 sound chip
	void writeData(uint8_t reg, uint8_t data) const;
	
	void muteAll() const;

	void dbgPrint() const;

private:
	void enableBus() const;

	int m_dataBus[8];
	int m_we;
	int m_ce;
	int m_rdy;
};
