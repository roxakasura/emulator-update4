#include "stdafx.h"
#include "Resolution.h"
#include "Util.h"
#include "PlayerSystem.h"
#include "Console.h"

double Resolution_ClipX1 = 0x007588B4;
double Resolution_ClipX2 = 0x007588C0;
float Float2000 = 2000.0f;


void InitResolution() // OK
{
	SetCompleteHook(0xE9, 0x00648274, &ResolutionSwitch);

	SetCompleteHook(0xE9, 0x00649553, &ResolutionSwitchFont);

	SetCompleteHook(0xE9, 0x004EECA1, &ResolutionMoveList);

	SetCompleteHook(0xE9, 0x004EE5EB, &ResolutionMoveList2);

	SetCompleteHook(0xE9, 0x004BADBA, &ResolutionKanturu);

	SetCompleteHook(0xE9, 0x0040AB03, &ResolutionCrywolf);
}

__declspec(naked) void ResolutionSwitch() // OK
{
	static DWORD ResolutionSwitchAddress1 = 0x00648302;

	_asm
	{
		Mov Edx,Dword Ptr Ds:[MAIN_RESOLUTION]
		Mov Dword Ptr Ss:[Ebp-0x340],Edx
		Cmp Dword Ptr Ss:[Ebp-0x340],0x00
		Jnz NEXT1
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],640
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],480
		Jmp EXIT
		NEXT1:
		Cmp Dword Ptr Ss:[Ebp-0x340],0x01
		Jnz NEXT2
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],800
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],600
		Jmp EXIT
		NEXT2:
		Cmp Dword Ptr Ss:[Ebp-0x340],0x02
		Jnz NEXT3
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1024
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],768
		Jmp EXIT
		NEXT3:
		Cmp Dword Ptr Ss:[Ebp-0x340],0x03
		Jnz NEXT4
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1280
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],1024
		Jmp EXIT
		NEXT4:
		Cmp Dword Ptr Ss:[Ebp-0x340],0x04
		Jnz NEXT5
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1360
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],768
		Jmp EXIT
		NEXT5:
		Cmp Dword Ptr Ss:[Ebp-0x340],0x05
		Jnz NEXT6
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1440
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],900
		Jmp EXIT
		NEXT6:
		Cmp Dword Ptr Ss:[Ebp-0x340],0x06
		Jnz NEXT7
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1600
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],900
		Jmp EXIT
		NEXT7:
		Cmp Dword Ptr Ss:[Ebp-0x340],0x07
		Jnz NEXT8
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1680
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],1050
		Jmp EXIT
		NEXT8:
		Cmp Dword Ptr Ss:[Ebp-0x340],0x08
		Jnz NEXT9
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1920
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],1080
		Jmp EXIT
		NEXT9:
		Cmp Dword Ptr Ss : [Ebp - 0x340], 0x09
			Mov Dword Ptr Ds : [MAIN_RESOLUTION_X],1280
			Mov Dword Ptr Ds : [MAIN_RESOLUTION_Y],720
		EXIT:
		Jmp [ResolutionSwitchAddress1]
	}
}

__declspec(naked) void ResolutionSwitchFont() // OK
{
	static DWORD ResolutionSwitchFontAddress1 = 0x006495CD;

	_asm
	{
		Mov Edx,Dword Ptr Ds:[MAIN_RESOLUTION_X]
		Mov Dword Ptr Ss:[Ebp-0xEDC],Edx
		Cmp Dword Ptr Ss:[Ebp-0xEDC],640
		Jnz NEXT1
		Mov Dword Ptr Ds:[MAIN_FONT_SIZE],0x0C
		Jmp EXIT
		NEXT1:
		Cmp Dword Ptr Ss:[Ebp-0xEDC],800
		Jnz NEXT2
		Mov Dword Ptr Ds:[MAIN_FONT_SIZE],0x0D
		Jmp EXIT
		NEXT2:
		Cmp Dword Ptr Ss:[Ebp-0xEDC],1024
		Jnz NEXT3
		Mov Dword Ptr Ds:[MAIN_FONT_SIZE],0x0E
		Jmp EXIT
		NEXT3:
		Cmp Dword Ptr Ss:[Ebp-0xEDC],1280
		Jnz NEXT4
		Mov Dword Ptr Ds:[MAIN_FONT_SIZE],0x0F
		Jmp EXIT
		NEXT4:
		Mov Dword Ptr Ds:[MAIN_FONT_SIZE],0x0F
		Push Float2000
		Push 0x007588B4
		Call [SetFloat]
		Add Esp, 0x08
		Push Float2000
		Push 0X007588C0
		Call [SetFloat]
		Add Esp, 0x08
		EXIT:
		Jmp [ResolutionSwitchFontAddress1]
	}
}


__declspec(naked) void ResolutionMoveList() // OK
{
	static DWORD ResolutionMoveListAddress1 = 0x004EED49; //
	static DWORD ResolutionMoveListAddress2 = 0x004EECAC; //  

	_asm
	{
		Mov Eax,Dword Ptr Ds:[MAIN_RESOLUTION_X]
		Mov Dword Ptr Ss:[Ebp-0x1B4],Eax
		Cmp Dword Ptr Ss:[Ebp-0x1B4],0x500
		Jbe EXIT
		Jmp [ResolutionMoveListAddress1]
		EXIT:
		Jmp [ResolutionMoveListAddress2]
	}
}

__declspec(naked) void ResolutionMoveList2() // OK
{
	static DWORD ResolutionMoveListAddress3 = 0x004EE693; //
	static DWORD ResolutionMoveListAddress4 = 0x004EE5F6; //

	_asm
	{
		Mov Eax,Dword Ptr Ds:[MAIN_RESOLUTION_X]
		Mov Dword Ptr Ss:[Ebp-0x1B4],Eax
		Cmp Dword Ptr Ss:[Ebp-0x1B4],0x500
		Jbe EXIT
		Jmp [ResolutionMoveListAddress3]
		EXIT:
		Jmp [ResolutionMoveListAddress4]
	}
}

//---------------------------- (004BADBA) ---------------------------------
unsigned __int8 ResolutionKanturu(int This)
{
	unsigned __int8 result; // eax@8
	int v2; // [sp+4h] [bp-8h]@1
	signed int i; // [sp+8h] [bp-4h]@8

	v2 = This;
	*(BYTE *)(This + 8) = 0;
	*(DWORD *)(This + 12) = 215;
	*(DWORD *)(This + 16) = 250;
	*(DWORD *)(This + 20) = (640 - *(DWORD *)(This + 12)) / 2;
	*(DWORD *)(This + 24) = (480 - *(DWORD *)(This + 16)) / 2 - 100;
	(*(void(__thiscall **)(int, signed int, signed int))(*(DWORD *)(This + 1244) + 8))(This + 1244, 50, 16);
	(*(void(__thiscall **)(int, signed int, signed int))(*(DWORD *)(v2 + 1380) + 8))(v2 + 1380, 50, 16);
	(*(void(__thiscall **)(int, signed int, signed int))(*(DWORD *)(v2 + 1516) + 8))(v2 + 1516, 50, 16);
	sub_416886(v2 + 1380, 225, 230);
	sub_416886(v2 + 1244, 295, 230);
	sub_416886(v2 + 1516, 365, 230);
	*(DWORD *)(v2 + 1236) = 0;
	result = sub_7394D0((unsigned __int8 *)(v2 + 36), 0, 0x12Cu);
	for (i = 0; i < 3; ++i)
		result = sub_7394D0((unsigned __int8 *)(v2 + 300 * i + 336), 0, 0x12Cu);
	return result;
}

//----- (0040AB03) --------------------------------------------------------
unsigned __int8 ResolutionCrywolf(int This)
{
	void *v1; // eax@7
	void *v2; // eax@7
	int v4; // [sp+4h] [bp-4h]@1

	v4 = This;
	*(BYTE *)(This + 4) = 0;
	*(DWORD *)(This + 16) = 215;
	*(DWORD *)(This + 20) = 250;
	*(DWORD *)(This + 8) = (640 - *(DWORD *)(This + 16)) / 2;
	*(DWORD *)(This + 12) = (480 - *(DWORD *)(This + 20)) / 2 - 100;
	v1 = pGetTextLine(pTextLineThis, 2147);
	(*(void(__thiscall **)(int, DWORD, void *))(*(DWORD *)(v4 + 24) + 44))(v4 + 24, 0, v1);
	(*(void(__thiscall **)(int, signed int, signed int))(*(DWORD *)(v4 + 24) + 8))(v4 + 24, 50, 16);
	sub_416886(v4 + 24, *(DWORD *)(v4 + 8) + *(DWORD *)(v4 + 16) / 3 - 25, 230);
	v2 = pGetTextLine(pTextLineThis, 1002);
	(*(void(__thiscall **)(int, DWORD, void *))(*(DWORD *)(v4 + 160) + 44))(v4 + 160, 0, v2);
	(*(void(__thiscall **)(int, signed int, signed int))(*(DWORD *)(v4 + 160) + 8))(v4 + 160, 50, 16);
	sub_416886(v4 + 160, *(DWORD *)(v4 + 8) + 2 * (*(DWORD *)(v4 + 16) / 3) - 25, 230);
	*(WORD *)(v4 + 296) = 0;
	*(DWORD *)(v4 + 300) = 0;
	return sub_7394D0((unsigned __int8 *)(v4 + 304), 0, 0x10u);
}