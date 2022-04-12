#pragma once

struct DYNAMIC_WING_EFFECT_INFO
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

class CDynamicWingEffect
{
public:
	CDynamicWingEffect();
	virtual ~CDynamicWingEffect();
	void Load(DYNAMIC_WING_EFFECT_INFO* info);
public:
	 //std::map<int,DYNAMIC_WING_EFFECT_INFO> m_DynamicWingEffectInfo;
	std::vector<DYNAMIC_WING_EFFECT_INFO> m_DynamicWingEffectInfo;
};

extern CDynamicWingEffect gDynamicWingEffect;
