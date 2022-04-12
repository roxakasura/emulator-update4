#include "stdafx.h"
#include "Reconnect.h"
#include "Protect.h"
#include "Protocol.h"
#include "HackCheck.h"
#include "Util.h"
#include "User.h"

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
DWORD ReconnectHelperOn = 0;

void InitReconnect() // OK
{
	SetCompleteHook(0xE9,0x0040A712,&ReconnectGetAccountInfo); //0040A712 1,04j

	SetCompleteHook(0xE9,0x00662764,&ReconnectCheckConnection); //00662764 1.04j

	SetCompleteHook(0xE9,0x006A2642,&ReconnectCloseSocket); //006A2642 1.04j

	SetCompleteHook(0xE9,0x0064D4F8,&ReconnectMenuExitGame); //0064D4F8 1.04j

//	SetCompleteHook(0xE9,0x006726A1,&ReconnectServerConnect); //006726A1 1.04j0x006726A8

	SetCompleteHook(0xE8,0x0040A94E,&ReconnectCreateConnection); //0040A94E,0049D8D5, 0065F1B8, 00672FDA, 0069CDBF 1.04j 

	SetCompleteHook(0xE8,0x0049D8D5,&ReconnectCreateConnection); //0040A94E,0049D8D5, 0065F1B8, 00672FDA, 0069CDBF 1.04j 

	SetCompleteHook(0xE8,0x0065F1B8,&ReconnectCreateConnection);  //0040A94E,0049D8D5, 0065F1B8, 00672FDA, 0069CDBF 1.04j 
	
	SetCompleteHook(0xE8,0x00672FDA,&ReconnectCreateConnection);  //0040A94E,0049D8D5, 0065F1B8, 00672FDA, 0069CDBF 1.04j 
	
	SetCompleteHook(0xE8,0x0069CDBF,&ReconnectCreateConnection);  //0040A94E,0049D8D5, 0065F1B8, 00672FDA, 0069CDBF 1.04j 

//	SetCompleteHook(0xE8,0x00719F38,&ReconnectMainProc);
}

void ReconnectMainProc() // OK
{
//	((void(*)())0x00719FEB)();

	if(*(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	if(ReconnectStatus != RECONNECT_STATUS_RECONNECT)
	{
		return;
	}

	ReconnectDrawInterface();

	if((GetTickCount()-ReconnectMaxTime) > ReconnectMaxWait)
	{
		ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT,RECONNECT_PROGRESS_NONE,0,0);
		((void(__thiscall*)(void*))0x6A2630)((void*)0x07B02978);
		return;
	}

	if((GetTickCount()-ReconnectCurTime) < ReconnectCurWait)
	{
		return;
	}

	switch(ReconnectProgress)
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
	float progress = ((ReconnectMaxWait == 0) ? 0 : (((GetTickCount() - ReconnectMaxTime)*150.0f) / (float)ReconnectMaxWait));

	progress = ((progress>151) ? 151 : progress);

	pSetBlend(true);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	pDrawBarForm(240.0f, 170.0f, 160.0f, 18.0f, 0.0f, 0);

	glColor3f(1.00f, 0.00f, 0.00f);
	pDrawBarForm(245.0f, 175.0f, progress, 8.0f, 0.0f, 0);
	glColor3f(1.00f, 1.00f, 1.00f);

	pGLSwitch();

	pSetBlend(true);

	char buff[256];

	switch (ReconnectProgress)
	{
	case RECONNECT_PROGRESS_NONE:
		pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
		wsprintf(buff, "Reconnecting...");
		pDrawText(pTextThis(), 280, 175, buff, 80, 0, (LPINT)3, 0);
		break;
	case RECONNECT_PROGRESS_CONNECTED:
		pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
		wsprintf(buff, "Logging in...");
		pDrawText(pTextThis(), 280, 175, buff, 80, 0, (LPINT)3, 0);
		break;
	case RECONNECT_PROGRESS_JOINED:
		pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
		wsprintf(buff, "Waiting character list...");
		pDrawText(pTextThis(), 280, 175, buff, 80, 0, (LPINT)3, 0);
		break;
	case RECONNECT_PROGRESS_CHAR_LIST:
		pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
		wsprintf(buff, "Waiting character info...");
		pDrawText(pTextThis(), 280, 175, buff, 80, 0, (LPINT)3, 0);
		break;
	}
}

void ReconnectSetInfo(DWORD status,DWORD progress,DWORD CurWait,DWORD MaxWait) // OK
{
	ReconnectStatus = status;

	ReconnectProgress = progress;

	ReconnectCurTime = GetTickCount();

	ReconnectMaxTime = GetTickCount();

	ReconnectCurWait = CurWait;

	ReconnectMaxWait = MaxWait;

	ReconnectAuthSend = ((status==RECONNECT_STATUS_NONE)?0:ReconnectAuthSend);

	ReconnectHelperOn = ((status==RECONNECT_STATUS_NONE)?0:ReconnectHelperOn);
}

void ReconnecGameServerLoad() // OK
{
	if(ReconnectCreateConnection(GameServerAddress,GameServerPort) != 0)
	{
		*(DWORD*)(MAIN_CONNECTION_STATUS) = 1;

		ReconnectSetInfo(RECONNECT_STATUS_RECONNECT,RECONNECT_PROGRESS_CONNECTED,10000,300000);
	}
}

void ReconnecGameServerAuth() // OK
{
	if(((ReconnectAuthSend==0)?(ReconnectAuthSend++):ReconnectAuthSend) != 0)
	{
		return;
	}

	PMSG_CONNECT_ACCOUNT_SEND pMsg;

	pMsg.header.setE(0xF1,0x01,sizeof(pMsg));

	PacketArgumentEncrypt(pMsg.account,ReconnectAccount,10);

	PacketArgumentEncrypt(pMsg.password,ReconnectPassword,10);

	pMsg.TickCount = GetTickCount();

	pMsg.ClientVersion[0] = (*(BYTE*)(0x0077F598))-1;

	pMsg.ClientVersion[1] = (*(BYTE*)(0x0077F599))-2;

	pMsg.ClientVersion[2] = (*(BYTE*)(0x0077F59A))-3;

	pMsg.ClientVersion[3] = (*(BYTE*)(0x0077F59B))-4;

	pMsg.ClientVersion[4] = (*(BYTE*)(0x0077F59C))-5;

	memcpy(pMsg.ClientSerial,(void*)0x0077F5A0,sizeof(pMsg.ClientSerial));

	DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void ReconnectOnCloseSocket() // OK
{
	if(*(DWORD*)(MAIN_SCREEN_STATE) == 5 && ReconnectStatus != RECONNECT_STATUS_DISCONNECT)
	{
		ReconnectSetInfo(RECONNECT_STATUS_RECONNECT,RECONNECT_PROGRESS_NONE,30000,60000);

		ReconnectAuthSend = 0;

		ReconnectHelperOn = 0;

		ReconnectViewportDestroy();

		*(DWORD*)(MAIN_PARTY_MEMBER_COUNT) = 0;

		memcpy(ReconnectName,gUser.m_Player.Name,10);
	}
}

void ReconnectOnMapServerMove(char* address,WORD port) // OK
{
	if(ReconnectStatus != RECONNECT_STATUS_RECONNECT || ReconnectProgress == RECONNECT_PROGRESS_CHAR_LIST)
	{
		strcpy_s(ReconnectMapServerAddress,address);

		ReconnectMapServerPort = port;

		ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT,((ReconnectProgress==RECONNECT_PROGRESS_CHAR_LIST)?ReconnectProgress:RECONNECT_PROGRESS_NONE),0,0);
	}
}

void ReconnectOnMapServerMoveAuth(BYTE result) // OK
{
	if(ReconnectStatus != RECONNECT_STATUS_RECONNECT)
	{
		if(result == 1)
		{
			ReconnectSetInfo(((ReconnectProgress==RECONNECT_PROGRESS_CHAR_LIST)?ReconnectStatus:RECONNECT_STATUS_NONE),((ReconnectProgress==RECONNECT_PROGRESS_CHAR_LIST)?ReconnectProgress:RECONNECT_PROGRESS_NONE),0,0);
		}
		else
		{
			ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT,RECONNECT_PROGRESS_NONE,0,0);
		}
	}
}

void ReconnectOnConnectAccount(BYTE result) // OK
{
	if(ReconnectProgress == RECONNECT_PROGRESS_CONNECTED)
	{
		if(ReconnectAuthSend != 0)
		{
			if(result == 1)
			{
				PMSG_CHARACTER_LIST_SEND pMsg;

				pMsg.header.set(0xF3,0x00,sizeof(pMsg));

				DataSend((BYTE*)&pMsg,pMsg.header.size);

				ReconnectSetInfo(RECONNECT_STATUS_RECONNECT,RECONNECT_PROGRESS_JOINED,30000,30000);
			}
			else
			{
				if(result == 3)
				{
					ReconnectSetInfo(RECONNECT_STATUS_RECONNECT,RECONNECT_PROGRESS_CONNECTED,10000,30000);
					ReconnectAuthSend = 0;
				}
				else
				{
					ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT,RECONNECT_PROGRESS_NONE,0,0);
					((void(__thiscall*)(void*))0x6A2630)((void*)0x07B02978);
				}
			}
		}
	}
}

void ReconnectOnCloseClient(BYTE result) // OK
{
	if(ReconnectStatus != RECONNECT_STATUS_RECONNECT)
	{
		if(result == 0 || result == 2)
		{
			ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT,RECONNECT_PROGRESS_NONE,0,0);
		}
	}
}

void ReconnectOnCharacterList() // OK
{
	if(ReconnectProgress == RECONNECT_PROGRESS_JOINED)
	{
		PMSG_CHARACTER_INFO_SEND pMsg;

		pMsg.header.set(0xF3,0x03,sizeof(pMsg));

		memcpy(pMsg.name,gUser.m_Player.Name,10);

		DataSend((BYTE*)&pMsg,pMsg.header.size);

		ReconnectSetInfo(RECONNECT_STATUS_RECONNECT,RECONNECT_PROGRESS_CHAR_LIST,30000,30000);
	}
}

void ReconnectOnCharacterInfo() // OK
{
	if(ReconnectProgress == RECONNECT_PROGRESS_CHAR_LIST)
	{
		if(ReconnectHelperOn != 0)
		{

		}
	}

	ReconnectSetInfo(RECONNECT_STATUS_NONE,RECONNECT_PROGRESS_NONE,0,0);
}

void ReconnectViewportDestroy() // OK
{
	DWORD count = 0;

	DWORD ViewportAddress = 0;

	do
	{
		BYTE send[256];

		PMSG_VIEWPORT_DESTROY_RECV pMsg;

		pMsg.header.set(0x14,0);

		int size = sizeof(pMsg);

		pMsg.count = 0;

		PMSG_VIEWPORT_DESTROY info;

		for(;count < MAX_MAIN_VIEWPORT;count++)
		{
			if((ViewportAddress=(*(DWORD*)(0x074D2B28)+(count*0x47C))) == 0)
			{
				continue;
			}

			if(*(BYTE*)(ViewportAddress+0x22C) == 0)
			{
				continue;
			}

			info.index[0] = SET_NUMBERHB((*(WORD*)(ViewportAddress+0x22C)));
			info.index[1] = SET_NUMBERLB((*(WORD*)(ViewportAddress+0x22C)));

			if((size+sizeof(info)) > sizeof(send))
			{
				break;
			}
			else
			{
				memcpy(&send[size],&info,sizeof(info));
				size += sizeof(info);

				pMsg.count++;
			}
		}

		pMsg.header.size = size;

		memcpy(send,&pMsg,sizeof(pMsg));

		ProtocolCoreEx(pMsg.header.head,send,size,-1);
	}
	while(count < MAX_MAIN_VIEWPORT);
}

BOOL ReconnectCreateConnection(char* address,WORD port) // OK
{
	if(PORT_RANGE(port) != 0 && GameServerAddress != address)
	{
		if(strcmp(ReconnectMapServerAddress,address) != 0 || ReconnectMapServerPort != port)
		{
			wsprintf(GameServerAddress,"%s",address);

			GameServerPort = port;

			memset(ReconnectMapServerAddress,0,sizeof(ReconnectMapServerAddress));

			ReconnectMapServerPort = 0;
		}
	}

	return ((BOOL(*)(char*,WORD))0x00672670)(address,port);
}

__declspec(naked) void ReconnectGetAccountInfo() // OK
{
	static DWORD ReconnectGetAccountInfoAddress1 = 0x0040A71C;

	_asm
	{
		Push 0x0A
		Lea Eax,Dword Ptr Ss:[0x075539D0];
		Push Eax
		Lea Ecx,ReconnectAccount
		Push Ecx
		Call [MemoryCpy]
		Add Esp,0x0C
		Push 0x0A
		Lea Edx, Dword Ptr Ss:[0x07553AD0];
		Push Edx
		Lea Eax,ReconnectPassword
		Push Eax
		Call [MemoryCpy]
		Add Esp,0x0C
		Mov Dword Ptr Ds:[0x07B06BE0],0x01
		Jmp [ReconnectGetAccountInfoAddress1]
	}
}

__declspec(naked) void ReconnectCheckConnection() // OK
{
	static DWORD ReconnectCheckConnectionAddress1 = 0x00662769;
	static DWORD ReconnectCheckConnectionAddress2 = 0x00662836;

	_asm
	{
		Cmp Eax,-1
		Jnz EXIT
		Mov Ecx,ReconnectStatus
		Cmp Ecx,RECONNECT_STATUS_RECONNECT
		Je EXIT
		Jmp [ReconnectCheckConnectionAddress1]
		EXIT:
		Jmp [ReconnectCheckConnectionAddress2]
	}
}

__declspec(naked) void ReconnectCloseSocket() // OK
{
	static DWORD ReconnectCloseSocketAddress1 = 0x006A264C;

	_asm
	{
		Mov Eax,Dword Ptr Ds:[MAIN_CONNECTION_STATUS]
		Cmp Eax,0x00
		Je EXIT
		Mov Ecx,Dword Ptr Ss:[Ebp-0x0C]
		Mov Edx,Dword Ptr Ds:[Ecx+0x0C]
		Push Edx
		Call [CheckSocketPort]
		Add Esp,0x04
		Je EXIT
		Call [ReconnectOnCloseSocket]
		EXIT:
		Mov Dword Ptr Ds:[MAIN_CONNECTION_STATUS],0x00
		Jmp [ReconnectCloseSocketAddress1]
	}
}

__declspec(naked) void ReconnectMenuExitGame() // OK
{
	static DWORD ReconnectMenuExitGameAddress1 = 0x0064D4FD;

	_asm
	{
		Mov Eax,ReconnectStatus
		Cmp Eax,RECONNECT_STATUS_RECONNECT
		Jnz EXIT
		Push 0
		Call [ExitProcess]
		EXIT:
		Mov ReconnectStatus,RECONNECT_STATUS_DISCONNECT
		PUSH 0x0077F128
		Jmp [ReconnectMenuExitGameAddress1]
	}
}

__declspec(naked) void ReconnectServerConnect() // OK
{
	static DWORD ReconnectServerConnectAddress1 = 0x006726A8; //ok

	_asm
	{
		And Edx,0xFFFF
		Mov GameServerPort,Dx
		Lea Ecx,GameServerAddress
		Push 0x10
		Push Eax
		Push Ecx
		Call [MemoryCpy]
		Add Esp,0x0C
		Mov ReconnectMapServerPort,0x00
		Lea Ecx,ReconnectMapServerAddress
		Push 0x10
		Push 0x00
		Push Ecx
		Call [MemorySet]
		Add Esp,0x0C
		Movzx Edx,GameServerPort
		Lea Eax,GameServerAddress
		Push Edx
		Push Eax
		Jmp[ReconnectServerConnectAddress1]
	}
}
