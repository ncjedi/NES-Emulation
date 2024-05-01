#include <iostream>
#include <string>

#include "Bus.h"

int main()
{
	Bus bus;
	std::string temp;

	//Set the ending point. 1FFF refers back to itself in a loop.
	bus.ram[0xFFFE] = 0xFF;
	bus.ram[0xFFFF] = 0x1F;
	bus.ram[0x1FFF] = 0x00;

	//Set a value
	bus.ram[0x0200] = 0xFF;

	//set reset address
	bus.ram[0xFFFC] = 0x00;
	bus.ram[0xFFFD] = 0x01;

	//load accumulator with value
	bus.ram[0x0100] = 0xAD;
	bus.ram[0x0101] = 0x00;
	bus.ram[0x0102] = 0x02;

	//transfer accumulator to x register
	bus.ram[0x0103] = 0xAA;

	//Roll accumulator left then right
	bus.ram[0x0104] = 0x2A;
	bus.ram[0x0105] = 0x6A;

	//Roll accumulator left then add carry bit if there is a carry bit (if there is branch 0x02 forwards else jump over the if statment)
	//bus.ram[0x0106] = 0x2A; // roll left
	bus.ram[0x0106] = 0x22; //do nothing (for testing else)

	bus.ram[0x0107] = 0xB0; //if the carry bit is set...
	bus.ram[0x0108] = 0x03; //branch to 010C! (for some reason this sets it to 010C instead of 010B... but kind of convienent because just count the number of lines you need to jump over!)

	bus.ram[0x0109] = 0x4C; //else jump to 0111
	bus.ram[0x010A] = 0x11;
	bus.ram[0x010B] = 0x01;

	//if statment
	bus.ram[0x010C] = 0x69; //Add...
	bus.ram[0x010D] = 0x00; //Zero to the accumulator but the carry bit is also added!
	bus.ram[0x010E] = 0x4C; //jump over else statment(0113)
	bus.ram[0x010F] = 0x13;
	bus.ram[0x0110] = 0x01;

	//else statment
	bus.ram[0x0111] = 0xE9;//subtract...
	bus.ram[0x0112] = 0x36;//54 from the accumulator!

	bus.mainCPU.Reset();

	while(bus.mainCPU.pc != 0x1FFF)
	{
		bus.mainCPU.Clock();
	}

	std::cout << "ADDRESS: " << unsigned(bus.mainCPU.GetAddrAbs()) << " PROGRAM COUNTER: " << unsigned(bus.mainCPU.pc) << " ACCUMULATOR: " << unsigned(bus.mainCPU.a) << " X REGISTER: " << unsigned(bus.mainCPU.x) << " REL ADDRESS: " << unsigned(bus.mainCPU.GetAddrRel());
	std::cin >> temp;
}