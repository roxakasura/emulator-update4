#include "stdafx.h"
#include "Patchs.h"
#include "Protect.h"
#include "Protocol.h"
#include "Util.h"

__declspec(naked) void ReduceCPU()
{
	static DWORD JmpBack = 0x0067040B;

	__asm
	{
		Push 1;

		Call Dword Ptr Ds : [0x006E8148] ; //Sleep

		Call Dword Ptr Ds : [0x006E8144] ; //GetTickCount

		Jmp[JmpBack];
	}
}

void ReduceRam(LPVOID lpThreadParameter)
{
	HANDLE v1;

	HANDLE v2;

	while (TRUE)
	{
		Sleep(5000);

		v1 = GetCurrentProcess();

		SetProcessWorkingSetSize(v1, 0xFFFFFFFF, 0xFFFFFFFF);

		v2 = GetCurrentProcess();

		SetThreadPriority(v2, -2);
	}
}

void InitPatchs()
{
	SetByte(0x006F8DF4, 0xA0); // Accent

	SetByte(0x004D4017, 0xEB); // Crack (mu.exe)

	SetByte(0x004D4510, 0x75); // config.ini read error

	SetByte(0x004D4568, 0xE9); // Crack (GameGuard)

	SetByte(0x004D4569, 0xA6); // Crack (GameGuard)

	SetByte(0x004D456A, 0x00); // Crack (GameGuard)

	SetByte(0x004D456B, 0x00); // Crack (GameGuard)

	SetByte(0x004D456C, 0x00); // Crack (GameGuard)

	SetByte(0x004DF23A, 0xEB); // Crack (ResourceGuard)

	SetByte(0x0046EC49, 0xEB); // Ctrl Fix

	SetByte(0x004D3F64, 0xEB); // Multi Instance

	SetByte(0x006F99FC, (gProtect.m_MainInfo.ClientVersion[0] + 1)); // Version

	SetByte(0x006F99FD, (gProtect.m_MainInfo.ClientVersion[2] + 2)); // Version

	SetByte(0x006F99FE, (gProtect.m_MainInfo.ClientVersion[3] + 3)); // Version

	SetByte(0x006F99FF, (gProtect.m_MainInfo.ClientVersion[5] + 4)); // Version

	SetByte(0x006F9A00, (gProtect.m_MainInfo.ClientVersion[6] + 5)); // Version

	SetWord(0x0070875C, (gProtect.m_MainInfo.IpAddressPort)); // IpAddressPort

	SetDword(0x0066FFF8, (DWORD)gProtect.m_MainInfo.ScreenShotPath); //Screenshot

	SetDword(0x004D3392, (DWORD)gProtect.m_MainInfo.WindowName); //Window Name

	MemoryCpy(0x006F8E34, gProtect.m_MainInfo.IpAddress, sizeof(gProtect.m_MainInfo.IpAddress)); // IpAddress

	MemoryCpy(0x006F9A04, gProtect.m_MainInfo.ClientSerial, sizeof(gProtect.m_MainInfo.ClientSerial)); // ClientSerial

	MemorySet(0x004215B0, 0x90, 29); // Remove MuError.log

	SetCompleteHook(0xFF, 0x004FFD5D, &ProtocolCoreEx);

	SetCompleteHook(0xE9, 0x00670405, &ReduceCPU);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ReduceRam, 0, 0, 0);
}