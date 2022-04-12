#include "stdafx.h"

WORD pItemType;
DWORD Item = 0;
float R = 0.0f;
float G = 0.0f;
float B = 0.0f;

cSmokeEffect gSmokeEffect;

cSmokeEffect::cSmokeEffect()
{
	this->Init();
}

cSmokeEffect::~cSmokeEffect()
{
	
}

void cSmokeEffect::Init()
{
	for (int i=0; i<MAX_SMOKE_ITEMS; i++)
	{
		this->m_CustomSmokeEffect[i].Index = -1;
	}
}

void cSmokeEffect::Load(CUSTOM_SMOKEEFFECT* info)
{
	for (int i=0; i<MAX_SMOKE_ITEMS; i++)
	{
		this->SetInfo(info[i]);
	}
}

void cSmokeEffect::SetInfo(CUSTOM_SMOKEEFFECT info)
{
	if(info.Index < 0 || info.Index >= MAX_SMOKE_ITEMS)
	{
		return;
	}
	this->m_CustomSmokeEffect[info.Index] = info;
}

CUSTOM_SMOKEEFFECT* cSmokeEffect::GetEffect(int ItemID)
{
	for(int n=0;n < MAX_SMOKE_ITEMS;n++)
	{
		CUSTOM_SMOKEEFFECT* lpInfo = this->GetEffectByIndex(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(GET_ITEM_MODEL(11, lpInfo->ItemIndex) == ItemID)
		{
			return lpInfo;
		}
	}

	return 0;
}

CUSTOM_SMOKEEFFECT* cSmokeEffect::GetEffectByIndex(int index)
{
	if(index < 0 || index >= MAX_SMOKE_ITEMS)
	{
		return 0;
	}

	if(this->m_CustomSmokeEffect[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomSmokeEffect[index];
}

int cSmokeEffect::GetItemID(int ItemID)
{
	for(int n=0;n < MAX_SMOKE_ITEMS;n++)
	{
		CUSTOM_SMOKEEFFECT* lpInfo = this->GetEffectByIndex(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(GET_ITEM_MODEL(11, lpInfo->ItemIndex) == ItemID)
		{
			return GET_ITEM_MODEL(11, lpInfo->ItemIndex);
		}
	}

	return -1;
}

float cSmokeEffect::GetRedColor(int ItemID)
{
	for(int n=0;n < MAX_SMOKE_ITEMS;n++)
	{
		CUSTOM_SMOKEEFFECT* lpInfo = this->GetEffectByIndex(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(GET_ITEM_MODEL(11, lpInfo->ItemIndex) == ItemID)
		{
			return lpInfo->Red;
		}
	}

	return -1;
}

float cSmokeEffect::GetGreenColor(int ItemID)
{
	for(int n=0;n < MAX_SMOKE_ITEMS;n++)
	{
		CUSTOM_SMOKEEFFECT* lpInfo = this->GetEffectByIndex(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(GET_ITEM_MODEL(11, lpInfo->ItemIndex) == ItemID)
		{
			return lpInfo->Green;
		}
	}

	return -1;
}

float cSmokeEffect::GetBlueColor(int ItemID)
{
	for(int n=0;n < MAX_SMOKE_ITEMS;n++)
	{
		CUSTOM_SMOKEEFFECT* lpInfo = this->GetEffectByIndex(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(GET_ITEM_MODEL(11, lpInfo->ItemIndex) == ItemID)
		{
			return lpInfo->Blue;
		}
	}

	return -1;
}


__declspec(naked) void SetColorEffect()
{
	static DWORD Offset1 = 0x506AB8;
	static DWORD Offset2 = 0x50761D;
	static DWORD Offset3 = 0x506BAE;

	_asm
	{
		MOV AX, WORD PTR DS : [EAX + 0x288]
		MOV pItemType, AX
	}
	
	Item = gSmokeEffect.GetItemID(pItemType);

	if(pItemType == Item)
	{
		R = gSmokeEffect.GetRedColor(pItemType);
		G = gSmokeEffect.GetGreenColor(pItemType);
		B = gSmokeEffect.GetBlueColor(pItemType);

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

			MOV ECX, R
			MOV DWORD PTR DS : [EDI], ECX

			MOV EDX, G
			MOV DWORD PTR DS : [EBX + 0xF4], EDX

			MOV ECX, B
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

void cSmokeEffect::SetLoad()
{
	SetCompleteHook(0xE9,0x506AB1, &SetColorEffect);	//1.01t
}
