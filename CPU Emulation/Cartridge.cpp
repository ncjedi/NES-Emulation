#include "Cartridge.h"

Cartridge::Cartridge(const std::string& fileName)
{
    //iNES header
    struct Header
    {
        char name[4];
        uint8_t prgRomChunks;
        uint8_t chrRomChunks;
        uint8_t mapper1;
        uint8_t mapper2;
        uint8_t prgRamSize;
        uint8_t tvSystem1;
        uint8_t tvSystem2;
        char unused[5];
    } header;

    std::ifstream stream;
    stream.open(fileName, std::ifstream::binary);

    if (stream.is_open())
    {
        //Read in file header
        stream.read((char*)&header, sizeof(Header));

        if (header.mapper1 & 0x04)
        {
            stream.seekg(512, std::ios_base::cur);
        }

        //Determine mapper ID
        mapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4); //TODO: figure out what this means

        //Figure out file format
        uint8_t fileType = 1;

        if (fileType == 0)
        {

        }

        if (fileType == 1)
        {
            nPRGBanks = header.prgRomChunks;
            vPRGMemory.resize(nPRGBanks * 16384);
            stream.read((char*)vPRGMemory.data(), vPRGMemory.size());

            nCHRBanks = header.chrRomChunks;
            vCHRMemory.resize(nCHRBanks * 8192);
            stream.read((char*)vCHRMemory.data(), vCHRMemory.size());
        }

        if (fileType == 2)
        {

        }

        switch (mapperID)
        {
        case 0:
            mainMapper = std::make_shared<Mapper0>(nPRGBanks, nCHRBanks);
            break;
        }

        stream.close();
    }
}

Cartridge::~Cartridge()
{
}

bool Cartridge::CPURead(uint16_t address, uint8_t& data)
{
    uint32_t mappedAddress = 0;

    if (mainMapper->CPUMapRead(address, mappedAddress))
    {
        data = vPRGMemory[mappedAddress];
        return true;
    }

    else //Another case of a seemingly useless else...***
    {
        return false;
    }
}

bool Cartridge::CPUWrite(uint16_t address, uint8_t data)
{
    uint32_t mappedAddress = 0;

    if (mainMapper->CPUMapRead(address, mappedAddress))
    {
        data = vPRGMemory[mappedAddress];
        return true;
    }

    else //Another case of a seemingly useless else...***
    {
        return false;
    }
}

bool Cartridge::PPURead(uint16_t address, uint8_t& data)
{
    uint32_t mappedAddress = 0;

    if (mainMapper->CPUMapRead(address, mappedAddress))
    {
        data = vCHRMemory[mappedAddress];
        return true;
    }

    else //Another case of a seemingly useless else...***
    {
        return false;
    }
}

bool Cartridge::PPUWrite(uint16_t address, uint8_t data)
{
    uint32_t mappedAddress = 0;

    if (mainMapper->CPUMapRead(address, mappedAddress))
    {
        data = vCHRMemory[mappedAddress];
        return true;
    }

    else //Another case of a seemingly useless else...***
    {
        return false;
    }
}
