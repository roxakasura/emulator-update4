#pragma once

#define MAX_SMOKE_ITEMS 500
#define oDrawItemEffectCall1				0x004902C5
#define oDrawItemEffectCall2				0x00507A41
#define oDrawItemEffectCall3				0x00625F8C

#define pDrawItemEffect						((void(__cdecl*)(DWORD ItemStruct,DWORD EffectStruct,DWORD a3)) 0x005026F0)


struct CUSTOM_SMOKEEFFECT
{
	int Index;
	int ItemIndex;
	float Red;
	float Green;
	float Blue;
};

class cSmokeEffect
{
public:
	cSmokeEffect();
	virtual ~cSmokeEffect();
	void Init();
	void Load(CUSTOM_SMOKEEFFECT* info);
	void SetInfo(CUSTOM_SMOKEEFFECT info);
	CUSTOM_SMOKEEFFECT* GetEffect(int ItemID);
	CUSTOM_SMOKEEFFECT* GetEffectByIndex(int Index);
	int GetItemID(int ItemID);
	float GetRedColor(int ItemID);
	float GetGreenColor(int ItemID);
	float GetBlueColor(int ItemID);
	void SetLoad();
	static void DrawItemEffect(DWORD ItemStruct,DWORD EffectStruct,DWORD a3);
public:
	CUSTOM_SMOKEEFFECT m_CustomSmokeEffect[MAX_SMOKE_ITEMS];
}; extern cSmokeEffect gSmokeEffect;