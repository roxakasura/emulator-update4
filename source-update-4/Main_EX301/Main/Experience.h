#pragma once

#define pDrawToolTip	((void(__cdecl*)(int a1, int a2, LPCSTR lpString))0x0053DEB0) //1.04j ok

#define sub_404A60      ((unsigned int(__thiscall*)(DWORD *This, int a2))0x404A60);

void ExperienceLoad();

class CAddons
{
public:
	void Load();
	static void ExperienceSettings();
	DWORD gLevelExperience[401];
};

extern CAddons gAddons;