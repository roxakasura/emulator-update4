#pragma once

#define RenderBoolean                                    ((void(__cdecl*)(int a1, int a2, char *a3)) 0x53F870) //1.02s: 005A21B0 //
#define CreateGuildMark                                    ((void(__cdecl*)(int a1, bool a2)) 0x005FA170) //1.02s: 006639D0 //
#define RenderBitmap                                    ((void(__cdecl*)(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)) 0x006438B4) //1.02s: 006B97A7 //

#define sub_4BBDC0				((int(__thiscall*)(void *This)) 0x004BBDC0)

void PlayerGuildLogo(int a1, int a2, char* a3);
void PlayerLoad();

extern int valor;