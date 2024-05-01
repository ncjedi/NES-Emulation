#include "Bus.h"

Bus::Bus()
{
	mainCPU.ConnectBus(this);

	//Clear Ram
	for (uint8_t i : ram) i = 0x00;
}
Bus::~Bus()
{

}

uint8_t Bus::Read(uint16_t address, bool readOnly)
{
	uint8_t data = 0x00;

	if (mainCartirage->CPURead(address, data)) // thing for video guy's implimentation. probably will change this later. Wanna keep it the same as his for the moment though ***
	{

	}
	else if (address >= 0x0000 && address <= 0x1FFF)
	{
		data = ram[address & 0x07FF];
	}
	else if (address >= 0x2000 && address <= 0x3FFF)
	{
		data = ppu.CPURead(address & 0x0007);
	}

	return data;
}
void Bus::Write(uint16_t address, uint8_t data)
{
	if (mainCartirage->CPUWrite(address, data)) // thing for video guy's implimentation. probably will change this later. Wanna keep it the same as his for the moment though ***
	{

	}
	else if (address >= 0x0000 && address <= 0x1FFF)
	{
		ram[address & 0x07FF] = data;
	}
	else if (address >= 0x2000 && address <= 0x3FFF)
	{
		ppu.CPUWrite(address & 0x0007, data);
	}
}

void Bus::InsertCartrage(const std::shared_ptr<Cartridge>& cartirage)
{
	mainCartirage = cartirage;
	ppu.InsertCartrage(cartirage);
}

void Bus::Reset()
{
	mainCPU.Reset();
	nSystemClockCounter = 0;
}

void Bus::Clock()
{

}
