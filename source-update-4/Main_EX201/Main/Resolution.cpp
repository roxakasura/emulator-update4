#include "stdafx.h"
#include "Resolution.h"
#include "Offset.h"
#include "Util.h"

void InitResolution()
{
	SetCompleteHook(0xE9, 0x004D3747, &ResolutionSwitch);

	SetCompleteHook(0xE9, 0x004D4A73, &ResolutionSwitchFont);

	SetCompleteHook(0xE9, 0x0045F6C3, &ResolutionMoveList);

	SetCompleteHook(0xE9, 0x00460313, &ResolutionMoveList2);

	SetCompleteHook(0xE8, 0x00693370, &ResolutionKanturu);
}

__declspec(naked) void ResolutionSwitch()
{
	static DWORD ResolutionSwitchAddress1 = 0x004D37C3;

	_asm
	{
		Mov Eax, Dword Ptr Ds : [0x05792568] ; //MAIN_RESOLUTION
		Cmp Eax, 0x00;
		Jnz NEXT1;
		Mov Dword Ptr Ds : [0x007086F8] , 640; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ds : [0x007086FC] , 480; //MAIN_RESOLUTION_Y
		Jmp EXIT;
	NEXT1:
		Cmp Eax, 0x01;
		Jnz NEXT2;
		Mov Dword Ptr Ds : [0x007086F8] , 800; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ds : [0x007086FC] , 600; //MAIN_RESOLUTION_Y
		Jmp EXIT;
	NEXT2:
		Cmp Eax, 0x02;
		Jnz NEXT3;
		Mov Dword Ptr Ds : [0x007086F8] , 1024; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ds : [0x007086FC] , 768; //MAIN_RESOLUTION_Y
		Jmp EXIT;
	NEXT3:
		Cmp Eax, 0x03;
		Jnz NEXT4;
		Mov Dword Ptr Ds : [0x007086F8] , 1280; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ds : [0x007086FC] , 1024; //MAIN_RESOLUTION_Y
		Jmp EXIT;
	NEXT4:
		Cmp Eax, 0x04;
		Jnz NEXT5;
		Mov Dword Ptr Ds : [0x007086F8] , 1360; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ds : [0x007086FC] , 768; //MAIN_RESOLUTION_Y
		Jmp EXIT;
	NEXT5:
		Cmp Eax, 0x05;
		Jnz NEXT6;
		Mov Dword Ptr Ds : [0x007086F8] , 1440; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ds : [0x007086FC] , 900; //MAIN_RESOLUTION_Y
		Jmp EXIT;
	NEXT6:
		Cmp Eax, 0x06;
		Jnz NEXT7;
		Mov Dword Ptr Ds : [0x007086F8] , 1600; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ds : [0x007086FC] , 900; //MAIN_RESOLUTION_Y
		Jmp EXIT;
	NEXT7:
		Cmp Eax, 0x07;
		Jnz NEXT8;
		Mov Dword Ptr Ds : [0x007086F8] , 1680; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ds : [0x007086FC] , 1050; //MAIN_RESOLUTION_Y
		Jmp EXIT;
	NEXT8:
		Cmp Eax, 0x08;
		Jnz EXIT;
		Mov Dword Ptr Ds : [0x007086F8] , 1920; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ds : [0x007086FC] , 1080; //MAIN_RESOLUTION_Y
	EXIT:
		Jmp[ResolutionSwitchAddress1];
	}
}

__declspec(naked) void ResolutionSwitchFont()
{
	static DWORD ResolutionSwitchFontAddress1 = 0x004D4AEC;
	static DWORD Resolution_ClipX1 = 0x006EA788;
	static DWORD Resolution_ClipX2 = 0x006EA7AC;
	static float Float2000 = 2000.0f;

	_asm
	{
		Mov Eax, Dword Ptr Ds : [0x007086F8] ; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ss : [Ebp - 0x2474] , Eax;
		Cmp Dword Ptr Ss : [Ebp - 0x2474] , 640;
		Jnz NEXT1;
		Mov Dword Ptr Ds : [0x077DDFF8] , 0x0C; //MAIN_FONT_SIZE
		Jmp EXIT;
	NEXT1:
		Cmp Dword Ptr Ss : [Ebp - 0x2474] , 800;
		Jnz NEXT2;
		Mov Dword Ptr Ds : [0x077DDFF8] , 0x0D; //MAIN_FONT_SIZE
		Jmp EXIT;
	NEXT2:
		Cmp Dword Ptr Ss : [Ebp - 0x2474] , 1024;
		Jnz NEXT3;
		Mov Dword Ptr Ds : [0x077DDFF8] , 0x0E; //MAIN_FONT_SIZE
		Jmp EXIT;
	NEXT3:
		Cmp Dword Ptr Ss : [Ebp - 0x2474] , 1280;
		Jnz NEXT4;
		Mov Dword Ptr Ds : [0x077DDFF8] , 0x0F; //MAIN_FONT_SIZE
		Jmp EXIT;
	NEXT4:
		Mov Dword Ptr Ds : [0x077DDFF8] , 0x0F; //MAIN_FONT_SIZE
		Push Float2000;
		Push Resolution_ClipX1;
		Call[SetFloat];
		Add Esp, 0x08;
		Push Float2000;
		Push Resolution_ClipX2;
		Call[SetFloat];
		Add Esp, 0x08;
	EXIT:
		Jmp[ResolutionSwitchFontAddress1];
	}
}

__declspec(naked) void ResolutionMoveList()
{
	static DWORD ResolutionMoveListAddress1 = 0x0045F710;
	static DWORD ResolutionMoveListAddress2 = 0x0045F6CC;

	_asm
	{
		Mov Ecx, Dword Ptr Ds : [0x007086F8] ; //MAIN_RESOLUTION_X
		Mov Dword Ptr Ss : [Ebp - 0x5C] , Esi;
		Cmp Ecx, 0x500;
		Jbe EXIT;
		Jmp[ResolutionMoveListAddress1];
	EXIT:
		Jmp[ResolutionMoveListAddress2];
	}
}

__declspec(naked) void ResolutionMoveList2()
{
	static DWORD ResolutionMoveListAddress1 = 0x004603A6;
	static DWORD ResolutionMoveListAddress2 = 0x0046031E;

	_asm
	{
		Mov Ecx, Dword Ptr Ds : [0x007086F8] ; //MAIN_RESOLUTION_X
		Cmp Ecx, 0x500;
		Jbe EXIT;
		Jmp[ResolutionMoveListAddress1];
	EXIT:
		Jmp[ResolutionMoveListAddress2];
	}
}

void ResolutionKanturu()
{
	if (m_Resolution >= 4)
	{
		*(WORD*)(*(DWORD*)(0x07DE8544) + 0x0C) = 0xD7;
	}

	((bool(__thiscall*)(void*))0x004325F0)((void*)*(DWORD*)(0x07DE8544));
}