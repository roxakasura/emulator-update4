#pragma once

#define MAX_CHARACTER 5

#define pGetPreviewStruct	((DWORD(__thiscall*)(LPVOID This, int ViewportID)) 0x74D2B28) //1.04j
#define pPreviewThis		((LPVOID(*)()) 0x0040294F) //1.04j


#define SelectedHero		*(int*)0x77ECE0 //1.04j
#define SelectedCharacter	*(int*)0x76EFA4 //1.04j

#define ShowWin										((int(__thiscall*)(int a1,int a2)) 0x00463D90)
#define Instance									((int(*)()) 0x00463272)
#define MouseX										*(int*)0x7AFE950
#define MouseY										*(int*)0x7AFE94C
#define PressKey									((char(__cdecl*)(int vKey)) 0x0053D8E0)
#define SelectedHero								*(int*)0x77ECE0
#define SelectedCharacter							*(int*)0x76EFA4
#define sub_463272									((int(*)()) 0x00463272)
#define sub_532400									((int(__cdecl*)(char a1)) 0x00532400)
#define pTextThis									((LPVOID(*)()) 0x0041FD65)
#define pSetTextColor								((void(__thiscall*)(LPVOID This, BYTE r, BYTE g, BYTE b, BYTE h)) 0x0041FF35)
#define pDrawText									((int(__thiscall*)(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)) 0x00420024)
#define CUIRenderText_SetFont						((int(__thiscall*)(LPVOID This, HGDIOBJ a2)) 0x0041FFF9)
#define g_hFontBold									*(HGDIOBJ*)0x7AFEE98
#define RenderBitmap								((void(__cdecl*)(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)) 0x006438B4)
#define BeginBitmap									((void(*)()) 0x643691)
#define DisableAlphaBlend							((void(__cdecl*)()) 0x00642209)
#define EnableAlphaBlend							((void(__cdecl*)()) 0x00642323)
#define PlayBuffer									((signed int (__cdecl*)(int a1, int a2, int a3)) 0x006A4FB5)

void CButtonCharacterS13();