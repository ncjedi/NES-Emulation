#pragma once

#include "Bus.h"

class PPU
{
public:
	PPU();
	~PPU();

	//Main bus communications
	uint8_t CPURead(uint16_t address, bool readOnly = false);
	void CPUWrite(uint16_t address, uint8_t data);

	//PPU bus communications
	uint8_t PPURead(uint16_t address, bool readOnly = false);
	void PPUWrite(uint16_t address, uint8_t data);

	//PPU bus devices
	uint8_t nameTable[2][1024];
	uint8_t paletteTable[32];

	void InsertCartrage(const std::shared_ptr<Cartridge>& cartirage);
	void Clock();

private:
	std::shared_ptr<Cartridge> mainCartriage;
};

