#include "PPU.h"

uint8_t PPU::CPURead(uint16_t address, bool readOnly)
{
	uint8_t data = 0x00;

	switch (address)
	{
	case 0x0000:
		break;
	case 0x0001:
		break;
	case 0x0002:
		break;
	case 0x0003:
		break;
	case 0x0004:
		break;
	case 0x0005:
		break;
	case 0x0006:
		break;
	case 0x0007:
		break;
	}

	return data;
}

void PPU::CPUWrite(uint16_t address, uint8_t data)
{
	switch (address)
	{
	case 0x0000:
		break;
	case 0x0001:
		break;
	case 0x0002:
		break;
	case 0x0003:
		break;
	case 0x0004:
		break;
	case 0x0005:
		break;
	case 0x0006:
		break;
	case 0x0007:
		break;
	}
}

uint8_t PPU::PPURead(uint16_t address, bool readOnly = false)
{
	uint8_t data = 0x00;

	address &= 0x3FFF;

	if (mainCartriage->PPURead(address, data)) // thing for video guy's implimentation. probably will change this later. Wanna keep it the same as his for the moment though ***
	{

	}

	return data;
}

void PPU::PPUWrite(uint16_t address, uint8_t data)
{
	address &= 0x3FFF;

	if (mainCartriage->PPUWrite(address, data)) // thing for video guy's implimentation. probably will change this later. Wanna keep it the same as his for the moment though ***
	{

	}
}

void PPU::InsertCartrage(const std::shared_ptr<Cartridge>& cartirage)
{
	mainCartriage = cartirage;
}

void PPU::Clock()
{

}