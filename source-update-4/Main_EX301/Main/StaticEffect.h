// CustomWingEffect.h: interface for the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"

struct CUSTOM_WING_EFFECT_INFO
{
	int Index;
	int ItemIndex;
	int EffectIndex;
	int EffectSize;
	int EffectBone;
	float ColorR;
	float ColorG;
	float ColorB;
};

class CCustomWingEffect
{
public:
	CCustomWingEffect();
	virtual ~CCustomWingEffect();
	void Init();
	void Load(CUSTOM_WING_EFFECT_INFO* info);
	void SetInfo(CUSTOM_WING_EFFECT_INFO info);
public:
	CUSTOM_WING_EFFECT_INFO m_CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
	int count;
};

extern CCustomWingEffect gCustomWingEffect;
