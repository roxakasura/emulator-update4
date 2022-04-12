#pragma once

#define	MAIN_FILE ".\\Config.ini"
#define Offset_CreateFontA1 0x0062F7D0
#define Offset_CreateFontA2 0x004B4E0E
#define Offset_CreateFontA3	0x004B4E4E
#define Offset_CreateFontA4 0x004B4E90

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