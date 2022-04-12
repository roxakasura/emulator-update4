#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT               
#define _WIN32_WINNT 0x0501
#endif

#ifndef _WIN32_WINNT               
#define _WIN32_WINNT 0x0610
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0600
#endif

#define WIN32_LEAN_AND_MEAN

typedef unsigned __int64 QWORD;

#include <windows.h>
#include <WinBase.h>
#include <WinSock2.h>
#include <WinUser.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <process.h>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <WinInet.h>
#include <rpc.h>
#include <rpcdce.h>
#include <ShellAPI.h>
#include <Psapi.h>
#include <wchar.h>
#include "detoured.h"
#include "detours.h"
#include "glaux.h"

#include <crtdefs.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GLu32.lib")
#pragma comment(lib,"GLaux.lib")
#pragma comment(lib,"Detours.lib")
#pragma comment(lib,"Psapi.lib")
#pragma comment(lib,"Ws2_32.lib")

#include "ToolKit.h"
#include "Window.h"
#include "Util.h"
#include "Resolution.h"
#include "Protect.h"
#include "Util.h"
#include "HackCheck.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "User.h"
#include "Reconnect.h"
#include "PacketManager.h"
#include "Interface.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "ItemManager.h"
#include "MiniMap.h"
#include "Controller.h"
#include "Camera3D.h"
#include "Font.h"
#include "SelectChar.h"
#include "ServerInfo.h"
#include "ItemDescription.h"
#include "DynamicEffect.h"
#include "StaticEffect.h"
#include "EffectManager.h"
#include "MathLib.h"
#include "BMD.h"
#include "PlayerSystem.h"
#include "ItemDurability.h"
#include "RightClick.h"
#include "Features99z.h"
#include "NewMaps.h"
#include "Experience.h"
#include "Console.h"
#include "TrayMode.h"
#include "ItemSmoke.h"
#include "Smoke.h"
#include "Tokenizer.h"
#include "CustomMap.h"
#include "Monster.h"
#include "CustomMonster.h"

void GlobalMessage();

#define MAIN_RESOLUTION 0x5750320
#define MAIN_RESOLUTION_X 0x6C4158
#define MAIN_RESOLUTION_Y 0x6C415C
#define MAIN_FONT_SIZE 0x773D130
#define MAX_DYNAMIC_WING_EFFECT 3000
#define MAX_CUSTOM_WING_EFFECT 3000
#define Color4f(r, b, g, o) ((o << 24) + (g << 16) + (b << 8) + r)
#define HDK_SET_ITEM_EFFECT 0x00506AB8 //1.01t
#define HDK_ITEM_EFFECT_ALLOW 0x00506ACC //1.01t
#define HDK_ITEM_EFFECT_NOT_ALLOW 0x00506E65 //1.01t
#define HDK_SET_COLOR_EFFECT 0x00506B1D //1.01t
#define HDK_NEXT_ITEM_COLOR 0x00506B42 //1.01t
#define MAIN_CLIENT_UPDATE 4