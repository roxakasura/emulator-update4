#pragma once

#define SceneFlag *(int*)0x00708760

#define FontHeight *(int*)0x077DDFF8

#define g_bUseWindowMode *(bool*)0x006F92FC

#define m_Resolution *(int*)0x05792568

#define WindowWidth *(int*)0x007086F8

#define WindowHeight *(int*)0x007086FC

#define g_fScreenRate_x *(float*)0x057920D8

#define g_fScreenRate_y *(float*)0x057920DC

#define g_hWnd *(HWND*)0x05792778

#define g_hDC *(HDC*)0x05792780

#define g_hRC *(HGLRC*)0x05792784

#define WndProc (WNDPROC)(0x4C7B40)

#define pDrawMessage ((int(__cdecl*)(LPCSTR Text, int Mode)) 0x0057AC00)