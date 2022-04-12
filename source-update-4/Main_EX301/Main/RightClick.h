#pragma once

#define CheckWindows			((bool(__stdcall*)(int a1)) 0x0045E06F)
#define pCheckWindow			((bool(__stdcall*)(int Code)) 0x0045E06F)
#define pOpenWindow             ((bool(__stdcall*)(int Code, int a2)) 0x45E696)
void RightClick();