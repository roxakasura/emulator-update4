#pragma once

#define	MAIN_FILE ".\\Config.ini"
#define Offset_CreateFontA1 0x00405c7d
#define Offset_CreateFontA2 0x0064964d
#define Offset_CreateFontA3 0x006496b4
#define Offset_CreateFontA4 0x0064971c
#define Offset_CreateFontA5 0x00649786

class CFont
{
public:
	void Load();
	// ---
	static HFONT LoadFont();
	// ---
	char szFontName[100];
}; 

extern CFont gFont;