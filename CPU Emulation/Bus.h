#pragma once
#include<cstdint>
#include<array>
#include<memory>

#include "CPU.h"
#include "PPU.h"
#include "Cartridge.h"

class Bus
{
public:
	Bus();
	~Bus();

	//Devices
	CPU mainCPU;
	PPU ppu;
	std::array<uint8_t, 2048> ram; // would like to make a class for this with mirroring built in

	std::shared_ptr<Cartridge> mainCartirage;

	//Member Functions
	uint8_t Read(uint16_t address, bool readOnly);
	void Write(uint16_t address, uint8_t data);

	void InsertCartrage(const std::shared_ptr<Cartridge>& cartirage);
	void Reset();
	void Clock();

private:
	uint32_t nSystemClockCounter = 0;
};

