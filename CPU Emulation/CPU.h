#pragma once
#include <string>
#include <vector>

class Bus;

class CPU
{
public:
	CPU();
	~CPU();

	void ConnectBus(Bus* connection);

	//sets each flag bit
	enum Flags
	{
		C = (1 << 0), //Carry bit
		Z = (1 << 1), //Zero bit
		I = (1 << 2), //Disable inturrupts bit
		D = (1 << 3), //Decimal Mode bit
		B = (1 << 4), //Break bit
		U = (1 << 5), //Unused bit :(
		V = (1 << 6), //Overflow bit
		N = (1 << 7) //Negitive bit
	};

	uint8_t a = 0x00; //accumulator
	uint8_t x = 0x00; //x register
	uint8_t y = 0x00; //y register
	uint8_t sktp = 0x00; //stack pointer
	uint16_t pc = 0x0000; //program counter
	uint8_t status = 0x00; //status register

	//Input signals into the CPU
	void Clock();
	void Reset();
	void IRQ();
	void NMI();

	uint16_t GetAddrAbs() //Test Function
	{
		return addr_abs;
	}

	uint16_t GetAddrRel() //Test Function
	{
		return addr_rel;
	}

private:
	Bus *bus = nullptr;

	uint8_t Read(uint16_t address);
	void Write(uint16_t address, uint8_t data);

	uint8_t GetFlag(Flags f);
	void SetFlag(Flags f, bool v);

	//Addressing modes
	uint8_t IMP();	uint8_t IMM();
	uint8_t ZP0();	uint8_t ZPX();
	uint8_t ZPY();	uint8_t REL();
	uint8_t ABS();	uint8_t ABX();
	uint8_t ABY();	uint8_t IND();
	uint8_t IZX();	uint8_t IZY();

	//Instructions
	uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
	uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
	uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
	uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
	uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
	uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
	uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
	uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
	uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
	uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
	uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
	uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
	uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

	uint8_t XXX(); //For unoffical opcodes

	struct INSTRUCTION
	{
		std::string name;
		uint8_t(CPU::* operate)(void) = nullptr; //pointer to the opcode function of the instruction
		uint8_t(CPU::* addrmode)(void) = nullptr; //pointer to the addressing mode function of the instruction
		uint8_t cycles = 0; //number of cycles the instruction will take to execute
	};

	std::vector<INSTRUCTION> lookup;

	//Internal CPU stuff
	//Fetching data
	uint8_t Fetch();
	uint8_t fetched = 0x00;

	//Addressing
	uint16_t addr_abs = 0x0000;
	uint8_t addr_rel = 0x00;

	//Current opcode
	uint8_t opcode = 0x00;

	//Number of cycles the current instruction will take
	uint8_t cycles = 0x00;
};

