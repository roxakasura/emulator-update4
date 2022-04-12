#pragma once

#define pSetBlend				((void(__cdecl*)(BYTE Mode)) 0x00642288)
#define pGLSwitchBlend			((void(__cdecl*)()) 0x642323)
#define pDrawBarForm			((void(__cdecl*)(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)) 0x006437A7)
#define pGLSwitch				((void(__cdecl*)()) 0x00642209)
#define pTextThis				((LPVOID(*)()) 0x0041FD65)
#define pSetBackgroundTextColor	((void(__thiscall*)(LPVOID This, int r, int g, int b, int h)) 0x0041FF97)
#define pDrawText				((int(__thiscall*)(LPVOID This, int PosX, int PosY, LPCTSTR Text, int Width, int Height, LPINT Align, int unknow)) 0x00420024)
#define	pCheckMouseOver			((int(__cdecl*)(int a1, int a2, int a3, int a4, int a5)) 0x416686)

#define pSetCursorFocus			*(DWORD*)0x7B02758
#define pChatWindow				*(BYTE*)0x76EFC9
#define pClickCursor			*(BYTE*)(0x7AFE7F8)

#define MAX_MAIN_VIEWPORT 400
#define MAX_WIN_WIDTH 640

#include "stdafx.h"

enum eReconnectStatus
{
	RECONNECT_STATUS_NONE = 0,
	RECONNECT_STATUS_RECONNECT = 1,
	RECONNECT_STATUS_DISCONNECT = 2,
};

enum eReconnectProgress
{
	RECONNECT_PROGRESS_NONE = 0,
	RECONNECT_PROGRESS_CONNECTED = 1,
	RECONNECT_PROGRESS_JOINED = 2,
	RECONNECT_PROGRESS_CHAR_LIST = 3,
	RECONNECT_PROGRESS_CHAR_INFO = 4,
};

void InitReconnect();
void ReconnectMainProc();
void ReconnectDrawInterface();
void ReconnectSetInfo(DWORD status,DWORD progress,DWORD CurWait,DWORD MaxWait);
void ReconnecGameServerLoad();
void ReconnecGameServerAuth();
void ReconnectOnCloseSocket();
void ReconnectOnMapServerMove(char* address,WORD port);
void ReconnectOnMapServerMoveAuth(BYTE result);
void ReconnectOnConnectAccount(BYTE result);
void ReconnectOnCloseClient(BYTE result);
void ReconnectOnCharacterList();
void ReconnectOnCharacterInfo();
void ReconnectViewportDestroy();
BOOL ReconnectCreateConnection(char* address,WORD port);
void ReconnectGetAccountInfo();
void ReconnectCheckConnection();
void ReconnectCloseSocket();
void ReconnectMenuExitGame();
void ReconnectServerConnect();
