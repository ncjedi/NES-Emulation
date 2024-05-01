#include <fstream>

#include "Bus.h"

#include "Mapper0.h"

#pragma once
class Cartridge
{
public:
	Cartridge(const std::string& fileName);
	~Cartridge();

	//Main bus communications
	bool CPURead(uint16_t address, uint8_t &data);
	bool CPUWrite(uint16_t address, uint8_t data);

	//PPU bus communications
	bool PPURead(uint16_t address, uint8_t& data);
	bool PPUWrite(uint16_t address, uint8_t data);

private:
	std::vector<uint8_t> vPRGMemory;
	std::vector<uint8_t> vCHRMemory;

	uint8_t mapperID = 0;
	uint8_t nPRGBanks = 0;
	uint8_t nCHRBanks = 0;

	std::shared_ptr<Mapper> mainMapper;
};

