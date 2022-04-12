#pragma once

#define pDrawToolTip	((void(__cdecl*)(int a1, int a2, LPCSTR lpString))0x005487E0) //1.01t ok
#define pDrawBarForm			((void(__cdecl*)(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)) 0x0060DC30)

#define sub_404A60      ((unsigned int(__thiscall*)(DWORD *This, int a2))0x404A60);

void ExperienceLoad();

class CAddons
{
public:
	void Load();
	static void ExperienceSettings();
	DWORD gLevelExperience[1001];
};

extern CAddons gAddons;