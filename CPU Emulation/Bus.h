#pragma once
#include<cstdint>
#include<array>

#include "CPU.h"

class Bus
{
public:
	Bus();
	~Bus();

	//Devices
	CPU mainCPU;
	std::array<uint8_t, 64 * 1024> ram;

	//Member Functions
	uint8_t Read(uint16_t address, bool readOnly);
	void Write(uint16_t address, uint8_t data);
};

