#include "StdAfx.h"
#include "Util.h"

char CurrentDir1[MAX_PATH];
char configname[MAX_PATH];
int  LastMap;
bool IsMiniMap;
bool ShowMiniMap;

typedef int(*TLoadImage)(char[64], int, int, int, int, int);
typedef int(*TUnBlend2) ();

BYTE *Main_MiniMapShow	= (BYTE*)0x0049C78D; //1.04j
int *Map				= (int*)0x0077038C; //1.04j
TUnBlend2 UnBlend2		= (TUnBlend2)0x00642209; //1.04j
TLoadImage LoadImg		= (TLoadImage)0x006F9D4F;


void MiniMap()
{
	char path[64];
	char mypath[MAX_PATH];
	LastMap = 100;

	if (LastMap != *Map)
	{
		sprintf_s(path, "Minimap\\World%d\\map1.jpg", *Map + 1);
		sprintf_s(mypath, "%sData\\Minimap\\World%d\\map1.ozj", CurrentDir1, *Map + 1);

		if (FileExists(mypath))
		{
			LoadImg(path, 1920, 0x2601, 0x2900, 0, 1);
			IsMiniMap = true;
		}
		else
		{
			IsMiniMap = false;
			LastMap = *Map;
		}
	}

	if (IsMiniMap == true)
	{
		*Main_MiniMapShow = 0x74;
	}
	else
	{
		*Main_MiniMapShow = 0xEB;
	}

	UnBlend2();
}

void HookMiniMap()
{
	SetCompleteHook(0xE8,0x0059F709,&MiniMap);
	IsMiniMap = false;
}