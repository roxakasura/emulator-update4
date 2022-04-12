#include "StdAfx.h"

int *Map = (int*)0x6B8D48; // Ok
int LastMap = 100;
bool IsMiniMap = false;

char CurrentDir1[MAX_PATH];

#define pUnblend	((int(__cdecl*)()) 0x0060CC20) 
#define pLoadImg	((int(__cdecl*)(PCHAR a1, int a2, GLint param, GLint a4, int a5, char a6)) 0x0062C1E0) 
#define pMiniMap	((void(__cdecl*)()) 0x0060CB10) 

void MiniMap()
{
	char path[MAX_PATH];
	char mypath[MAX_PATH];

	if (LastMap != *Map)
	{
		sprintf_s(path, "Minimap\\World%d\\map%d.jpg", *Map + 1,*Map + 1);
		sprintf_s(mypath, "%sData\\Minimap\\World%d\\map%d.OZJ", CurrentDir1, *Map + 1, *Map + 1);

		if (CreateFile(mypath, 0, 0, 0, OPEN_EXISTING, 0, 0) != INVALID_HANDLE_VALUE)
		{
			pLoadImg(path, 1684, 9729, 10496, 0, 1);
			IsMiniMap = true;
		}
		else
		{
			IsMiniMap = false;
			LastMap = *Map;
		}
	}

	if (IsMiniMap)
	{
		*(BYTE*)0x004105F6 = 0xEB;
	}
	else
	{
		*(BYTE*)0x004105F6 = 0x74;
	}

	pUnblend();
}

void ReadyMiniMap()
{
	gToolKit.SetOp((LPVOID)0x00598FB9, (LPVOID)MiniMap, 0xE8);
}