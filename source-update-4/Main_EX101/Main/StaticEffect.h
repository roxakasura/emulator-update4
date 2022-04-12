// CustomWingEffect.h: interface for the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

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
	void Load(CUSTOM_WING_EFFECT_INFO* info);
public:
	std::vector<CUSTOM_WING_EFFECT_INFO> m_CustomWingEffectInfo;
};

extern CCustomWingEffect gCustomWingEffect;
