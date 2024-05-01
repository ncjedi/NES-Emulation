    #include "Mapper0.h"

Mapper0::Mapper0()
{
}

Mapper0::~Mapper0()
{
}

bool Mapper0::CPUMapRead(uint16_t address, uint32_t& mappedAddress)
{
    if (address >= 0x8000 && address <= 0xFFFF)
    {
        mappedAddress = address & (mainPRGBanks > 1 ? 0x7FFF : 0x3FFF);
        return true;
    }

    return false;
}

bool Mapper0::CPUMapWrite(uint16_t address, uint32_t& mappedAddress)
{
    if (address >= 0x8000 && address <= 0xFFFF)
    {
        mappedAddress = address & (mainPRGBanks > 1 ? 0x7FFF : 0x3FFF);
        return true;
    }

    return false;
}

bool Mapper0::PPUMapRead(uint16_t address, uint32_t& mappedAddress)
{
    if (address >= 0x8000 && address <= 0x1FFF)
    {
        mappedAddress = address;
        return true;
    }

    return false;
}

bool Mapper0::PPUMapWrite(uint16_t address, uint32_t& mappedAddress)
{
    return false;
}
