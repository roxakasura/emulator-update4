
// CustomWingEffect.h: interface for the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_WING_EFFECT 3000

struct CUSTOM_WING_EFFECT_INFO
{
	int Index;
	int ItemIndex;
	int EffectIndex;
	float EffectSize;
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
	void Load(char* path);
	void SetInfo(CUSTOM_WING_EFFECT_INFO info);
public:
	CUSTOM_WING_EFFECT_INFO m_CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
};

extern CCustomWingEffect gCustomWingEffect;