#include "stdafx.h"
#include "Common.h"
#include "Protocol.h"
#include "Util.h"

DWORD ClicMouseTime = GetTickCount();

void InitCommon() // OK
{
	SetCompleteHook(0xE9,0x0066271F,&CheckTickCount);
}

void ClicMouseProc() // OK
{
	if(*(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	if((GetTickCount()-ClicMouseTime) < 1000)
	{
		return;
	}

	ClicMouseTime = GetTickCount();

	PBMSG_HEAD pMsg;

	pMsg.set(0x04,sizeof(pMsg));

	DataSend((BYTE*)&pMsg,pMsg.size);
}

void __declspec(naked) CheckTickCount() // OK
{
	static DWORD CheckTickCountAddress1 = 0x00662725;

	_asm
	{
		Push 1
		Call Dword Ptr Ds:[Sleep]
		Call Dword Ptr Ds:[GetTickCount]
		Jmp[CheckTickCountAddress1]
	}
}