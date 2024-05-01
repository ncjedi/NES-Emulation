#include "Mapper.h"

Mapper::Mapper(uint8_t PRGBanks, uint8_t CHRBanks)
{
	mainPRGBanks = PRGBanks;
	mainCHRBanks = CHRBanks;
}

Mapper::~Mapper()
{

}