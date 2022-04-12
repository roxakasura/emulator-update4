#include "StdAfx.h"

void HookJump(DWORD Offset, LPVOID Function)
{
    *(BYTE*)(Offset) = 0xE9;
    *(DWORD*)(Offset + 1) = *(DWORD*)Function - (Offset + 5);
}

bool cSmoke::Load()
{
	this->_Count = 0;

	memset(this->SmokeStruct, 0, sizeof(this->SmokeStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Smoke.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->SmokeStruct[this->_Count]._Index = Section.Rows[i].GetInt(0);
			this->SmokeStruct[this->_Count]._ColorR = Section.Rows[i].GetFloat(1);
			this->SmokeStruct[this->_Count]._ColorG = Section.Rows[i].GetFloat(2);
			this->SmokeStruct[this->_Count]._ColorB = Section.Rows[i].GetFloat(3);
			this->_Count++;
		}
	}

	//SetNop(0x506AB1, 7);
	HookJump(0x506AB1, this->Effect);

	return true;
}

int cSmoke::Get(DWORD Type)
{
	for (int i = 0; i < this->_Count; i++)
	{
		if (Type == ITEM_ID(11, this->SmokeStruct[i]._Index))
		{
			return i;
		}
	}

	return -1;
}

__declspec(naked) void cSmoke::Effect()
{
	static DWORD Offset1 = 0x506AB8;
	static DWORD Offset2 = 0x50761D;
	static DWORD Offset3 = 0x506BAE;

	_asm
	{
		MOV AX, WORD PTR DS : [EAX + 0x288]
		MOV Smoke._Index, AX
	}

	if ((Smoke._Item = Smoke.Get(Smoke._Index)) > -1)
	{
		Smoke._ColorR = Smoke.SmokeStruct[Smoke._Item]._ColorR;
		Smoke._ColorG = Smoke.SmokeStruct[Smoke._Item]._ColorG;
		Smoke._ColorB = Smoke.SmokeStruct[Smoke._Item]._ColorB;

		_asm
		{
			CMP DWORD PTR DS : [0x7424650], 0x9
			JLE NOT_ALLOW01
			MOV ECX, DWORD PTR DS : [EBX + 0xF0]
			MOV EDX, DWORD PTR DS : [EBX + 0xF4]
			LEA EDI, DWORD PTR DS : [EBX + 0xF0]
			MOV DWORD PTR SS : [EBP - 0x44], ECX
			MOV ECX, DWORD PTR DS : [EBX + 0xF8]
			MOV DWORD PTR SS : [EBP - 0x40], EDX
			MOV DWORD PTR SS : [EBP - 0x3C], ECX

			MOV ECX, Smoke._ColorR
			MOV DWORD PTR DS : [EDI], ECX

			MOV EDX, Smoke._ColorG
			MOV DWORD PTR DS : [EBX + 0xF4], EDX

			MOV ECX, Smoke._ColorB
			MOV DWORD PTR DS : [EBX + 0xF8], ECX

			JMP[Offset3]
		}

		_asm
		{
		    NOT_ALLOW01:
			JMP[Offset2]
		}
	}
	else
	{
		_asm
		{
			JMP[Offset1]
		}
	}
}

cSmoke Smoke;