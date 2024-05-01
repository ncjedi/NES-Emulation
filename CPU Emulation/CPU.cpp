#include "CPU.h"
#include "Bus.h"

CPU::CPU()
{
	using a = CPU;
	lookup =
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};
}

CPU::~CPU()
{

}

void CPU::ConnectBus(Bus* connection)
{
	bus = connection;
}

uint8_t CPU::Read(uint16_t address)
{
	return bus->Read(address, false);
}

void CPU::Write(uint16_t address, uint8_t data)
{
	bus->Write(address, data);
}

void CPU::Clock()
{
	if (cycles == 0)
	{
		opcode = Read(pc);

		SetFlag(U, true);

		pc++;

		cycles = lookup[opcode].cycles;

		//Do these functions need to be set to variables or can they be directly put into the and statment? ***
		uint8_t checkAdditionalCycles1 = (this->*lookup[opcode].addrmode)();
		uint8_t checkAdditionalCycles2 = (this->*lookup[opcode].operate)();
		cycles += (checkAdditionalCycles1 && checkAdditionalCycles2);

		SetFlag(U, true);
	}

	cycles--;
}

//Reset the CPU
void CPU::Reset()
{
	addr_abs = 0xFFFC;
	uint16_t lowByte = Read(addr_abs + 0);
	uint16_t highByte = Read(addr_abs + 1);

	pc = (highByte << 8) | lowByte;

	a = 0;
	x = 0;
	y = 0;
	sktp = 0;
	status = 0x00 | U;

	addr_rel = 0x00;
	addr_abs = 0x0000;
	fetched = 0x00;

	cycles = 8;
}

void CPU::IRQ()
{
	if (GetFlag(I) == 0)
	{
		Write(0x0100 + sktp, (pc >> 8) & 0x00FF);
		sktp--;
		Write(0x0100 + sktp, pc & 0x00FF);
		sktp--;

		SetFlag(B, 0);
		SetFlag(U, 1);
		SetFlag(I, 1);

		Write(0x0100 + sktp, status);
		sktp--;

		addr_abs = 0xFFFE;
		uint16_t lowByte = Read(addr_abs + 0);
		uint16_t highByte = Read(addr_abs + 1);
		pc = (highByte << 8) | lowByte;

		cycles = 7;
	}
}

void CPU::NMI()
{
	Write(0x0100 + sktp, (pc >> 8) & 0x00FF);
	sktp--;
	Write(0x0100 + sktp, pc & 0x00FF);
	sktp--;

	SetFlag(B, 0);
	SetFlag(U, 1);
	SetFlag(I, 1);

	Write(0x0100 + sktp, status);
	sktp--;

	addr_abs = 0xFFFA;
	uint16_t lowByte = Read(addr_abs + 0);
	uint16_t highByte = Read(addr_abs + 1);
	pc = (highByte << 8) | lowByte;

	cycles = 8;
}

//Gets whether a flag is set in the status flags by ANDing that one bit with the rest of the status flag bits
uint8_t CPU::GetFlag(Flags f)
{
	return((status & f) > 0) ? 1 : 0;
}

//Takes in a flag and a bool. if the bool is true the flag is set by ORing the one bit of the flag with the rest of the status flags. If the bool is not true the flag is unset by ANDing the inverse that one bit with the rest of the status flags
void CPU::SetFlag(Flags f, bool v)
{
	if (v)
	{
		status |= f;
	}
	else
	{
		status &= ~f;
	}
}

//Fetches data from the absolute address if the address mode is not implied
uint8_t CPU::Fetch()
{
	if (!(lookup[opcode].addrmode == &CPU::IMP))
	{
		fetched = Read(addr_abs);
	}
	return fetched;
}

//--------------------Addressing modes--------------------

//Implied addressing does nothing but it might use the accumulator so throw that in there
uint8_t CPU::IMP()
{
	fetched = a;
	return 0;
}

//Immideate addressing gets the next boy coming up
uint8_t CPU::IMM()
{
	addr_abs = pc++;
	return 0;
}

//Zero page addressing gets addresses from the zeroth page (also x and y offset functions)
uint8_t CPU::ZP0()
{
	addr_abs = Read(pc);
	pc++;
	addr_abs &= 0x00FF; //Does this and need to be here? if we're assigning a 16 bit variable with an 8 bit one shouldn't the first 8 bits be 0 anyawys? ***
	return 0;
}

uint8_t CPU::ZPX()
{
	addr_abs = Read(pc + x);
	pc++;
	addr_abs &= 0x00FF; //Does this and need to be here? if we're assigning a 16 bit variable with an 8 bit one shouldn't the first 8 bits be 0 anyawys? ***
	return 0;
}

uint8_t CPU::ZPY()
{
	addr_abs = Read(pc + y);
	pc++;
	addr_abs &= 0x00FF; //Does this and need to be here? if we're assigning a 16 bit variable with an 8 bit one shouldn't the first 8 bits be 0 anyawys? ***
	return 0;
}

//Absolute addressing takes in an address as a value (also x and y offset functions)
uint8_t CPU::ABS()
{
	uint16_t lowBit = Read(pc);
	pc++;
	uint16_t highBit = Read(pc);
	pc++;

	addr_abs = (highBit << 8) | lowBit;

	return 0;
}

uint8_t CPU::ABX()
{
	uint16_t lowBit = Read(pc);
	pc++;
	uint16_t highBit = Read(pc);
	pc++;

	addr_abs = (highBit << 8) | lowBit;
	addr_abs += x;

	if ((addr_abs & 0xFF00) != (highBit << 8)) //Page fault :(
	{
		return 1;
	}
	else //surely this else isn't nessessary. but. keeping it as the video guy has it first. but in testing this is the FIRST THING TO GO ***
	{
		return 0;
	}
}

uint8_t CPU::ABY()
{
	uint16_t lowBit = Read(pc);
	pc++;
	uint16_t highBit = Read(pc);
	pc++;

	addr_abs = (highBit << 8) | lowBit;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (highBit << 8)) //Page fault :(
	{
		return 1;
	}
	else //surely this else isn't nessessary. but. keeping it as the video guy has it first. but in testing this is the FIRST THING TO GO ***
	{
		return 0;
	}
}

//Indirect addressing is an address with an address as it's value (so basically a pointer) the value is used as the address
uint8_t CPU::IND()
{
	uint16_t lowBit = Read(pc);
	pc++;
	uint16_t highBit = Read(pc);
	pc++;

	uint16_t pointer = (highBit << 8) | lowBit;

	//The cpu has a bug when on the edge of a page and goes whacko so this emulates that
	if (lowBit == 0x00FF)
	{
		addr_abs = (Read(pointer & 0xFF00) << 8) | Read(pointer);
	}
	else
	{
		addr_abs = (Read(pointer + 1) << 8) | Read(pointer);
	}

	return 0;
}

//Indirect zero page x register offset addressing. it's weird. like absolute addressing but the VALUE address is offset by the x register.
uint8_t CPU::IZX()
{
	uint16_t address = Read(pc);
	pc++;

	uint16_t lowBit = Read((uint16_t)(address + (uint16_t)x) & 0x00FF); //why wouldn't the address plus 16 bit x already be a 16 bit value? ***
	uint16_t highBit = Read((uint16_t)(address + (uint16_t)x + 1) & 0x00FF); //same HERE ***

	addr_abs = (highBit << 8) | lowBit;

	return 0;
}

/*
Indirect zero page y register offset addressing is EVEN MORE WEIRD because it's not a mirror of the x resgister offset version.
Instead this addressing mode gets the value and THEN offsets it by the y register.
This also introduces a page fault if the low byte is FF. No idea why this is the way it is. I think someone was confused.
*/
uint8_t CPU::IZY()
{
	uint16_t address = Read(pc);
	pc++;

	uint16_t lowBit = Read(address & 0x00FF);
	uint16_t highBit = Read((address + 1) & 0x00FF);

	addr_abs = (highBit << 8) | lowBit;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (highBit << 8)) //Page fault :(
	{
		return 1;
	}
	else //surely this else isn't nessessary. but. keeping it as the video guy has it first. but in testing this is the FIRST THING TO GO ***
	{
		return 0;
	}
}

//Realitive addressing. The only addressing mode to use the realitive address variable. It reads an address directly but that address can only be 1 byte long and is realitive to the instruction. Mostly if not entirely used for branching.
uint8_t CPU::REL()
{
	addr_rel = Read(pc);
	pc++;

	if (addr_rel & 0x80) //Check if the realitive address is negitive
	{
		addr_rel |= 0xFF00; //Not sure why we're ORing an 8 bit chracter with a 16 bit one but the video guy said to. so if something breaks with branching this is probably why. ***
	}

	return 0;
}

//--------------------Instructions--------------------

//ANDs the data fetched and the accumulator
uint8_t CPU::AND()
{
	Fetch();
	a = a & fetched;

	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);

	return 1;
}

//Branching instructions based on flags in the status

uint8_t CPU::BCS()
{
	if (GetFlag(C) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BCC()
{
	if (GetFlag(C) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BEQ()
{
	if (GetFlag(Z) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BMI()
{
	if (GetFlag(N) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BNE()
{
	if (GetFlag(Z) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BPL()
{
	if (GetFlag(N) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BVC()
{
	if (GetFlag(V) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}
	return 0;
}

uint8_t CPU::BVS()
{
	if (GetFlag(V) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}
	return 0;
}

//Clearing bits in status instructions

uint8_t CPU::CLC()
{
	SetFlag(C, false);
	return 0;
}

uint8_t CPU::CLD()
{
	SetFlag(D, false);
	return 0;
}

uint8_t CPU::CLI()
{
	SetFlag(I, false);
	return 0;
}

uint8_t CPU::CLV()
{
	SetFlag(V, false);
	return 0;
}

//Addition instruction
uint8_t CPU::ADC()
{
	Fetch();

	uint16_t sum = (uint16_t)a + (uint16_t)fetched + (uint16_t)GetFlag(C);

	SetFlag(C, sum > 255);
	SetFlag(Z, (sum & 0x00FF) == 0);//why not just check if sum is 0? ***
	SetFlag(N, (sum & 0x80));
	SetFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)sum)) & 0x0080); //Check this for missplaced parenthesies. Also why is everything convereted to 16 bit characters?? ***

	a = sum & 0x00FF;

	return 1;
}

//Subtraction instruction
uint8_t CPU::SBC()
{
	Fetch();

	uint16_t invertedFetch = ((uint16_t)fetched) ^ 0x00FF;

	uint16_t sum = (uint16_t)a + invertedFetch + (uint16_t)GetFlag(C);

	SetFlag(C, sum & 0xFF00);
	SetFlag(Z, (sum & 0x00FF) == 0);//why not just check if sum is 0? ***
	SetFlag(N, (sum & 0x80));
	SetFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & (sum ^ invertedFetch)) & 0x0080); //Check this for missplaced parenthesies. Also why is everything convereted to 16 bit characters?? ***

	a = sum & 0x00FF;

	return 1;
}

//Arithmatic shift left
uint8_t CPU::ASL()
{
	Fetch();

	uint16_t shift = (uint16_t)fetched << 1;

	SetFlag(C, shift & 0xFF00);
	SetFlag(Z, (shift & 0x00FF) == 0);//why not just check if sum is 0? ***
	SetFlag(N, (shift & 0x80));

	if (lookup[opcode].addrmode == &CPU::IMP)
	{
		a = shift & 0x00FF;
	}
	else
	{
		Write(addr_abs, shift & 0x00FF);
	}

	return 0;
}

/*
I have no idea what this instruction does.There's no documentation for it. 
It seems to just set some of the status bits according to the instruction's data.
However for the zero bit the accumulator is used.
*/
uint8_t CPU::BIT()
{
	Fetch();

	uint16_t data = a & fetched;

	SetFlag(Z, (data & 0x00FF) == 0x00);
	SetFlag(N, fetched & (1 << 7));
	SetFlag(V, fetched & (1 << 6));
	
	return 0;
}

//An internal program interupt. Instead of one called by the two external interupts.
uint8_t CPU::BRK()
{
	pc++;

	SetFlag(I, 1);

	Write(0x0100 + sktp, (pc >> 8) & 0x00FF);
	sktp--;
	Write(0x0100 + sktp, pc & 0x00FF);
	sktp--;

	SetFlag(B, 1);
	Write(0x0100 + sktp, status);
	sktp--;
	SetFlag(B, 0);

	pc = (uint16_t)Read(0xFFFE) | ((uint16_t)Read(0xFFFF) << 8);

	return 0;
}

//Comparisons. Compares the value in the CPU to the fetched data and sets status bits accordingly. If the CPU's value is greater than or equal to the data the carry bit is 1, if not the carry bit is 0. If both are equal the zero bit is set to 1.

uint8_t CPU::CMP()
{
	Fetch();

	uint16_t comparison = (uint16_t)a - (uint16_t)fetched;

	SetFlag(C, a >= fetched);
	SetFlag(Z, (comparison & 0x00FF) == 0x0000);
	SetFlag(N, (comparison & 0x0080));

	return 1;
}

uint8_t CPU::CPX()
{
	Fetch();

	uint16_t comparison = (uint16_t)x - (uint16_t)fetched;

	SetFlag(C, x >= fetched);
	SetFlag(Z, (comparison & 0x00FF) == 0x0000);
	SetFlag(N, (comparison & 0x0080));

	return 0;
}

uint8_t CPU::CPY()
{
	Fetch();

	uint16_t comparison = (uint16_t)y - (uint16_t)fetched;

	SetFlag(C, y >= fetched);
	SetFlag(Z, (comparison & 0x00FF) == 0x0000);
	SetFlag(N, (comparison & 0x0080));

	return 0;
}

//Decrements

uint8_t CPU::DEC()
{
	Fetch();
	uint16_t decrementedValue = fetched - 1;

	Write(addr_abs, decrementedValue & 0x00FF);

	SetFlag(Z, (decrementedValue & 0x00FF) == 0x0000);
	SetFlag(N, decrementedValue & 0x0080);

	return 0;
}

uint8_t CPU::DEX()
{
	x--;

	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);

	return 0;
}

uint8_t CPU::DEY()
{
	y--;

	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);

	return 0;
}

//XOR
uint8_t CPU::EOR()
{
	Fetch();
	a = a ^ fetched;

	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);

	return 1;
}

//Increments

uint8_t CPU::INC()
{
	Fetch();

	uint16_t incrementedValue = fetched + 1;
	Write(addr_abs, incrementedValue & 0x00FF);

	SetFlag(Z, (incrementedValue & 0x00FF) == 0x0000);
	SetFlag(N, incrementedValue & 0x0080);

	return 0;
}

uint8_t CPU::INX()
{
	x++;

	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);

	return 0;
}

uint8_t CPU::INY()
{
	y++;

	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);

	return 0;
}

//Jump to memory address
uint8_t CPU::JMP()
{
	pc = addr_abs;
	return 0;
}

//Jump to subroutine and store current CPU status. Basically a function call!
uint8_t CPU::JSR()
{
	pc--; //When returning from the subroutine the program counter is incremented again... are the decrement and increment nessessary? ***

	Write(0x0100 + sktp, (pc >> 8) & 0x00FF);
	sktp--;
	Write(0x0100 + sktp, pc & 0x00FF);
	sktp--;

	pc = addr_abs;
	return 0;
}

//Load Values into the CPU

uint8_t CPU::LDA()
{
	Fetch();

	a = fetched;

	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);

	return 1;
}

uint8_t CPU::LDX()
{
	Fetch();

	x = fetched;

	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);

	return 1;
}

uint8_t CPU::LDY()
{
	Fetch();

	y = fetched;

	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);

	return 1;
}

//Logical Shift Right
uint8_t CPU::LSR()
{
	Fetch();

	SetFlag(C, fetched & 0x0001); //This Setflag Should be able to go with the others ***

	uint16_t shift = fetched >> 1;

	SetFlag(Z, (shift & 0x00FF) == 0x0000);
	SetFlag(N, shift & 0x0080);

	if (lookup[opcode].addrmode == &CPU::IMP)
	{
		a = shift & 0x00FF;
	}
	else
	{
		Write(addr_abs, shift & 0x00FF);
	}

	return 0;
}

//No operation! some NES games and other programs still use these though.
uint8_t CPU::NOP()
{
	switch (opcode) 
	{
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}

//OR
uint8_t CPU::ORA()
{
	Fetch();

	a = a | fetched;

	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);

	return 1;
}

//Push and pops to and from the stack

uint8_t CPU::PHA()
{
	Write(0x0100 + sktp, a);
	sktp--;

	return 0;
}

uint8_t CPU::PHP()
{
	Write(0x0100 + sktp, status | B | U);

	SetFlag(B, 0);
	SetFlag(U, 0);

	sktp--;

	return 0;
}

uint8_t CPU::PLA()
{
	sktp++;
	a = Read(0x0100 + sktp);

	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);

	return 0;
}

uint8_t CPU::PLP()
{
	sktp++;
	status = Read(0x0100 + sktp);

	SetFlag(U, 1);

	return 0;
}

//Rotations

uint8_t CPU::ROL()
{
	Fetch();

	uint16_t rotation = (uint16_t)(fetched << 1) | GetFlag(C); //The flag is set AFTER the rotation is done... is this working correctly?? if this doesn't work correctly set the carry bit BEFORE the rotation is done. ***

	SetFlag(C, rotation & 0xFF00);
	SetFlag(Z, (rotation & 0x00FF) == 0x0000);
	SetFlag(N, rotation & 0x0080);

	if (lookup[opcode].addrmode == &CPU::IMP)
	{
		a = rotation & 0x00FF;
	}
	else
	{
		Write(addr_abs, rotation & 0x00FF);
	}

	return 0;
}

uint8_t CPU::ROR()
{
	Fetch();

	uint16_t rotation = (uint16_t)(GetFlag(C) << 7) | (fetched >> 1); //This seems much better to me since fetched is an 8 bit character here but still. if something's wrong set the carry bit FIRST ***

	SetFlag(C, fetched & 0x01);
	SetFlag(Z, (rotation & 0x00FF) == 0x0000);
	SetFlag(N, rotation & 0x0080);

	if (lookup[opcode].addrmode == &CPU::IMP)
	{
		a = rotation & 0x00FF;
	}
	else
	{
		Write(addr_abs, rotation & 0x00FF);
	}

	return 0;
}

//Return from inturupt
uint8_t CPU::RTI()
{
	sktp++;
	status = Read(0x0100 + sktp);
	status &= ~B;
	status &= ~U;

	sktp++;
	pc = (uint16_t)Read(0x0100 + sktp);
	sktp++;
	pc |= (uint16_t)Read(0x0100 + sktp) << 8;

	return 0;
}

//Return from subroutine
uint8_t CPU::RTS()
{
	sktp++;
	pc = (uint16_t)Read(0x0100 + sktp);
	sktp++;
	pc |= (uint16_t)Read(0x0100 + sktp) << 8;

	pc++; //See JSR ***

	return 0;
}

//Set flags

uint8_t CPU::SEC()
{
	SetFlag(C, true);
	return 0;
}

uint8_t CPU::SED()
{
	SetFlag(D, true);
	return 0;
}

uint8_t CPU::SEI()
{
	SetFlag(I, true);
	return 0;
}

//Store CPU values

uint8_t CPU::STA()
{
	Write(addr_abs, a);
	return 0;
}

uint8_t CPU::STX()
{
	Write(addr_abs, x);
	return 0;
}

uint8_t CPU::STY()
{
	Write(addr_abs, y);
	return 0;
}

//Value Transfers

uint8_t CPU::TAX()
{
	x = a;

	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);

	return 0;
}

uint8_t CPU::TAY()
{
	y = a;

	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);

	return 0;
}

uint8_t CPU::TSX()
{
	x = sktp;

	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);

	return 0;
}

uint8_t CPU::TXA()
{
	a = x;

	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);

	return 0;
}

uint8_t CPU::TXS()
{
	sktp = x;
	return 0;
}

uint8_t CPU::TYA()
{
	a = y;

	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);

	return 0;
}

//Illegal opcode catch
uint8_t CPU::XXX()
{
	return 0;
}