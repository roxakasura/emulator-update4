#include "stdafx.h"
#include "Util.h"
#include "CustomWing.h"
#include "ItemManager.h"
#include "WingManager.h"

WORD iWingShowDurability_Buff;

void InitWing() // OK	
{
	SetCompleteHook(0xE9, 0x00532F09, &WingMakePreviewCharSet); //1.02r
	
	SetOp((LPVOID)0x005E1E04, (LPVOID)WingShowDurability, 0xE9);	//	season 2
	
	SetOp((LPVOID)0x005E1154, (LPVOID)WingShowAddons, 0xE9);
	
	SetOp((LPVOID)0x005729B1, (LPVOID)WingShowExcelenteOptions, 0xE9);

	SetOp((LPVOID)0x00572C11, (LPVOID)WingShowLuckOption, 0xE9);

	SetOp((LPVOID)0x00572C11, (LPVOID)WingShowLuckOption, 0xE9);

	SetOp((LPVOID)0x00572E62, (LPVOID)WingShowLifeOption, 0xE9);

	SetOp((LPVOID)0x005DDD77, (LPVOID)WingRemoveExcellent01, 0xE9);		// Remove nome e cor excelente

	SetOp((LPVOID)0x005DF32F, (LPVOID)WingRemoveExcellent02, 0xE9);		// Remove nome e cor excelente

	//SetOp((LPVOID)0x0062EE3D, (LPVOID)CustomWingFunction21, 0xE9);		// Remove brilho amarelo

	SetOp((LPVOID)0x00640A6A, (LPVOID)CustomWingFunction22, 0xE9);		// Remove brilho excelente

	//SetOp((LPVOID)0x006078DA, (LPVOID)CustomWingFunction24, 0xE9);		// Remove brilho amarelo

	//MemorySet(0x00640B49,0x90,0x5); antilag
	//
	//MemorySet(0x00640ACD,0x90,0x5);
}


void __declspec(naked) CustomWingFunction24()
{
	static DWORD WingAllowJewel_Address01 = 0x006078E7; //0062F9A5 1.02c  81F9 07080000    CMP ECX,807
	static DWORD WingAllowJewel_Address02 = 0x006078E0; //0062F99F 1.02c  32DB             XOR BL,BL

	_asm
	{
		CMP ECX,0x1A1E
		JLE EXIT1

		CMP ECX, MIN_WING_ITEMID
		JL EXIT2

		CMP ECX, MAX_WING_ITEMID
		JLE EXIT1

		JMP[WingAllowJewel_Address02]

		EXIT1:
		JMP[WingAllowJewel_Address01]

		EXIT2 :
		JMP[WingAllowJewel_Address02]
	}

}

DWORD iWingExcGlow_Buff;
void __declspec(naked) CustomWingFunction22()
{
	_asm
	{
		MOV iWingExcGlow_Buff, EAX
	}

	if(iWingExcGlow_Buff == ITEM2(12, 6) ||
		(iWingExcGlow_Buff >= ITEM2(12, 36) && iWingExcGlow_Buff <= ITEM2(12, 511)))
	{
		_asm
		{
			MOV EAX, 0x00640AD9 //0059841C
			JMP EAX
		}
	}

	_asm
	{
		MOV EAX, 0x00640A70 //00598495  
		JMP EAX
	}
}

void __declspec(naked) CustomWingFunction21()
{
	static DWORD CustomWingFunction21_Offset01 = 0x0062EE51;//005FB8C6  |> 8B45 84        MOV EAX,DWORD PTR SS:[EBP-7C]
	static DWORD CustomWingFunction21_Offset02 = 0x0062EE49;//005FB8BE  |. FF45 88        INC DWORD PTR SS:[EBP-78]

	_asm
	{
		CMP AX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID
		JG NEXT_CHECK
		JMP[CustomWingFunction21_Offset02]

		NEXT_CHECK:
		CMP AX, 0x1800
			JL NEXT_CHECK2
			CMP AX, 0x1806
			JG NEXT_CHECK2
			JMP[CustomWingFunction21_Offset02]

			NEXT_CHECK2 :
			JMP[CustomWingFunction21_Offset01]
	}
}

void __declspec(naked) WingRemoveExcellent02()
{
	static DWORD CustomWingFunction13_Offset01 = 0x005DF361;//005B1A1A  |> 66:81F9 1F1A   CMP CX,1A1F
	static DWORD CustomWingFunction13_Offset02 = 0x005DF33D;//005B19FD  |. 8B4D F0        MOV ECX,DWORD PTR SS:[EBP-10] ??? verificar

	_asm
	{
		CMP CX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID
		JG NEXT_CHECK
		JMP[CustomWingFunction13_Offset02]

		NEXT_CHECK:
		CMP CX, 0x1800
			JL NEXT_CHECK2
			CMP CX, 0x1806
			JG NEXT_CHECK2
			JMP[CustomWingFunction13_Offset02]

			NEXT_CHECK2 :
			JMP[CustomWingFunction13_Offset01]
	}
}

void __declspec(naked) WingRemoveExcellent01()
{
	static DWORD CustomWingFunction12_Offset01 = 0x005DDD85;//005B0310  |> 66:81F9 1E1A   CMP CX,1A1E
	static DWORD CustomWingFunction12_Offset02 = 0x005DDD8C;//005B0317  |> 83FE 07        CMP ESI,7

	_asm
	{
		CMP CX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP CX, 0x1800
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction12_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction12_Offset02]
	}
}


DWORD iWingAddLifeOption_Buff;
__declspec(naked) void WingShowLifeOption()
{
	_asm
	{
		MOV iWingAddLifeOption_Buff, EAX
	}

	if(iWingAddLifeOption_Buff == ITEMGET(12, 6) ||
		(iWingAddLifeOption_Buff >= ITEMGET(12, 36) && iWingAddLifeOption_Buff <= ITEMGET(12, 511)))
	{
		_asm
		{
			MOV EAX, 0x00572E68 //0059841C
			JMP EAX
		}
	}

	_asm
	{
		MOV EAX, 0x00572E85 //00598495  
		JMP EAX
	}
}


DWORD iWingAddLuckOption_Buff;
__declspec(naked) void WingShowLuckOption()
{
	_asm
	{
		MOV iWingAddLuckOption_Buff, EAX
	}

	if((iWingAddLuckOption_Buff >= ITEMGET(12, 0)  && iWingAddLuckOption_Buff <= ITEMGET(12, 6))	
		||(iWingAddLuckOption_Buff >= ITEMGET(12, 36) && iWingAddLuckOption_Buff <= ITEMGET(12, 511)))
	{
		_asm
		{
			MOV EAX, 0x00572C1D//00597E1F
			JMP EAX
		}
	}

	_asm
	{
		MOV EAX, 0x00572C2E //00597E3E  |> 8B4D 08        MOV ECX,DWORD PTR SS:[EBP+8]
		JMP EAX
	}
}

__declspec(naked) void WingShowExcelenteOptions()
{
	static DWORD Jump = 0x005729B6;

	_asm
	{
		CMP CX,0x18C8
		JMP [Jump]
	}
}

__declspec(naked) void WingShowAddons()
{
	static DWORD Jump = 0x005E1159;

	_asm
	{
		CMP CX,0x18C8
		JMP [Jump]
	}
}

__declspec(naked) void WingShowDurability()
{
	_asm
	{
		MOV iWingShowDurability_Buff, CX
	}

	if( iWingShowDurability_Buff < ITEMGET(12, 0)
		|| (iWingShowDurability_Buff >= ITEMGET(12, 36) && iWingShowDurability_Buff <= ITEMGET(12, 225))
		|| (iWingShowDurability_Buff >= ITEMGET(13, 0) && iWingShowDurability_Buff < ITEMGET(14, 0)) )
	{
		_asm
		{
			MOV ECX, 0x005E1E2A //00619DF3   > BA 01000000    MOV EDX,1


			JMP ECX
		}
	}

	_asm
	{
		MOV ECX, 0x005E1E19 //00619DD3 
		JMP ECX
	}
}

__declspec(naked) void WingMakePreviewCharSet()
{
	static DWORD WingMakePreviewCharSetAddress1 = 0x00532F5A;
	static DWORD WingMakePreviewCharSetAddress2 = 0x00532F0E;

	_asm
	{
		Pushad;
		Mov Ecx, Dword Ptr Ss : [Ebp + 0x0C];
		Movzx Edx, Byte Ptr Ds : [Ecx + 0x10];
		Sar Edx, 0x01;
		And Edx, 0x0F;
		Test Edx, Edx;
		Je EXIT;
		Mov Edx, Dword Ptr Ss : [Ebp + 0x0C];
		Movzx Ecx, Byte Ptr Ds : [Edx + 0x10];
		Sar Ecx, 0x01;
		And Ecx, 0x0F;
		Sub Ecx, 0x01;
		Push Ecx;
		Lea Ecx, gCustomWing;
		Call[CCustomWing::CheckCustomWing];
		Test Eax, Eax;
		Je EXIT;
		Mov Ecx, Dword Ptr Ss : [Ebp + 0x0C];
		Movzx Eax, Byte Ptr Ds : [Ecx + 0x10];
		Sar Eax, 0x01;
		And Eax, 0x0F;
		Sub Eax, 0x01;
		Push Eax;
		Lea Ecx, gCustomWing;
		Call[CCustomWing::GetCustomWingItem];
		Add Eax, ITEM_BASE_MODEL;
		Mov Word Ptr Ds : [Esi + 0x32C], Ax;
		Popad;
		Jmp[WingMakePreviewCharSetAddress1];
	EXIT:
		Popad;
		Mov al, Byte Ptr Ds : [Edi + 0x08];
		And al, 0x07;
		Jmp[WingMakePreviewCharSetAddress2];
	}
}
