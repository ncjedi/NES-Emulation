#pragma once
#include "Mapper.h"

class Mapper0 : public Mapper
{
public:
	Mapper0();
	~Mapper0();

	bool CPUMapRead(uint16_t address, uint32_t& mappedAddress) override;
	bool CPUMapWrite(uint16_t address, uint32_t& mappedAddress) override;
	bool PPUMapRead(uint16_t address, uint32_t& mappedAddress) override;
	bool PPUMapWrite(uint16_t address, uint32_t& mappedAddress) override;
};

