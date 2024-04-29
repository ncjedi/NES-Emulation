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
	if (address >= 0x0000 && address <= 0xFFFF)
	{
		return ram[address];
	}
}
void Bus::Write(uint16_t address, uint8_t data)
{
	if (address >= 0x0000 && address <= 0xFFFF)
	{
		ram[address] = data;
	}
}