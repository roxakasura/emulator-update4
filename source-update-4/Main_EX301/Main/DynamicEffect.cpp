// CustomWingEffect.cpp: implementation of the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomWing.h"
#include "DynamicEffect.h"
#include "ItemManager.h"


CDynamicWingEffect gDynamicWingEffect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDynamicWingEffect::CDynamicWingEffect() // OK
{
	this->Init();
}

CDynamicWingEffect::~CDynamicWingEffect() // OK
{

}

void CDynamicWingEffect::Init() // OK
{
	this->count = 0;

	for(int n=0;n < MAX_DYNAMIC_WING_EFFECT;n++)
	{
		this->m_DynamicWingEffectInfo[n].Index = -1;
	}
}

void CDynamicWingEffect::Load(DYNAMIC_WING_EFFECT_INFO* info) // OK
{
	for(int n=0;n < MAX_DYNAMIC_WING_EFFECT;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CDynamicWingEffect::SetInfo(DYNAMIC_WING_EFFECT_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_DYNAMIC_WING_EFFECT)
	{
		return;
	}

	this->m_DynamicWingEffectInfo[info.Index] = info;
	this->count++;
}

BOOL CDynamicWingEffect::DynamicWingEffect(int ItemIndex,DWORD a,DWORD b,DWORD c) // OK
{
	for(int n=0;n < this->count;n++)
	{
		
		if ((this->m_DynamicWingEffectInfo[n].ItemIndex == ITEM_BASE_MODEL) == ItemIndex)
		{
			return 0;
		}

		if (this->m_DynamicWingEffectInfo[n].Index == -1)
		{
			return 0;
		}

		if(this->m_DynamicWingEffectInfo[n].ItemIndex == ItemIndex)
		{
			float ItemColor[3];

			ItemColor[0] = this->m_DynamicWingEffectInfo[n].ColorR;

			ItemColor[1] = this->m_DynamicWingEffectInfo[n].ColorG;

			ItemColor[2] = this->m_DynamicWingEffectInfo[n].ColorB;
		}
	}
	return 0;
}