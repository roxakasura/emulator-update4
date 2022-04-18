#pragma once

#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT _WIN32_WINNT_WINXP

#if(GAMESERVER_TYPE == 0)
#define GAMESERVER_VERSION "GameServer"
#else
#define GAMESERVER_VERSION "GameSiege"
#endif


#if(GAMESERVER_DOWNGRADE == 301)
#define GAMESERVER_TITLE "Season 3 - 1.04J"
#elif(GAMESERVER_DOWNGRADE == 201)
#define GAMESERVER_TITLE "Season 2 - 1.02R"
#else
#define GAMESERVER_TITLE "Season 0 - 1.01T"
#endif

#ifndef GAMESERVER_TYPE
#define GAMESERVER_TYPE 0
#endif

#define GAMESERVER_CLIENTE_UPDATE 4

#ifndef GAMESERVER_EXTRA
#define GAMESERVER_EXTRA 1
#endif

#ifndef GAMESERVER_UPDATE
#define GAMESERVER_UPDATE 803
#endif

#ifndef GAMESERVER_DOWNGRADE
#define GAMESERVER_DOWNGRADE 301
#endif

#ifndef GAMESERVER_LANGUAGE
#define GAMESERVER_LANGUAGE 1
#endif

#ifndef PROTECT_STATE
#define PROTECT_STATE 1
#endif

#ifndef ENCRYPT_STATE
#define ENCRYPT_STATE 1
#endif

#define TARCISIO 1
#define ALGOQUEVOUUSARUMDIA 0
#define MUSIGN 0
#define WILLIAMCUSTOM 0

// System Include
#include <windows.h>
#include <winsock2.h>
#include <mswSock.h>
#include <commctrl.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <map>
#include <vector>
#include <queue>
#include <random>
#include <Rpc.h>
#include <algorithm>
#include <string>
#include <atltime.h>
#include <dbghelp.h>
#include <Psapi.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Rpcrt4.lib")
#pragma comment(lib,"dbghelp.lib")
#pragma comment(lib,"Psapi.lib")

#if(GAMESERVER_UPDATE>=701)
#if(NDEBUG==0)
#pragma comment(lib,"..\\..\\..\\Util\\cryptopp\\Debug\\cryptlib.lib")
#else
#pragma comment(lib,"..\\..\\..\\Util\\cryptopp\\Release\\cryptlib.lib")
#endif
#pragma comment(lib,"..\\..\\..\\Util\\mapm\\mapm.lib")
#endif

typedef char chr;

typedef float flt;

typedef short shrt;

typedef unsigned __int64 QWORD;