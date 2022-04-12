// CustomWingEffect.h: interface for the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

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
	void Load(DYNAMIC_WING_EFFECT_INFO* info);
	void SetInfo(DYNAMIC_WING_EFFECT_INFO info);
	BOOL DynamicWingEffect(int ItemIndex,DWORD a,DWORD b,DWORD c);
public:
	DYNAMIC_WING_EFFECT_INFO m_DynamicWingEffectInfo[MAX_DYNAMIC_WING_EFFECT];
	int count;
};

extern CDynamicWingEffect gDynamicWingEffect;
