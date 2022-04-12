#include "StdAfx.h"

DWORD dwJewelUpgradeAllow_Buff;
DWORD dwJewelApplyAllow_Buff;

void InitItem() // OK
{
	SetCompleteHook(0xE9, 0x005F58AB, &FixBoxTexture);

	SetCompleteHook(0xFF,0x0060ABBB,&ItemModelLoad); //s1

	SetCompleteHook(0xFF,0x0060ABC0,&ItemTextureLoad); //s1

	SetCompleteHook(0xFF,0x005069A2,&GetItemColor); //s1

	SetCompleteHook(0xFF,0x005F8445,&GetItemColor); //s1
}

void InitJewel() // OK
{
	gToolKit.SetRange((LPVOID)0x005B8E6D, 7, ASM::NOP);
	gToolKit.SetJmp((LPVOID)0x005B8E6D, LoadJewelUpgrade); // 006318D2
	// ---
	gToolKit.SetRange((LPVOID)0x005C6CF2, 7, ASM::NOP);
	gToolKit.SetJmp((LPVOID)0x005C6CF2, LoadJewelApply); // 00644F73
}

void __declspec(naked) FixBoxTexture()
{
	static DWORD BoxTextureAddress1 = 0x005F58B7;
	_asm
	{
		MOV WORD PTR DS : [ESI + 2], 0x2231
		MOV WORD PTR DS : [ESI + 2], 0x2231
		JMP[BoxTextureAddress1]
	}
}

WORD iWingShowDurability_Buff;
__declspec(naked) void WingShowDurability()
{
	_asm
	{
		MOV iWingShowDurability_Buff, CX
	}

	if( iWingShowDurability_Buff < ITEMGET(12, 0)
		|| (iWingShowDurability_Buff >= ITEMGET(12, 36) && iWingShowDurability_Buff <= ITEMGET(12, 511))
		|| (iWingShowDurability_Buff >= ITEMGET(13, 0) && iWingShowDurability_Buff < ITEMGET(14, 0)) )
	{
		_asm
		{
			MOV ECX, 0x005A5FFF //00619DF3   > BA 01000000    MOV EDX,1


			JMP ECX
		}
	}

	_asm
	{
		MOV ECX, 0x005A5FEB //00619DD3 
		JMP ECX
	}
}

__declspec(naked) void WingShowAddons()
{
	static DWORD Jump = 0x005A531C;

	_asm
	{
		CMP CX,0x18C8
		JMP [Jump]
	}
}

void InitWing() // OK	
{
	SetCompleteHook(0xE9, 0x0050A674, &WingMakePreviewCharSet);
	SetOp((LPVOID)0x005A5FD6, (LPVOID)WingShowDurability, ASM::JMP);
	SetOp((LPVOID)0x005A5317, (LPVOID)WingShowAddons, ASM::JMP);
	SetOp((LPVOID)0x005A237B, (LPVOID)WingRemoveExcellent01, 0xE9);		// Remove nome e cor excelente
	SetOp((LPVOID)0x005A393E, (LPVOID)WingRemoveExcellent02, 0xE9);		// Remove nome e cor excelente
	SetOp((LPVOID)0x005F9DDB, (LPVOID)CustomWingFunction06, 0xE9);		// Remove a glow excelente
	SetOp((LPVOID)0x005EBDF6, (LPVOID)CustomWingFunction21, 0xE9);		// Remove brilho amarelo
	SetOp((LPVOID)0x005F8740, (LPVOID)CustomWingFunction22, 0xE9);		// Remove brilho amarelo
	SetOp((LPVOID)0x005F87BB, (LPVOID)CustomWingFunction23, 0xE9);		// Remove brilho amarelo
	SetOp((LPVOID)0x005C6D2F, (LPVOID)CustomWingFunction24, 0xE9);		// Remove brilho amarelo
	SetByte(0x005F872E, 0x40);
	SetByte(0x005F8736, 0x3F);

/*	MemorySet(0x0050343B,0x90,0x5);		 //transparencia sword, wings e armas/shields
	MemorySet(0x005034A4,0x90,0x5);		 //transparencia sword, wings e armas/shields
	MemorySet(0x00503559,0x90,0x5);		 //transparencia sword, wings e armas/shields
	MemorySet(0x00504A3E,0x90,0x5);		 //transparencia sword, wings e armas/shields
	MemorySet(0x00504ADE,0x90,0x5);		 //transparencia sword, wings e armas/shields
	MemorySet(0x00504B66,0x90,0x5);		 //transparencia sword, wings e armas/shields
	MemorySet(0x0050546D,0x90,0x5);		 //transparencia sword, wings e armas/shields
	MemorySet(0x00504BB1,0x90,0x5);*/	 //transparencia sword, wings e armas/shields

//	MemorySet(0x5F8640,0x90,0x1921); //deixa o char transparente
}

__declspec(naked) void WingMakePreviewCharSet()
{
	static DWORD WingMakePreviewCharSetAddress1 = 0x0050A6C5;
	static DWORD WingMakePreviewCharSetAddress2 = 0x0050A679;

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
		Mov Word Ptr Ds : [Esi + 0x2E8], Ax;
		Popad;
		Jmp[WingMakePreviewCharSetAddress1];
	EXIT:
		Popad;
		Mov al, Byte Ptr Ds : [Edi + 0x08];
		And al, 0x07;
		Jmp[WingMakePreviewCharSetAddress2];
	}
}

void __declspec(naked) CustomWingFunction06()
{
	static DWORD CustomWingFunction06_Offset01 = 0x005F9DE7;//0060AD50  |> 66:3D 301C     CMP AX,1C30
	static DWORD CustomWingFunction06_Offset02 = 0x005F9E4A;//0060ADB3  |> 8B45 20        MOV EAX,DWORD PTR SS:[EBP+20]
	
	_asm
	{
		CMP AX, MIN_WING_ITEMID2
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID2
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP AX, 0x1A03//1A12
			JL NEXT_CHECK1
			CMP AX, 0x1A09//1A18
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction06_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction06_Offset02]
	}
}

void __declspec(naked) WingRemoveExcellent01()
{
	static DWORD CustomWingFunction12_Offset01 = 0x005A2389;//005B0310  |> 66:81F9 1E1A   CMP CX,1A1E
	static DWORD CustomWingFunction12_Offset02 = 0x005A2390;//005B0317  |> 83FE 07        CMP ESI,7

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

void __declspec(naked) WingRemoveExcellent02()
{
	static DWORD CustomWingFunction13_Offset01 = 0x005A3970;//005B1A1A  |> 66:81F9 1F1A   CMP CX,1A1F
	static DWORD CustomWingFunction13_Offset02 = 0x005A394C;//005B19FD  |. 8B4D F0        MOV ECX,DWORD PTR SS:[EBP-10] ??? verificar



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

void __declspec(naked) CustomWingFunction21()
{
	static DWORD CustomWingFunction21_Offset01 = 0x005EBE0A;//005FB8C6  |> 8B45 84        MOV EAX,DWORD PTR SS:[EBP-7C]
	static DWORD CustomWingFunction21_Offset02 = 0x005EBE02;//005FB8BE  |. FF45 88        INC DWORD PTR SS:[EBP-78]

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

void __declspec(naked) CustomWingFunction22()
{
	static DWORD CustomWingFunction22_ItemIndex;
	static DWORD CustomWingFunction22_Offset01 = 0x005F892C;//0060971A
	//---
	static DWORD CustomWingFunction22_Offset02 = 0x005F878E;//006095E0  |> 8D81 E2E5FFFF  LEA EAX,DWORD PTR DS:[ECX-1A1E]
	static DWORD CustomWingFunction22_Offset03 = 0x005F8748;//0060958C  |. 0F84 88010000  JE main.0060971A



	_asm
	{
		MOV CustomWingFunction22_ItemIndex, ECX
	}

	if (CustomWingFunction22_ItemIndex >= MIN_WING_ITEMID2 && CustomWingFunction22_ItemIndex <= MAX_WING_ITEMID2)
	{
		__asm { JMP[CustomWingFunction22_Offset01] }
	}
	else
	{
		_asm
		{
			CMP ECX, 0x1A0E
			JG Next_Check
			JMP[CustomWingFunction22_Offset03]
			Next_Check:
			JMP[CustomWingFunction22_Offset02]
		}
	}

}

void __declspec(naked) CustomWingFunction23()
{
	static DWORD CustomWingFunction22_ItemIndex;
	static DWORD CustomWingFunction22_Offset01 = 0x005F892C;//0060971A
	//---
	static DWORD CustomWingFunction22_Offset02 = 0x005F885A;//006095E0  |> 8D81 E2E5FFFF  LEA EAX,DWORD PTR DS:[ECX-1A1E]
	static DWORD CustomWingFunction22_Offset03 = 0x005F87C7;//0060958C  |. 0F84 88010000  JE main.0060971A



	_asm
	{
		MOV CustomWingFunction22_ItemIndex, ECX
	}

	if (CustomWingFunction22_ItemIndex >= MIN_WING_ITEMID2 && CustomWingFunction22_ItemIndex <= MAX_WING_ITEMID2)
	{
		__asm { JMP[CustomWingFunction22_Offset01] }
	}
	else
	{
		_asm
		{
			CMP ECX, 0x1C21
			JG Next_Check
			JMP[CustomWingFunction22_Offset03]
			Next_Check:
			JMP[CustomWingFunction22_Offset02]
		}
	}

}

void __declspec(naked) CustomWingFunction24()
{
	static DWORD WingAllowJewel_Address01 = 0x005C6D3C; //0062F9A5 1.02c  81F9 07080000    CMP ECX,807
	static DWORD WingAllowJewel_Address02 = 0x005C6D35; //0062F99F 1.02c  32DB             XOR BL,BL

	_asm
	{
		CMP ESI,0x1A1E
		JLE EXIT1

		CMP ESI, MIN_WING_ITEMID
		JL EXIT2

		CMP ESI, MAX_WING_ITEMID
		JLE EXIT1

		JMP[WingAllowJewel_Address02]

		EXIT1:
		JMP[WingAllowJewel_Address01]

		EXIT2 :
		JMP[WingAllowJewel_Address02]
	}

}

void ItemModelLoad() // OK
{
	pInitModelData();

	for(int n=0;n < MAX_CUSTOM_JEWEL;n++)
	{
		if(gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemModel((gCustomJewel.m_CustomJewelInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomJewel.m_CustomJewelInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_WING;n++)
	{
		if(gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemModel((gCustomWing.m_CustomWingInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomWing.m_CustomWingInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		if(gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemModel((gCustomItem.m_CustomItemInfo[n].ItemIndex+ITEM_BASE_MODEL),((gCustomItem.m_CustomItemInfo[n].ItemIndex>=GET_ITEM(7,0)&&gCustomItem.m_CustomItemInfo[n].ItemIndex<GET_ITEM(12,0))?"Player\\":"Item\\"),gCustomItem.m_CustomItemInfo[n].ModelName,-1);
		}
	}
}

void ItemTextureLoad() // OK
{
	for(int n=0;n < MAX_CUSTOM_JEWEL;n++)
	{
		if(gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomJewel.m_CustomJewelInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomJewel.m_CustomJewelInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_WING;n++)
	{
		if(gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomWing.m_CustomWingInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomWing.m_CustomWingInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		if(gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomItem.m_CustomItemInfo[n].ItemIndex+ITEM_BASE_MODEL),((gCustomItem.m_CustomItemInfo[n].ItemIndex>=GET_ITEM(7,0)&&gCustomItem.m_CustomItemInfo[n].ItemIndex<GET_ITEM(12,0))?"Player\\":"Item\\"),gCustomItem.m_CustomItemInfo[n].ModelName,-1);
		}
	}

	pInitTextureData();
}

void LoadItemModel(int index,char* folder,char* name,int value)
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,char*,int))0x005FACA0)(index,path,name,value);
}

void LoadItemTexture(int index,char* folder,char* name,int value)
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,int,int,int))0x005FA860)(index,folder,0x2901,0x2600,0x01);
}

void GetItemColor(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e)
{
	if (gCustomItem.GetCustomItemColor((a - ITEM_BASE_MODEL), (float*)d) == 0)
	{
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD))0x005F6220)(a, b, c, d, e);
	}
}

__declspec(naked) void LoadJewelUpgrade()
{
	_asm
	{
		CMP SI, ITEM(14, 14)
		JE Exit
		// ---
		CMP SI, ITEM(14, 200)
		JE Exit
		// ---
		CMP SI, ITEM(14, 201)
		JE Exit
		// ---
		CMP SI, ITEM(14, 202)
		JE Exit
		// ---
		CMP SI, ITEM(14, 203)
		JE Exit
		// ---
		CMP SI, ITEM(14, 204)
		JE Exit
		// ---
		CMP SI, ITEM(14, 205)
		JE Exit
		// ---
		CMP SI, ITEM(14, 206)
		JE Exit
		// ---
		CMP SI, ITEM(14, 207)
		JE Exit
		// ---
		CMP SI, ITEM(14, 208)
		JE Exit
		// ---
		CMP SI, ITEM(14, 209)
		JE Exit
		// ---
		CMP SI, ITEM(14, 210)
		JE Exit
		// ---
		CMP SI, ITEM(14, 211)
		JE Exit
		// ---
		CMP SI, ITEM(14, 212)
		JE Exit
		// ---
		CMP SI, ITEM(14, 213)
		JE Exit
		// ---
		CMP SI, ITEM(14, 214)
		JE Exit
		// ---
		MOV dwJewelUpgradeAllow_Buff, 0x005B8E74 // 006318D9
		JMP dwJewelUpgradeAllow_Buff
		// ---
		Exit:
		MOV dwJewelUpgradeAllow_Buff, 0x005B8E92 // 00631913
		JMP dwJewelUpgradeAllow_Buff
	}
}

__declspec(naked) void LoadJewelApply()
{
	_asm
	{
		CMP DX, ITEM(14, 14)
		JE Exit
		// ---
		CMP DX, ITEM(14, 200)
		JE Exit
		// ---
		CMP DX, ITEM(14, 201)
		JE Exit
		// ---
		CMP DX, ITEM(14, 202)
		JE Exit
		// ---
		CMP DX, ITEM(14, 203)
		JE Exit
		// ---
		CMP DX, ITEM(14, 204)
		JE Exit
		// ---
		CMP DX, ITEM(14, 205)
		JE Exit
		// ---
		CMP DX, ITEM(14, 206)
		JE Exit
		// ---
		CMP DX, ITEM(14, 207)
		JE Exit
		// ---
		CMP DX, ITEM(14, 208)
		JE Exit
		// ---
		CMP DX, ITEM(14, 209)
		JE Exit
		// ---
		CMP DX, ITEM(14, 210)
		JE Exit
		// ---
		CMP DX, ITEM(14, 211)
		JE Exit
		// ---
		CMP DX, ITEM(14, 212)
		JE Exit
		// ---
		CMP DX, ITEM(14, 213)
		JE Exit
		// ---
		CMP DX, ITEM(14, 214)
		JE Exit
		// ---
		MOV dwJewelApplyAllow_Buff, 0x005C6CF9 // 00644F7A
		JMP dwJewelApplyAllow_Buff
		// ---
		Exit:
		MOV dwJewelApplyAllow_Buff, 0x005C6D04 // 00644F9A
		JMP dwJewelApplyAllow_Buff
	}
}
