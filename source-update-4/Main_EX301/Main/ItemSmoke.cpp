#include "stdafx.h"
#include "ItemSmoke.h"
#include "ItemManager.h"
#include "ToolKit.h"
#include "Util.h"

DWORD pItemType = 0;
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

__declspec(naked) void SetItemEffect()
{
	_asm
	{
		Mov pItemType, ECX
	}

	Item = gSmokeEffect.GetItemID(pItemType);

	if(Item != -1)
	{
		_asm
		{
			MOV ESI, HDK_ITEM_EFFECT_ALLOW
			JMP ESI
		}
	}

	_asm
	{
		MOV ESI, HDK_ITEM_EFFECT_NOT_ALLOW 
		JMP ESI
	}
}

__declspec(naked) void SetColorEffect()
{
	_asm
	{
		Mov pItemType, EDX
	}

	Item = gSmokeEffect.GetItemID(pItemType);
	
	R = gSmokeEffect.GetRedColor(pItemType);
	G = gSmokeEffect.GetGreenColor(pItemType);
	B = gSmokeEffect.GetBlueColor(pItemType);

	if(pItemType == GET_ITEM_MODEL(11, 29))
	{
		_asm
		{
			// R
			MOV EDX,DWORD PTR SS:[EBP+0xC] // struct RGB
			MOV DWORD PTR DS:[EDX+0x128],0x3F266666 // float =D
			// G
			MOV EAX,DWORD PTR SS:[EBP+0xC]  // struct RGB
			MOV DWORD PTR DS:[EAX+0x12C],0x3E99999A// float =D
			// B
			MOV ECX,DWORD PTR SS:[EBP+0xC]  // struct RGB
			MOV DWORD PTR DS:[ECX+0x130],0x3DCCCCCD
		}
	}

	if(pItemType == Item)
	{
		_asm
		{
			// R
			MOV EDX,DWORD PTR SS:[EBP+0xC] // struct RGB
			MOV EAX, R
			MOV DWORD PTR DS:[EDX+0x128],EAX // float =D
			// G
			MOV EAX,DWORD PTR SS:[EBP+0xC]  // struct RGB
			MOV ECX, G
			MOV DWORD PTR DS:[EAX+0x12C],ECX // float =D
			// B
			MOV ECX,DWORD PTR SS:[EBP+0xC]  // struct RGB
			MOV EDX, B
			MOV DWORD PTR DS:[ECX+0x130],EDX
			MOV ESI, 0x005289CC
			JMP ESI
		}
	}

	_asm
	{
		MOV ESI, HDK_NEXT_ITEM_COLOR
		JMP ESI
	}
}

void cSmokeEffect::SetLoad()
{		
	MemorySet(HDK_SET_ITEM_EFFECT,0x90,12);							//1.04j
	ToolKit.WriteJmp(HDK_SET_ITEM_EFFECT, (DWORD)&SetItemEffect);	//1.04j

	MemorySet(HDK_SET_COLOR_EFFECT,0x90,46);						//1.04j
	ToolKit.WriteJmp(HDK_SET_COLOR_EFFECT, (DWORD)&SetColorEffect);	//1.04j
}
