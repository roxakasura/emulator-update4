#pragma once

typedef unsigned __int64 QWORD;

#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT _WIN32_WINNT_WINXP

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <map>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>
#include <vector>
#include <rpc.h>
#include <rpcdce.h>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <tlhelp32.h>
#include <process.h>
#include <shellapi.h>
#include <WinSock.h>
#include "TMemory.h"
#include <fstream>
#include <string>
#include <Psapi.h>
#include <winternl.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include "glaux.h"
#include "..\Cg\cg.h"
#include "..\Cg\cgGL.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Detours.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glaux.lib")

#pragma comment(lib,"Psapi.lib")

#include "Detours.h"

#include "Protocol.h"
#include "main.h"
#include "TrayMode.h"

//Display

#define Naked(Function) void __declspec(naked) Function()

#define pGameWindow				*(HWND*)0x00647CC2  //ok

#define MAIN_FONT_SIZE 0x007513340
#define MAIN_RESOLUTION 0x007afec78
#define MAIN_RESOLUTION_X 0x0077e350
#define MAIN_RESOLUTION_Y 0x0077e354

#define pCreateSpriteE ((int(__cdecl*)(int Arg1, int Arg2, int Arg3, int Arg4, int Arg5, int Arg6, int Arg7))0x06EE878) //ok 
#define pCreateParticleEx ((int(__cdecl*)(int Arg1, int Arg2, int Arg3, int Arg4, int Arg5, float Arg6, int Arg7))0x006DA9C1) //ok 
#define pObjectGetAngle ((char(__cdecl*)(float Arg1, float Arg2, float Arg3))0x00608782) //ok 
#define pObjectMaxBug ((void(__cdecl*)(int Arg1, char Arg2, int Arg3, int Arg4))0x00612ECB) //ok 
#define sub_007396FD ((int(*)())0x007396FD) //ok 

#define pMainState						*(int*)0x0077EBAC		// -> Main States

#define pPlayerState			*(int*)0x0077EBAC
#define pMapNumber				*(int*)0x0077038C

#define ScreenFolder		(0x0077F420)
#define ExeSerial			(0x0077F5A0)
#define ConnectIP			(0x0076E2F0)

enum ObjState
{
	SelectServer	= 2,
	SwitchCharacter = 4,
	GameProcess		= 5,
};


#define ITEM_INTER 649 // 289
#define ITEM(x, y) ((x * 512) + y)
#define ITEM2(x, y) ((x * 512) + y + ITEM_INTER)
#define Color4f(r, b, g, o) ((o << 24) + (g << 16) + (b << 8) + r)
#define HDK_SET_ITEM_EFFECT 0x0052885E //1.04j
#define HDK_ITEM_EFFECT_ALLOW 0x0052887F //1.04j
#define HDK_ITEM_EFFECT_NOT_ALLOW 0x00528EC6 //1.04j
#define HDK_SET_COLOR_EFFECT 0x005288BA //1.04j
#define HDK_NEXT_ITEM_COLOR 0x005288E9 //1.04j

#define MAX_DYNAMIC_WING_EFFECT 3000
#define MAX_CUSTOM_WING_EFFECT 3000
 

#define ANTI_CHEAT_PLUS			0
