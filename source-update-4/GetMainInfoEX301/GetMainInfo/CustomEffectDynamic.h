// CustomWingEffect.h: interface for the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_DYNAMIC_WING_EFFECT 3000

struct DYNAMIC_WING_EFFECT_INFO
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

class CDynamicWingEffect
{
public:
	CDynamicWingEffect();
	virtual ~CDynamicWingEffect();
	void Init();
	void Load(char* path);
	void SetInfo(DYNAMIC_WING_EFFECT_INFO info);
public:
	DYNAMIC_WING_EFFECT_INFO m_DynamicWingEffectInfo[MAX_DYNAMIC_WING_EFFECT];
};

extern CDynamicWingEffect gDynamicWingEffect;
