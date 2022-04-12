// CustomWingEffect.cpp: implementation of the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "CustomWing.h"
#include "ItemManager.h"

CCustomWingEffect gCustomWingEffect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomWingEffect::CCustomWingEffect() // OK
{
	this->Init();
}

CCustomWingEffect::~CCustomWingEffect() // OK
{

}

void CCustomWingEffect::Init() // OK
{
	this->count = 0;

	for(int n=0;n < MAX_CUSTOM_WING_EFFECT;n++)
	{
		this->m_CustomWingEffectInfo[n].Index = -1;
	}
}

void CCustomWingEffect::Load(CUSTOM_WING_EFFECT_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_WING_EFFECT;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomWingEffect::SetInfo(CUSTOM_WING_EFFECT_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_WING_EFFECT)
	{
		return;
	}

	this->m_CustomWingEffectInfo[info.Index] = info;
	this->count++;
}
