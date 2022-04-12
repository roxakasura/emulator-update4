#include "stdafx.h"

char GameServerAddress[16];
WORD GameServerPort;
char ReconnectAccount[11];
char ReconnectPassword[11];
char ReconnectName[11];
char ReconnectMapServerAddress[16];
WORD ReconnectMapServerPort;
DWORD ReconnectStatus = RECONNECT_STATUS_NONE;
DWORD ReconnectProgress = RECONNECT_PROGRESS_NONE;
DWORD ReconnectCurTime = 0;
DWORD ReconnectMaxTime = 0;
DWORD ReconnectCurWait = 0;
DWORD ReconnectMaxWait = 0;
DWORD ReconnectAuthSend = 0;

void InitReconnect()
{
	SetCompleteHook(0xE9, 0x0062110F, &ReconnectGetAccountInfo);

	SetCompleteHook(0xE9, 0x00628FDD, &ReconnectCheckConnection);

	SetCompleteHook(0xE9, 0x004E0CB5, &ReconnectCloseSocket);

	SetCompleteHook(0xE9, 0x006104B0, &ReconnectMenuExitGame);

	MemorySet(0x004BBAB3, 0x90, 0x05); // Fix Reconnect Exit Message

	SetCompleteHook(0xE9, 0x004BBA52, &ReconnectServerConnect);

	SetCompleteHook(0xE8, 0x00411016, &ReconnectCreateConnection);

	SetCompleteHook(0xE8, 0x004BC24F, &ReconnectCreateConnection);

	SetCompleteHook(0xE8, 0x004DC04C, &ReconnectCreateConnection);

	SetCompleteHook(0xE8, 0x00620529, &ReconnectCreateConnection);

	SetCompleteHook(0xE8, 0x00620E78, &ReconnectCreateConnection);

	SetCompleteHook(0xE8, 0x00632977, &ReconnectCreateConnection);

	//	SetCompleteHook(0xE8, 0x00596E7F, &ReconnectMainProc);
}

void ReconnectMainProc()
{
	//	((void(*)())0x00598C30)();

	if (*(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	if (ReconnectStatus != RECONNECT_STATUS_RECONNECT)
	{
		return;
	}

	//pSetCursorFocus = 0x1B;

	ReconnectDrawInterface();

	if ((GetTickCount() - ReconnectMaxTime) > ReconnectMaxWait)
	{
		ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT, RECONNECT_PROGRESS_NONE, 0, 0);
		((void(__thiscall*)(void*))0x004E0CA0)((void*)0x57506A0);
		return;
	}

	if ((GetTickCount() - ReconnectCurTime) < ReconnectCurWait)
	{
		return;
	}

	switch (ReconnectProgress)
	{
	case RECONNECT_PROGRESS_NONE:
		ReconnecGameServerLoad();
		break;
	case RECONNECT_PROGRESS_CONNECTED:
		ReconnecGameServerAuth();
		break;
	}

	ReconnectCurTime = GetTickCount();
}

void ReconnectDrawInterface()
{
	float MaxWidth = 150.0f;

	float progress = ((ReconnectMaxWait == 0) ? 0 : (((GetTickCount() - ReconnectMaxTime) * MaxWidth) / (float)ReconnectMaxWait));

	progress = ((progress > MaxWidth) ? MaxWidth : progress);

/*	float PosX = ImgCenterScreenPosX(MaxWidth);

	pSetBlend(true);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	pDrawBarForm(PosX, 170.0f, 160.0f, 18.0f, 0.0f, 0);

	glColor3f(1.00f, 0.00f, 0.00f);
	pDrawBarForm(PosX + 5, 175.0f, progress, 8.0f, 0.0f, 0);
	glColor3f(1.00f, 1.00f, 1.00f);*/

	//pGLSwitch();

	//pSetBlend(true);

	char buff[256];

	switch (ReconnectProgress)
	{
	case RECONNECT_PROGRESS_NONE:
		//pDrawTextBackground = Color4f(255, 255, 255, 0);
		wsprintf(buff, "Reconnecting...");
		pDrawInfo(240, 175, buff, (160 * *(GLsizei*)MAIN_RESOLUTION_X / 640), 7, 1);
		break;
	case RECONNECT_PROGRESS_CONNECTED:
		//pDrawTextBackground = Color4f(255, 255, 255, 0);
		wsprintf(buff, "Logging in...");
		pDrawInfo(240, 175, buff, (160 * *(GLsizei*)MAIN_RESOLUTION_X / 640), 7, 1);
		break;
	case RECONNECT_PROGRESS_JOINED:
		//pDrawTextBackground = Color4f(255, 255, 255, 0);
		wsprintf(buff, "Waiting character list...");
		pDrawInfo(240, 175, buff, (160 * *(GLsizei*)MAIN_RESOLUTION_X / 640), 7, 1);
		break;
	case RECONNECT_PROGRESS_CHAR_LIST:
		//pDrawTextBackground = Color4f(255, 255, 255, 0);
		wsprintf(buff, "Waiting character info...");
		pDrawInfo(240, 175, buff, (160 * *(GLsizei*)MAIN_RESOLUTION_X / 640), 7, 1);
		break;
	}
	//pGLSwitch();
}

void ReconnectSetInfo(DWORD status, DWORD progress, DWORD CurWait, DWORD MaxWait)
{
	ReconnectStatus = status;

	ReconnectProgress = progress;

	ReconnectCurTime = GetTickCount();

	ReconnectMaxTime = GetTickCount();

	ReconnectCurWait = CurWait;

	ReconnectMaxWait = MaxWait;

	ReconnectAuthSend = ((status == RECONNECT_STATUS_NONE) ? 0 : ReconnectAuthSend);
}

void ReconnecGameServerLoad()
{
	if (ReconnectCreateConnection(GameServerAddress, GameServerPort) != 0)
	{
		*(DWORD*)(MAIN_CONNECTION_STATUS) = 1;

		ReconnectSetInfo(RECONNECT_STATUS_RECONNECT, RECONNECT_PROGRESS_CONNECTED, 10000, 30000);
	}
}

void ReconnecGameServerAuth()
{
	if (((ReconnectAuthSend == 0) ? (ReconnectAuthSend++) : ReconnectAuthSend) != 0)
	{
		return;
	}

	PMSG_CONNECT_ACCOUNT_SEND pMsg;

	pMsg.header.setE(0xF1, 0x01, sizeof(pMsg));

	PacketArgumentEncrypt(pMsg.account, ReconnectAccount, (sizeof(ReconnectAccount) - 1));

	PacketArgumentEncrypt(pMsg.password, ReconnectPassword, (sizeof(ReconnectPassword) - 1));

	pMsg.TickCount = GetTickCount();

	pMsg.ClientVersion[0] = (*(BYTE*)(0x006B7248)) - 1;

	pMsg.ClientVersion[1] = (*(BYTE*)(0x006B7249)) - 2;

	pMsg.ClientVersion[2] = (*(BYTE*)(0x006B724A)) - 3;

	pMsg.ClientVersion[3] = (*(BYTE*)(0x006B724B)) - 4;

	pMsg.ClientVersion[4] = (*(BYTE*)(0x006B724C)) - 5;

	memcpy(pMsg.ClientSerial, (void*)0x006B7250, sizeof(pMsg.ClientSerial));

	DataSend((BYTE*)&pMsg, pMsg.header.size);
}

void ReconnectOnCloseSocket()
{
	if (*(DWORD*)(MAIN_SCREEN_STATE) == 5 && ReconnectStatus != RECONNECT_STATUS_DISCONNECT)
	{
		ReconnectSetInfo(RECONNECT_STATUS_RECONNECT, RECONNECT_PROGRESS_NONE, 30000, 30000);

		ReconnectAuthSend = 0;

		ReconnectViewportDestroy();

		*(DWORD*)(MAIN_PARTY_MEMBER_COUNT) = 0;

		memcpy(ReconnectName, (char*)(*(DWORD*)(MAIN_VIEWPORT_STRUCT)+0x1C9), sizeof(ReconnectName));
	}
}

void ReconnectOnMapServerMove(char* address, WORD port)
{
	if (ReconnectStatus != RECONNECT_STATUS_RECONNECT || ReconnectProgress == RECONNECT_PROGRESS_CHAR_LIST)
	{
		strcpy_s(ReconnectMapServerAddress, address);

		ReconnectMapServerPort = port;

		ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT, ((ReconnectProgress == RECONNECT_PROGRESS_CHAR_LIST) ? ReconnectProgress : RECONNECT_PROGRESS_NONE), 0, 0);
	}
}

void ReconnectOnMapServerMoveAuth(BYTE result)
{
	if (ReconnectStatus != RECONNECT_STATUS_RECONNECT)
	{
		if (result == 1)
		{
			ReconnectSetInfo(((ReconnectProgress == RECONNECT_PROGRESS_CHAR_LIST) ? ReconnectStatus : RECONNECT_STATUS_NONE), ((ReconnectProgress == RECONNECT_PROGRESS_CHAR_LIST) ? ReconnectProgress : RECONNECT_PROGRESS_NONE), 0, 0);
		}
		else
		{
			ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT, RECONNECT_PROGRESS_NONE, 0, 0);
		}
	}
}

void ReconnectOnConnectAccount(BYTE result)
{
	if (ReconnectProgress == RECONNECT_PROGRESS_CONNECTED)
	{
		if (ReconnectAuthSend != 0)
		{
			if (result == 1)
			{
				PMSG_CHARACTER_LIST_SEND pMsg;

				pMsg.header.set(0xF3, 0x00, sizeof(pMsg));

				DataSend((BYTE*)&pMsg, pMsg.header.size);

				ReconnectSetInfo(RECONNECT_STATUS_RECONNECT, RECONNECT_PROGRESS_JOINED, 30000, 30000);
			}
			else
			{
				if (result == 3)
				{
					ReconnectSetInfo(RECONNECT_STATUS_RECONNECT, RECONNECT_PROGRESS_CONNECTED, 10000, 30000);
					ReconnectAuthSend = 0;
				}
				else
				{
					ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT, RECONNECT_PROGRESS_NONE, 0, 0);
					((void(__thiscall*)(void*))0x004E0CA0)((void*)0x57506A0);
				}
			}
		}
	}
}

void ReconnectOnCloseClient(BYTE result)
{
	if (ReconnectStatus != RECONNECT_STATUS_RECONNECT)
	{
		if (result == 0 || result == 2)
		{
			ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT, RECONNECT_PROGRESS_NONE, 0, 0);
		}
	}
}

void ReconnectOnCharacterList()
{
	if (ReconnectProgress == RECONNECT_PROGRESS_JOINED)
	{
		PMSG_CHARACTER_INFO_SEND pMsg;

		pMsg.header.set(0xF3, 0x03, sizeof(pMsg));

		memcpy(pMsg.name, ReconnectName, sizeof(pMsg.name));

		DataSend((BYTE*)&pMsg, pMsg.header.size);

		ReconnectSetInfo(RECONNECT_STATUS_RECONNECT, RECONNECT_PROGRESS_CHAR_LIST, 30000, 30000);
	}
}

void ReconnectOnCharacterInfo()
{
	ReconnectSetInfo(RECONNECT_STATUS_NONE, RECONNECT_PROGRESS_NONE, 0, 0);

//	pSetCursorFocus = 0;
}

void ReconnectViewportDestroy()
{
	DWORD count = 0;

	DWORD ViewportAddress = 0;

	do
	{
		BYTE send[256];

		PMSG_VIEWPORT_DESTROY_RECV pMsg;

		pMsg.header.set(0x14, 0);

		int size = sizeof(pMsg);

		pMsg.count = 0;

		PMSG_VIEWPORT_DESTROY info;

		for (; count < MAX_MAIN_VIEWPORT; count++)
		{
			if ((ViewportAddress = (*(DWORD*)(0x07424644) + (count * 0x424))) == 0)
			{
				continue;
			}

			if (*(BYTE*)(ViewportAddress) == 0)
			{
				continue;
			}

			info.index[0] = SET_NUMBERHB((*(WORD*)(ViewportAddress + 0x1E4)));
			info.index[1] = SET_NUMBERLB((*(WORD*)(ViewportAddress + 0x1E4)));

			if ((size + sizeof(info)) > sizeof(send))
			{
				break;
			}
			else
			{
				memcpy(&send[size], &info, sizeof(info));
				size += sizeof(info);

				pMsg.count++;
			}
		}

		pMsg.header.size = size;

		memcpy(send, &pMsg, sizeof(pMsg));

		ProtocolCoreEx(pMsg.header.head, send, size, -1);
	} while (count < MAX_MAIN_VIEWPORT);
}

BOOL ReconnectCreateConnection(char* address, WORD port)
{
	if (PORT_RANGE(port) != 0 && GameServerAddress != address)
	{
		if (strcmp(ReconnectMapServerAddress, address) != 0 || ReconnectMapServerPort != port)
		{
			wsprintf(GameServerAddress, "%s", address);

			GameServerPort = port;

			memset(ReconnectMapServerAddress, 0, sizeof(ReconnectMapServerAddress));

			ReconnectMapServerPort = 0;
		}
	}

	return ((BOOL(*)(char*, WORD))0x004BBA20)(address, port);
}

__declspec(naked) void ReconnectGetAccountInfo()
{
	static DWORD ReconnectGetAccountInfoAddress1 = 0x0041DED0;
	static DWORD ReconnectGetAccountInfoAddress2 = 0x00621132;

	_asm
	{
		Push 0x0777D7C0;
		Push 0x006C47A8;
		Push 0x057500D8;
		Mov Dword Ptr Ds : [0x07D1A9D0] , Eax;
		Mov Dword Ptr DS : [0x07D17210] , 0x00;
		Call[ReconnectGetAccountInfoAddress1];
		Push 0x0A;
		Lea Eax, Dword Ptr Ss : [0x0777D7C0] ;
		Push Eax;
		Lea Ecx, ReconnectAccount;
		Push Ecx;
		Call[MemoryCpy];
		Add Esp, 0x0C;
		Push 0x0A;
		Lea Edx, Dword Ptr Ss : [0x0777D8C0] ;
		Push Edx;
		Lea Eax, ReconnectPassword;
		Push Eax;
		Call[MemoryCpy];
		Add Esp, 0x0C;
		Jmp[ReconnectGetAccountInfoAddress2];
	}
}

__declspec(naked) void ReconnectCheckConnection()
{
	static DWORD ReconnectCheckConnectionAddress1 = 0x00628FE2;
	static DWORD ReconnectCheckConnectionAddress2 = 0x0062901D;

	_asm
	{
		Cmp Eax, -1;
		Jnz EXIT;
		Mov Ecx, ReconnectStatus;
		Cmp Ecx, RECONNECT_STATUS_RECONNECT;
		Je EXIT;
		Jmp[ReconnectCheckConnectionAddress1];
	EXIT:
		Jmp[ReconnectCheckConnectionAddress2];
	}
}

__declspec(naked) void ReconnectCloseSocket()
{
	static DWORD ReconnectCloseSocketAddress1 = 0x004E0CBB;

	_asm
	{
		Mov Eax, Dword Ptr Ds : [MAIN_CONNECTION_STATUS] ;
		Cmp Eax, 0x00;
		Je EXIT;
		Mov Ecx, Dword Ptr Ss : [Ebp - 0x08] ;
		Mov Eax, Dword Ptr Ds : [Ecx + 0x0C] ;
		Push Eax;
		Call[CheckSocketPort];
		Add Esp, 0x04;
		Je EXIT;
		Call[ReconnectOnCloseSocket];
	EXIT:
		Mov Dword Ptr Ds : [MAIN_CONNECTION_STATUS] , 0x00;
		Jmp[ReconnectCloseSocketAddress1];
	}
}

__declspec(naked) void ReconnectMenuExitGame()
{
	static DWORD ReconnectMenuExitGameAddress1 = 0x006104B5;

	_asm
	{
		Mov Eax, ReconnectStatus;
		Cmp Eax, RECONNECT_STATUS_RECONNECT;
		Jnz EXIT;
		Push 0;
		Call[ExitProcess];
	EXIT:
		Mov ReconnectStatus, RECONNECT_STATUS_DISCONNECT;
		Push 0x006C452C;
		Jmp[ReconnectMenuExitGameAddress1];
	}
}

__declspec(naked) void ReconnectServerConnect()
{
	static DWORD ReconnectServerConnectAddress1 = 0x004BBA59;

	_asm
	{
		And Eax, 0xFFFF;
		Mov GameServerPort, Ax;
		Lea Ecx, GameServerAddress;
		Push 0x10;
		Push Edi;
		Push Ecx;
		Call[MemoryCpy];
		Add Esp, 0x0C;
		Mov ReconnectMapServerPort, 0x00;
		Lea Ecx, ReconnectMapServerAddress;
		Push 0x10;
		Push 0x00;
		Push Ecx;
		Call[MemorySet];
		Add Esp, 0x0C;
		Movzx Eax, GameServerPort;
		Lea Edi, GameServerAddress;
		Push Eax;
		Push Edi;
		Jmp[ReconnectServerConnectAddress1];
	}
}