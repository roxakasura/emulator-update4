#include "StdAfx.h"
#include "Util.h"
#include "Font.h"

CFont gFont;

void CFont::Load()
{
	int FontActive = GetPrivateProfileIntA("Main", "IsFontActive", 0, MAIN_FILE);

	if (FontActive == 1)
	{
		SetCompleteHook(0xE8, Offset_CreateFontA1, &CFont::LoadFont);
		SetCompleteHook(0xE8, Offset_CreateFontA2, &CFont::LoadFont);
		SetCompleteHook(0xE8, Offset_CreateFontA3, &CFont::LoadFont);
		SetCompleteHook(0xE8, Offset_CreateFontA4, &CFont::LoadFont);
		SetCompleteHook(0xE8, Offset_CreateFontA5, &CFont::LoadFont);
		//--
		SetByte((Offset_CreateFontA1 + 5), 0x90);
		SetByte((Offset_CreateFontA2 + 5), 0x90);
		SetByte((Offset_CreateFontA3 + 5), 0x90);
		SetByte((Offset_CreateFontA4 + 5), 0x90);
		SetByte((Offset_CreateFontA5 + 5), 0x90);
	}
}

HFONT CFont::LoadFont()
{
	HFONT hFont;
	// ---
	int Bold		= GetPrivateProfileIntA("Main", "IsFontBold", 0, MAIN_FILE);
	int Height		= GetPrivateProfileIntA("Main", "IsFontHeight", 10, MAIN_FILE);
	int Unicode		= GetPrivateProfileIntA("Main", "IsFontUnicode", 1, MAIN_FILE);
	// ---
	GetPrivateProfileStringA("Main", "IsFontName", "Tahoma", gFont.szFontName, 100, MAIN_FILE);
	// ---
	if (Bold == 0)
	{
		if (Unicode == 1)
		{
			hFont = CreateFontA(Height, 0, 0, 0, 400, 0, 0, 0, 0x01, 0, 0, 3, 0, gFont.szFontName);
		}
		else
		{
			hFont = CreateFontA(Height, 0, 0, 0, 400, 0, 0, 0, 0x0, 0, 0, 3, 0, gFont.szFontName);
		}
	}
	else
	{
		if (Unicode == 1)
		{
			hFont = CreateFontA(Height, 0, 0, 0, 700, 0, 0, 0, 0x01, 0, 0, 3, 0, gFont.szFontName);
		}
		else
		{
			hFont = CreateFontA(Height, 0, 0, 0, 700, 0, 0, 0, 0x0, 0, 0, 3, 0, gFont.szFontName);
		}
	}
	// ---
	return hFont;
}