// CustomWingEffect.cpp: implementation of the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

CCustomWingEffect gCustomWingEffect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomWingEffect::CCustomWingEffect()
{
	this->m_CustomWingEffectInfo.clear();
}

CCustomWingEffect::~CCustomWingEffect()
{

}

void CCustomWingEffect::Load(CUSTOM_WING_EFFECT_INFO* info)
{
	for(int n=0;n < MAX_DYNAMIC_WING_EFFECT;n++)
	{
		if(info[n].Index < 0 || info[n].Index >= MAX_DYNAMIC_WING_EFFECT)
		{
			return;
		}

		this->m_CustomWingEffectInfo.push_back(info[n]);
	}
}