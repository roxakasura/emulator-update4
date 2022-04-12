#pragma once

#define RenderBoolean									((void(__cdecl*)(int a1, int a2, char *a3)) 0x00549F50) //1.01t
#define CreateGuildMark									((void(__cdecl*)(int a1, bool a2)) 0x005DFDF0) //1.01t
#define RenderBitmap									((void(__cdecl*)(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)) 0x60DCF0) //1.1t
#define pDrawGUI						((void(__cdecl*)(int ObjectId, float X, float Y, float Width, float Height, int Arg6, int Arg7, float Width2, float Height2, char Arg10, float Arg11)) 0x0060DCF0)

void PlayerGuildLogo(int a1, int a2, char *a3);
void PlayerLoad();

extern int valor;