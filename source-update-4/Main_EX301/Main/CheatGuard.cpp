#include "stdafx.h"
#include "CheatGuard.h"
#include "TMemory.h"
#include "Protocol.h"
// ----------------------------------------------------------------------------------------------

CheatGuard gCheatGuard;
// ----------------------------------------------------------------------------------------------

void CheatGuard::Load()
{
	// ----
	ZeroMemory(this->XOR, sizeof(XOR));
	this->ChangeXORFilter();
	// ----
}
// ----------------------------------------------------------------------------------------------

void CheatGuard::ChangeXORFilter()
{

	this->XOR[0] = 0xE7;
	this->XOR[1] = 0x6D;
	this->XOR[2] = 0x3A;
	this->XOR[3] = 0x89;
	this->XOR[4] = 0xBC;
	this->XOR[5] = 0xB2;
	this->XOR[6] = 0x9F;
	this->XOR[7] = 0x73;
	this->XOR[8] = 0x23;
	this->XOR[9] = 0xA8;
	this->XOR[10] = 0xFE;
	this->XOR[11] = 0xB6;
	this->XOR[12] = 0x49;
	this->XOR[13] = 0x5D;
	this->XOR[14] = 0x39;
	this->XOR[15] = 0x5D;
	this->XOR[16] = 0x8A;
	this->XOR[17] = 0xCB;
	this->XOR[18] = 0x63;
	this->XOR[19] = 0x8D;
	this->XOR[20] = 0xEA;
	this->XOR[21] = 0x7D;
	this->XOR[22] = 0x2B;
	this->XOR[23] = 0x5F;
	this->XOR[24] = 0xC3;
	this->XOR[25] = 0xB1;
	this->XOR[26] = 0xE9;
	this->XOR[27] = 0x83;
	this->XOR[28] = 0x29;
	this->XOR[29] = 0x51;
	this->XOR[30] = 0xE8;
	this->XOR[31] = 0x56;
}
// ----------------------------------------------------------------------------------------------

bool CheatGuard::IsCorrectFrame()
{

}
// ----------------------------------------------------------------------------------------------

int CheatGuard::GetLargerFrame()
{

}
// ----------------------------------------------------------------------------------------------
