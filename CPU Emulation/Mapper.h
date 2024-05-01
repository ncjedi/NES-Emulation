#pragma once
#include<cstdint>

class Mapper
{
public:
	Mapper(uint8_t PRGBanks, uint8_t CHRBanks);
	virtual ~Mapper();

	virtual bool CPUMapRead(uint16_t address, uint32_t& mappedAddress) = 0;
	virtual bool CPUMapWrite(uint16_t address, uint32_t& mappedAddress) = 0;
	virtual bool PPUMapRead(uint16_t address, uint32_t& mappedAddress) = 0;
	virtual bool PPUMapWrite(uint16_t address, uint32_t& mappedAddress) = 0;

protected:
	uint8_t mainPRGBanks = 0;
	uint8_t mainCHRBanks = 0;
};

