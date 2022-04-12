#include "stdafx.h"
#include "HackCheck.h"
#include "Protect.h"
#include "Util.h"

typedef int(WINAPI*WSRECV)(SOCKET,char*,int,int);
typedef int(WINAPI*WSSEND)(SOCKET,char*,int,int);

WSRECV HookRecv;
WSSEND HookSend;
BYTE EncDecKey1;
BYTE EncDecKey2;

void DecryptData(BYTE* lpMsg,int size) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]^EncDecKey1)-EncDecKey2;
	}
}

void EncryptData(BYTE* lpMsg,int size) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]+EncDecKey2)^EncDecKey1;
	}
}

bool CheckSocketPort(SOCKET s) // OK
{
	SOCKADDR_IN addr;
	int addr_len = sizeof(addr);

	if(getpeername(s,(SOCKADDR*)&addr,&addr_len) == SOCKET_ERROR)
	{
		return 0;
	}

	if(PORT_RANGE(ntohs(addr.sin_port)) == 0)
	{
		return 0;
	}

	return 1;
}

int WINAPI MyRecv(SOCKET s,char* buf,int len,int flags) // OK
{
	int result = HookRecv(s,(char*)buf,len,flags);

	if(result == SOCKET_ERROR || result == 0)
	{
		return result;
	}

	if(CheckSocketPort(s) != 0)
	{
		DecryptData((BYTE*)buf,result);
	}

	return result;
}

int WINAPI MySend(SOCKET s,char* buf,int len,int flags) // OK
{
	if(CheckSocketPort(s) != 0)
	{
		EncryptData((BYTE*)buf,len);
	}

	return HookSend(s,buf,len,flags);
}

void InitHackCheck() // OK
{
	WORD EncDecKey = 0;

	for(int n=0;n < sizeof(gProtect.m_MainInfo.CustomerName);n++)
	{
		EncDecKey += (BYTE)(gProtect.m_MainInfo.CustomerName[n]^gProtect.m_MainInfo.ClientSerial[(n%sizeof(gProtect.m_MainInfo.ClientSerial))]);
	}

	EncDecKey1 = (BYTE)0xA2;				//Pacote 01 - Recebido do GS para comparacao na nova funcao do Main
	EncDecKey2 = (BYTE)0x83;				//Pacote 02 - Recebido ao GS para comparacao na nova funcao do Main

	EncDecKey1 += LOBYTE(EncDecKey);
	EncDecKey2 += HIBYTE(EncDecKey);

	HookRecv = *(WSRECV*)(0x006A7574);		// Offsets EncDecKey Recv Hook 1.04j

	HookSend = *(WSSEND*)(0x006A7584);		// Offsets EncDecKey Send Hook 1.04j

	SetDword(0x006A7574, (DWORD)&MyRecv);	// Funcao EncDecKey Recv Hook 1.04j

	SetDword(0x006A7584, (DWORD)&MySend);	// Funcao EncDecKey Send Hook 1.04j
}
