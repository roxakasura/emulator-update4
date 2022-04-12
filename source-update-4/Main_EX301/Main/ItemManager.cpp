#include "stdafx.h"
#include "ItemManager.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "StaticEffect.h"
#include "Util.h"
#include "User.h"
#include "ToolKit.h"
#include "Protect.h"

WORD	WingsAddExcellentStatus_Lv2_Pointer;
DWORD	WingsAddExcellentStatus_Lv2_Buff;
DWORD	iWingAddLifeOption_Buff;
WORD	iWingShowDurability_Buff;
WORD	iWingEnableMoveKanturuEvent2_Buff;
DWORD	iWingEnableMoveKanturuEvent_Buff;
DWORD   iWingCheckIndex3_buff;
DWORD	iWingEnableMoveIcarus_Buff;
DWORD	iWingEnableMoveIcarus2_Buff;
DWORD	iWingHideExcellentGlow_Buff;
DWORD	iWingHideExcellentGlow_Buff2;
int		ID = 0;

void InitItem() // OK
{
	SetCompleteHook(0xFF,0x0063E91A,&ItemModelLoad); 

	SetCompleteHook(0xFF,0x0063E92F,&ItemTextureLoad); 

	SetCompleteHook(0xFF,0x0052870B,&GetItemColor);

	SetCompleteHook(0xFF,0x0062346B,&GetItemColor);

	if (gProtect.m_MainInfo.ItemLevel15 == 1)
	{
		//===================================================================================
		// fumaça dos sets fixada em + 15
		//===================================================================================
		SetByte((LPVOID)0x00518D4F, 0x0D); //
		SetByte((LPVOID)0x00518D85, 0x0D); //
		//SetByte((LPVOID)0x0053BF6F, 0x0F);

		//===================================================================================
		// extensão até + 16
		//===================================================================================
		SetByte((LPVOID)0x00627BDE, 0x10); //

		//===================================================================================
		// extensão ate + 15 defesa, danos, etc..., alteração da variavel até + 11
		//===================================================================================
		SetByte((LPVOID)(0x005357DE + 3), 0x0B);
		SetByte((LPVOID)(0x005357E4 + 3), 0x0B);
		SetByte((LPVOID)(0x0053580D + 2), 0x0B);

		SetByte((LPVOID)(0x00535909 + 3), 0x0B);
		SetByte((LPVOID)(0x0053590F + 3), 0x0B);
		SetByte((LPVOID)(0x00535938 + 2), 0x0B);

		SetByte((LPVOID)(0x00535A2B + 3), 0x0B);
		SetByte((LPVOID)(0x00535A31 + 3), 0x0B);
		SetByte((LPVOID)(0x00535A57 + 2), 0x0B);

		SetByte((LPVOID)(0x00535B3C + 3), 0x0B);
		SetByte((LPVOID)(0x00535B42 + 3), 0x0B);
		SetByte((LPVOID)(0x00535B68 + 2), 0x0B);

		SetByte((LPVOID)(0x00535CE5 + 3), 0x0B);
		SetByte((LPVOID)(0x00535CEB + 3), 0x0B);

		SetByte((LPVOID)(0x00535D23 + 3), 0x0B);
		SetByte((LPVOID)(0x00535D29 + 3), 0x0B);

		SetByte((LPVOID)(0x00535D6B + 3), 0x0B);
		SetByte((LPVOID)(0x00535D71 + 3), 0x0B);

		SetByte((LPVOID)(0x00535D99 + 3), 0x0B);
		SetByte((LPVOID)(0x00535D9F + 3), 0x0B);
		SetByte((LPVOID)(0x00535DE4 + 2), 0x0B);
		SetByte((LPVOID)(0x00535E50 + 2), 0x0B);

		SetByte((LPVOID)(0x00535EC7 + 3), 0x0B);
		SetByte((LPVOID)(0x00535ECD + 3), 0x0B);
		SetByte((LPVOID)(0x00535EF6 + 2), 0x0B);
	}

	//MemorySet(0x5B608C,0x90, 70);
	//SetCompleteHook(0xE9, 0x5B608C, &RenaDescFix);
	
	MemorySet(0x624491,0x90, 12);
	SetCompleteHook(0xE9, 0x624491, &GmBoxEffect);

	SetCompleteHook(0xE9, 0x0061B298, &FixBoxTexture);

//	SetOp((LPVOID)0x005EAD80, (LPVOID)CustomBuddlePack, ASM::CALL); //proximos updates
}

DWORD ItemLevelBox;

void __declspec(naked) FixBoxTexture()
{
	static DWORD BoxTextureAddress1 = 0x0061B2A4;
	static DWORD BoxTextureAddress2 = 0x0061B319;
	_asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x08]
		MOV EDX, DWORD PTR DS : [ECX + 0x02]
		SAR EDX, 0x03
		MOV DWORD PTR SS : [EBP - 0x40], EDX
		MOV ItemLevelBox, EDX
	}

	switch (ItemLevelBox)
	{
	case 1:
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0x0C]
			MOV WORD PTR DS : [EAX + 0x02], 0x22F1
			Jmp[BoxTextureAddress2]
		}
		break;
	case 2:
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0x0C]
			MOV WORD PTR DS : [EAX + 0x02], 0x22F2
			Jmp[BoxTextureAddress2]
		}
		break;
	case 3:
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0x0C]
			MOV WORD PTR DS : [EAX + 0x02], 0x22F3
			Jmp[BoxTextureAddress2]
		}
		break;
	case 5:
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0x0C]
			MOV WORD PTR DS : [EAX + 0x02], 0x22F5
			Jmp[BoxTextureAddress2]
		}
		break;
	case 6:
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0x0C]
			MOV WORD PTR DS : [EAX + 0x02], 0x22F6
			Jmp[BoxTextureAddress2]
		}
		break;
	case 8:
	case 9:
	case 0xA:
	case 0xB:
	case 0xC:
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0x0C]
			MOV WORD PTR DS : [EAX + 0x02], 0x22F7
			Jmp[BoxTextureAddress2]
		}
		break;
	case 0xD:
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0x0C]
			MOV WORD PTR DS : [EAX + 0x02], 0x22F3
			Jmp[BoxTextureAddress2]
		}
	case 0xE:
	case 0xF:
		_asm
		{
			MOV EAX, DWORD PTR SS : [EBP - 0x0C]
			MOV WORD PTR DS : [EAX + 0x02], 0x22F2
			Jmp[BoxTextureAddress2]
		}
		break;
	default:
		_asm
		{
			Jmp[BoxTextureAddress2]
		}
		break;
	}
}

BOOL bGmBoxEffect_Switcher;

__declspec(naked) void GmBoxEffect()
{
	static DWORD dwPointer;
	// ----
	static DWORD dwAllow = 0x62449D;
	static DWORD dwReturn = 0x624562;
	// ----
	bGmBoxEffect_Switcher = FALSE;
	// ----
	_asm
	{
		MOV dwPointer, ECX
	}
	// ----
	if (dwPointer == ObjectId(13, 54) || dwPointer == ObjectId(14, 52) || dwPointer == ObjectId(14, 68))
	{
		bGmBoxEffect_Switcher = TRUE;
	}
	// ----
	if (bGmBoxEffect_Switcher == TRUE)
	{
		_asm
		{
			JMP dwAllow
		}
	}
	else
	{
		_asm
		{
			JMP dwReturn
		}
	}
}

__declspec(naked) void RenaDescFix()
{
	static DWORD dwGetTextLine = 0x402260;
	static DWORD dwAnotherCall = 0x739528;
	// ----
	static DWORD dwTextCall = 0x5B60EA;
	static DWORD dwTextProp = 0x5B60CF;
	// ----
	static DWORD dwReturnLoad = 0x5B60D2;
	// ----__declspec(naked) void
	_asm
	{
		CMP CX, ItemId(14, 21)							//Rena
		JNZ NextItem1
		CMP EDI, 0x3									//Rena +3 = Sign of Lord
		MOV DWORD PTR DS : [EAX * 4 + 0x7641DD4], EBX
		JNZ TextProp
		PUSH 0x50B										//Text.bmd line Number
		MOV ECX, 0x0750DF88
		CALL dwGetTextLine
		PUSH EAX
		MOV EAX, DWORD PTR DS : [0x7672F38]
		LEA EAX, [EAX + EAX * 4]
		LEA ECX, [EAX + EAX * 4]
		LEA EDX, [0x7640C48 + ECX * 4]
		PUSH EDX
		CALL dwAnotherCall
		MOV EAX, DWORD PTR DS : [0x7672F38]
		ADD ESP, 0x8
		INC EAX
		JMP dwTextCall

		NextItem1 :
		CMP CX, ItemId(14, 21)									//Rena
			JNZ NextItem2
			CMP EDI, 0x1										//Rena +1 = Stone
			MOV DWORD PTR DS : [EAX * 4 + 0x7641DD4], EBX
			JNZ TextProp
			PUSH 0x508											//Text.bmd line Number
			MOV ECX, 0x0750DF88
			CALL dwGetTextLine
			PUSH EAX
			MOV EAX, DWORD PTR DS : [0x7672F38]
			LEA EAX, [EAX + EAX * 4]
			LEA ECX, [EAX + EAX * 4]
			LEA EDX, [0x7640C48 + ECX * 4]
			PUSH EDX
			CALL dwAnotherCall
			MOV EAX, DWORD PTR DS : [0x7672F38]
			ADD ESP, 0x8
			INC EAX
			JMP dwTextCall

			NextItem2 :
		CMP CX, ItemId(14, 21)										//Rena
			JNZ NextLoad											//Return main.exe normal load
			CMP EDI, 0x0											//Rena +0 = Rena
			MOV DWORD PTR DS : [EAX * 4 + 0x7641DD4], EBX
			JNZ TextProp
			PUSH 0x6D7												//Text.bmd line Number
			MOV ECX, 0x0750DF88
			CALL dwGetTextLine
			PUSH EAX
			MOV EAX, DWORD PTR DS : [0x7672F38]
			LEA EAX, [EAX + EAX * 4]
			LEA ECX, [EAX + EAX * 4]
			LEA EDX, [0x7640C48 + ECX * 4]
			PUSH EDX
			CALL dwAnotherCall
			MOV EAX, DWORD PTR DS : [0x7672F38]
			ADD ESP, 0x8
			INC EAX
			JMP dwTextCall

			TextProp :
		JMP dwTextProp;

	NextLoad:
		JMP dwReturnLoad;
	}
}

BYTE CustomBuddlePack(int index)
{
	if (*(WORD*)index == 0x181E)
	{
		return 2;
	}
	else if (*(WORD*)index == 0x181F)
	{
		return 3;
	}
	else if (*(WORD*)index == 0x1C0D)
	{
		return 0;
	}
	else if (*(WORD*)index == 0x1C0E)
	{
		return 1;
	}
	else if (*(WORD*)index >= GET_ITEM(14, 200) && *(WORD*)index <= GET_ITEM(14, 210))
	{
		return 2;
	}

	return -1;
}
__declspec(naked) void WingHideExcellentGlow()
{
	_asm
	{
		MOV iWingHideExcellentGlow_Buff2, EAX
	}


	if (iWingHideExcellentGlow_Buff2 == 7335 || iWingHideExcellentGlow_Buff2 >= ITEM2(12, 36) && iWingHideExcellentGlow_Buff2 <= ITEM2(12, 512))
	{
		_asm
		{
			MOV ECX, 0x00627EAD //00434FBD 
			JMP ECX
		}
	}
	else
	{
		_asm
		{
			MOV ECX, 0x00627DEB//00434F90
			JMP ECX
		}
	}


}

void InitWing() // OK
{
//	BYTE WingsHideLeveltGlow[] = { 0xB8 };
//	WriteMemory( (PVOID) 0x00623BFF+6,& WingsHideLeveltGlow, sizeof( WingsHideLeveltGlow ) );

	SetCompleteHook(0xE9,0x00627DE0,&WingHideExcellentGlow);

	SetCompleteHook(0xE9,0x0052CD2A,&WingMakePreviewCharSet);

	SetCompleteHook(0xE9,0x00623A8E,&WingDisableLevelGlow);

	SetCompleteHook(0xE9,0x005B557D,&WingSetIncDamage);

	SetCompleteHook(0xE9,0x005B55DE,&WingSetDecDamage);

	SetCompleteHook(0xE9,0x00526168,&WingSetModelType);

	SetCompleteHook(0xE9,0x004EB3E4,&WingCheckIndex1);

	SetCompleteHook(0xE9,0x005355D9,&WingCheckIndex3); //  1.04j 005355D3 ok testado duvida

	//SetCompleteHook(0xE9,0x00535FDD,&WingCheckIndex4);  //  1.04j 00535FDD ok testado duvida

	SetCompleteHook(0xE9,0x0053697C,&WingCheckIndex5); //  1.04j 0053698A ok testado // 24wings

	SetCompleteHook(0xE9,0x00537B5F,&WingCheckIndex6); //  1.04j 00537B6D ok testado // 24wings

	SetCompleteHook(0xE9,0x00538A64,&WingCheckIndex7); //  1.04j 00538A64 ok testado

	SetCompleteHook(0xE9,0x00538BC8,&WingCheckIndex8); //  1.04j 00538BC8 ok testado

	SetCompleteHook(0xE9,0x00538D00,&WingCheckIndex9); //  1.04j 00538D00 ok testado

	SetCompleteHook(0xE9,0x0058DA5E,&WingCheckIndex10); //  1.04j 0058DA5E ok testado
	
	SetCompleteHook(0xE9,0x005B05D1,&WingCheckIndex11); //  1.04j 005B05D1 ok testado
	
	SetCompleteHook(0xE9,0x005B15F1,&WingCheckIndex12); // 1.04j 005B15F8  ok testado // 24wings

	SetCompleteHook(0xE9,0x005B2293,&WingCheckIndex13); // 1.04j 005B2293 ok testado
	
	SetCompleteHook(0xE9,0x005B3373,&WingCheckIndex14);  //  1.04j 005B3309 ok testado

	SetCompleteHook(0xE9,0x005B7F0D,&WingCheckIndex16);  // 1.04j 005B7F0D ok testado

	SetCompleteHook(0xE9,0x005BCD55,&WingCheckIndex15); //ACHEEEEI	

	SetCompleteHook(0xE9,0x005B8467,&WingCheckIndex17);  // 1.04j 005B8467 ok testado

	SetCompleteHook(0xE9,0x005DEB2F,&WingCheckIndex18);  // 1.04j 005DEB2F ok testado

	SetCompleteHook(0xE9,0x004BBAD6,&WingCheckIndex20); // 1.04j  004BBAD6

	SetCompleteHook(0xE9,0x004EF130,&WingCheckIndex21); // 1.04j 004EF130 ok testado Move list

	SetCompleteHook(0xE9,0x005DDEED,&WingCheckIndex23); // 1.04j 005DDEED  ok testado JewelsInsert

	SetCompleteHook(0xE9,0x0051CC28,&WingCheckModelIndex1); // 1.04j 0051CC28 ok testado

	//SetCompleteHook(0xE9,0x005BBAB0,&WingCheckModelIndex2); // 1.04j 005BBAB0 ok testado ??

	SetCompleteHook(0xE9,0x00627DFA,&WingCheckModelIndex3); // 1.04j 00627DFA ok testado
	
	SetCompleteHook(0xE9,0x00536775,&WingsShowAdditionals); //100% - Feita Por Denis
	
//	SetCompleteHook(0xE9,0x005363D0,&WingsShowAdditionals); //100% - Feita Por Denis asas lv2 opt
																   
	SetCompleteHook(0xE9,0x00536F25,&WingAddLifeOption); //100% - Feita Por Denis
																   
	SetCompleteHook(0xE9,0x004EE96D,&WingEnableMoveIcarus); //100% - Feita Por Denis
																   
	SetCompleteHook(0xE9,0x004EF159,&WingEnableMoveIcarus2); //100% - Feita Por Denis
	
	SetCompleteHook(0xE9,0x005B6102,&WingShowDurability); //100% - Feita Por Denis
	
	SetCompleteHook(0xE9,0x004BBAFF,&WingEnableMoveKanturuEvent); //100% - Feita Por Denis

	SetCompleteHook(0xE9,0x004BC085,&WingEnableMoveKanturuEvent2); //100% - Feita Por Denis
}

void InitJewel() // OK
{
	SetCompleteHook(0xE9,0x00537FCD,&JewelSetSalePrice);

	SetCompleteHook(0xE9,0x005DDE84,&JewelInsertTwo);

	SetCompleteHook(0xE9,0x005CC9C6,&JewelInsertOne);
}

void ItemModelLoad() // OK
{
	((void(*)())0x0062D7CC)();

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

	((void(*)())0x0062EAEB)();
}

void LoadItemModel(int index,char* folder,char* name,int value)
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,char*,int))0x0062B803)(index,path,name,value);
}

void LoadItemTexture(int index,char* folder,char* name,int value)
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,int,int,int))0x0062B387)(index,folder,0x2901,0x2600,0x01);
}

void GetItemColor(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e)
{
	if (gCustomItem.GetCustomItemColor((a - ITEM_BASE_MODEL), (float*)d) == 0)
	{
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD))0x0061C0AF)(a, b, c, d, e);
	}
}

__declspec(naked) void WingMakePreviewCharSet() // OK
{
	static DWORD WingMakePreviewCharSetAddress1 = 0x0052CD6C; //1.04j 0052CD6C testado
	static DWORD WingMakePreviewCharSetAddress2 = 0x0052CD33; //1.04j 0052CD33 testado

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x10]
		Sar Edx,0x01
		And Edx,0x0F
		Test Edx,Edx
		Je EXIT
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Ecx,Byte Ptr Ds:[Eax+0x10]
		Sar Ecx,0x01
		And Ecx,0x0F
		Sub Ecx,0x01
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWing]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Eax,Byte Ptr Ds:[Edx+0x10]
		Sar Eax,0x01
		And Eax,0x0F
		Sub Eax,0x01
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingItem]
		Add Eax,ITEM_BASE_MODEL
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Mov Word Ptr Ds:[Edx+0x330],Ax
		Jmp [WingMakePreviewCharSetAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		And Ecx,0xFF
		Jmp [WingMakePreviewCharSetAddress2]
	}
}

__declspec(naked) void WingDisableLevelGlow() // OK
{
	static DWORD WingDisableLevelGlowAddress1 = 0x0062404C; // 1.04j 0062404C
	static DWORD WingDisableLevelGlowAddress2 = 0x00623A97; // 1.04j 00623A97

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x0C]
		MOV DWORD PTR SS:[EBP-0x454],ECX
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Dword Ptr Ss:[Ebp-0x08],0x00
		Jmp [WingDisableLevelGlowAddress1]
		EXIT:
		Jmp [WingDisableLevelGlowAddress2]
	}
}

__declspec(naked) void WingSetIncDamage() // OK
{
	static DWORD WingSetIncDamageAddress1 = 0x005B5597; // 1.04j 005B5597
	static DWORD WingSetIncDamageAddress2 = 0x005B5582; // 1.04j 005B558D

	_asm
	{
		Movsx Ecx,Cx
		Push Ecx
		Push Ebp
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Ebp
		Pop Ecx
		Push Ebp
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingIncDamage]
		Mov Esi,Eax
		Jmp [WingSetIncDamageAddress1]
		EXIT:
		Pop Ebp
		Pop Ecx
		Cmp Ecx,0x1824
		Jmp [WingSetIncDamageAddress2]
	}
}

__declspec(naked) void WingSetDecDamage() // OK
{
	static DWORD WingSetDecDamageAddress1 = 0x005B55EE; // 1.04j 005B55EE
	static DWORD WingSetDecDamageAddress2 = 0x005B55E8; // 1.04j 005B55E8

	_asm
	{
		MOV DWORD PTR DS:[0x7672F38],EAX
		Push Edx
		Push Ebp
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Ebp
		Pop Edx
		Push Ebp
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingDecDamage]
		Mov Eax,Eax
		Jmp [WingSetDecDamageAddress1]
		EXIT:
		Pop Ebp
		Pop Edx
		CMP WORD PTR DS:[ECX],0x1828
		Jmp [WingSetDecDamageAddress2]
	}
}

__declspec(naked) void WingSetModelType() // OK
{
	static DWORD WingSetModelTypeAddress1 = 0x00526176; // 1.04j00526176
	static DWORD WingSetModelTypeAddress2 = 0x00526172; // 1.04j 00526172

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp-0x394]
		Sub Edx,ITEM_BASE_MODEL
		Push 1
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByModelType]
		Test Eax,Eax
		Je EXIT
		Jmp [WingSetModelTypeAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x394],0x1AB1
		Jmp [WingSetModelTypeAddress2]
	}
}

__declspec(naked) void WingCheckIndex1() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x004EB402; //1.04j  004EB402
	static DWORD WingCheckIndexAddress2 = 0x004EB3EB; //1.04j  004EB3EB

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x14]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x14],0x1C25
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex3() // OK
{
	_asm
	{
		MOV iWingCheckIndex3_buff, EAX
	}


	if (iWingCheckIndex3_buff <= 6184 || iWingCheckIndex3_buff >= ITEM(12, 36) && iWingCheckIndex3_buff <= ITEM(12, 512))
	{
		_asm
		{
			MOV ECX, 0x00535622 //00434FBD 
			JMP ECX
		}
	}
	else
	{
		_asm
		{
			MOV ECX, 0x005355E0//00434F90
			JMP ECX
		}
	}
}

__declspec(naked) void WingCheckIndex4() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00536014; //1.04j
	static DWORD WingCheckIndexAddress2 = 0x00535FE3; //1.04j

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex5() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00536997; //1.04j 00536997
	static DWORD WingCheckIndexAddress2 = 0x00536982; //1.04j 00536990

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex6() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00537B7A; //1.04j 00537B7A
	static DWORD WingCheckIndexAddress2 = 0x00537B65; //1.04j 00537B73

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex7() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00538A72; //1.04j 00538A72
	static DWORD WingCheckIndexAddress2 = 0x00538A6A; //1.04j 00538A6A

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex8() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00538BD6;  //1.04j 00538BD6
	static DWORD WingCheckIndexAddress2 = 0x00538BCE;  //1.04j 00538BCE

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex9() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00538D11;  //1.04j 00538D11
	static DWORD WingCheckIndexAddress2 = 0x00538D06;  //1.04j 00538D06

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex10() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0058DB4B;  //1.04j 0058DB4B
	static DWORD WingCheckIndexAddress2 = 0x0058DA65;  //1.04j 0058DA65

	_asm
	{
		Mov Edx,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Movsx Ecx,Word Ptr Ds:[Edx+0x0D94]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Movsx Ecx,Word Ptr Ds:[Edx+0x0D94]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex11() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005B05E7; //1.04j 005B05E7
	static DWORD WingCheckIndexAddress2 = 0x005B05D6; //1.04j 005B05D6

	_asm
	{
		Movsx Edx,Dx
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Edx
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop edx
		Cmp edx,0x1828
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex12() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005B15FF; // 1.04j 005B15FF
	static DWORD WingCheckIndexAddress2 = 0x005B15F6; // 1.04j 005B15FD

	_asm
	{
		Mov Edx,Eax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x1824
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex13() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005B2299; // 1.04j 005B2299
	static DWORD WingCheckIndexAddress2 = 0x005B22BD; // 1.04j 005B22BD

	_asm
	{
		Movsx Edx,Ax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop eax
		Cmp eax,0x1828
		Jg NEXT
		Jmp [WingCheckIndexAddress1]
		NEXT:
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex14() // OK
{
	static DWORD IsWingExcellentName;
	static DWORD WingCheck14Address1 = 0x005B3394; // 1.04j
	static DWORD WingCheck14Address2 = 0x005B3388; // 1.04j

	_asm
	{
		MOV IsWingExcellentName, EAX
	}

	if (IsWingExcellentName==ITEM(13,37)) //mantém a condição original para fenrir
	{
        _asm 
		{
			jmp WingCheck14Address1
		}
	}
	
	if (IsWingExcellentName>=ITEM(12,200) && IsWingExcellentName<=ITEM(12,400)) //adicionado uma condição onde remove name excellent wings
	{
        _asm 
		{
			jmp WingCheck14Address2
		}
	}
	else
	{
		_asm
		{
			jmp WingCheck14Address1 //retorna pro valor original caso não passe por nenhuma das condições
		}
	}
}

__declspec(naked) void WingCheckIndex16() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005B7F13; // 1.04j 005B7F13
	static DWORD WingCheckIndexAddress2 = 0x005B7F2E; // 1.04j 005B7F2E

	_asm
	{
		Movsx Edx,Ax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		CMP EAX,0x1828
		Jg NEXT
		Jmp [WingCheckIndexAddress1]
		NEXT:
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex17() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005B85A6; // 1.04j 005B85A6
	static DWORD WingCheckIndexAddress2 = 0x005B846C; // 1.04j 005B846C

	_asm
	{
		Movsx Edx,Cx
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Ecx
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Ecx
		CMP ECX,0x1828
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex18() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005DEBBE; // 1.04j 005DEBBE
	static DWORD WingCheckIndexAddress2 = 0x005DEB39; // 1.04j 005DEB39

	_asm
	{
		Movsx Edx,Ax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		CMP EAX,0x1828
		Jle NEXT
		Jmp [WingCheckIndexAddress2]
		NEXT:
		Jmp [WingCheckIndexAddress1]
	}
}

__declspec(naked) void WingCheckIndex20() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x004BBB33;
	static DWORD WingCheckIndexAddress2 = 0x004BBADB;

	_asm
	{
		Mov Edx,Edx
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Edx
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x1828
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex21() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x004EF18B;
	static DWORD WingCheckIndexAddress2 = 0x004EF135;

	_asm
	{
		Mov Edx,Eax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x1828
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex23() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005DDEFB;
	static DWORD WingCheckIndexAddress2 = 0x005DDEF3;

	_asm
	{
		Mov Edx,Ecx
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Ecx
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Ecx
		Cmp Ecx,0x1828
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckModelIndex1() // OK
{
	static DWORD WingCheckModelIndexAddress1 = 0x0051CC36; // 1.04j 0051CC36
	static DWORD WingCheckModelIndexAddress2 = 0x0051CC2F; // 1.04j 0051CC2F

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x1C]
		Sub Eax,ITEM_BASE_MODEL
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckModelIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp+0x1C],0x1AB1
		Jmp [WingCheckModelIndexAddress2]
	}
}

__declspec(naked) void WingCheckModelIndex2() // OK
{
	static DWORD WingCheckModelIndexAddress1 = 0x005BBACA; // 1.04j 005BBACA
	static DWORD WingCheckModelIndexAddress2 = 0x005BBAB4; // 1.04j 005BBAB4

	_asm
	{
		Mov Edx,Eax
		Mov Ecx,Edx
		Sub Ecx,ITEM_BASE_MODEL
		Push Edx
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckModelIndexAddress1]
		EXIT:
		Pop ax
		CMP AX,0x1AB1
		Jmp [WingCheckModelIndexAddress2]
	}
}

__declspec(naked) void WingCheckModelIndex3() // OK
{
	static DWORD WingCheckModelIndexAddress1 = 0x00627EAD; // 1.04j 00627EAD
	static DWORD WingCheckModelIndexAddress2 = 0x00627E07; // 1.04j 00627E07

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Ecx,Dword Ptr Ds:[Eax+0x30]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckModelIndexAddress1]
		EXIT:
		MOV EAX,DWORD PTR SS:[EBP+0x08]
		MOVSX ECX,WORD PTR DS:[EAX+0x02]
		CMP ECX,0x1AB1
		Jmp [WingCheckModelIndexAddress2]
	}
}

void __declspec(naked) WingsShowAdditionals()
{
	_asm
	{
		MOV WingsAddExcellentStatus_Lv2_Pointer, AX
	}
	// ----
	if(WingsAddExcellentStatus_Lv2_Pointer == ITEM(12, 40) || WingsAddExcellentStatus_Lv2_Pointer >= ITEM(12, 100) && WingsAddExcellentStatus_Lv2_Pointer <= ITEM(12, 512))
	{
		_asm
		{
			mov WingsAddExcellentStatus_Lv2_Buff, 0x00536780  //0x005363DC//MOV CL,BYTE PTR SS:[EBP-C]
			jmp WingsAddExcellentStatus_Lv2_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsAddExcellentStatus_Lv2_Buff, 0x0053677A//0x005363D6 //JG 0054130E
			jmp WingsAddExcellentStatus_Lv2_Buff
		}
	}
}


__declspec(naked) void WingAddLifeOption()
{
	_asm
	{
		MOV iWingAddLifeOption_Buff, EDX
	}

	if(iWingAddLifeOption_Buff == ITEM(12, 5) ||
		(iWingAddLifeOption_Buff >= ITEM(12, 36) && iWingAddLifeOption_Buff <= ITEM(12, 511)))
	{
		_asm
		{
			MOV EAX, 0x00536F2D//0059841C
			JMP EAX
		}
	}

	_asm
	{
		MOV EAX, 0x00536FA6 //00598495  
		JMP EAX
	}
}


__declspec(naked) void WingCheckIndex15() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005BCD61; // 1.04j 005B612F
	static DWORD WingCheckIndexAddress2 = 0x005BCD94; // 1.04j 005B6136

	_asm
	{
		CMP AX, 0x1824
		JL NEXT_CHECK
		CMP AX, 0x18FA
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP AX, 0x1800
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[WingCheckIndexAddress1]

			ALLOW_CHECK :
			JMP[WingCheckIndexAddress2]
	}
}

__declspec(naked) void JewelSetSalePrice() // OK
{
	static DWORD JewelSetSalePriceAddress1 = 0x0053903B;
	static DWORD JewelSetSalePriceAddress2 = 0x00537FD3;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::GetCustomJewelSalePrice]
		Mov Dword Ptr Ss:[Ebp-0x08],Eax
		Mov Dword Ptr Ss:[Ebp-0x04],0x00
		Jmp [JewelSetSalePriceAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [JewelSetSalePriceAddress2]
	}
}

__declspec(naked) void JewelInsertOne()
{
	static DWORD ItemJewelAllow01_Address01 = 0x005CC9CD; 
	static DWORD ItemJewelAllow01_Address02 = 0x005CC9E5;

	_asm
	{
		CMP SI, GET_ITEM(14, 200)
		JL NEXT
		CMP SI, GET_ITEM(14, 216)
		JLE EXIT

		NEXT :
		CMP SI, 0x1C2C
		JE EXIT

		JMP[ItemJewelAllow01_Address01]

		EXIT :
		JMP[ItemJewelAllow01_Address02]
	}
}

__declspec(naked) void JewelInsertTwo()
{
	_asm
	{
		MOV ID, EDI
	}

	switch (ID)
	{
	case ITEM(14,16):
		break;
	case ITEM(14,200):
		break;
	case ITEM(14,201):
		break;
	case ITEM(14,202):
		break;
	case ITEM(14,203):
		break;
	case ITEM(14,204):
		break;
	case ITEM(14,205):
		break;
	case ITEM(14,206):
		break;
	case ITEM(14,207):
		break;
	case ITEM(14,208):
		break;
	case ITEM(14,209):
		break;
	case ITEM(14,210):
		break;
	case ITEM(14,211):
		break;
	case ITEM(14,212):
		break;
	case ITEM(14,213):
		break;
	case ITEM(14,214):
		break;
	case ITEM(14,215):
		break;	
	case ITEM(14,216):
		break;
	default:
		_asm
		{
			MOV EDI,DWORD PTR DS:[0x7641800]
			MOV EAX, 0x005DDE8B
			JMP EAX
		}
		break;
	}

	_asm
	{
		MOV EAX, 0x005DDEA4
		JMP EAX
	}
}

__declspec(naked) void WingEnableMoveIcarus2()
{
	_asm
	{
		MOV iWingEnableMoveIcarus2_Buff, EAX
	}


	if(iWingEnableMoveIcarus2_Buff == ITEM(13, 30) || iWingEnableMoveIcarus2_Buff >= ITEM(12, 36) && iWingEnableMoveIcarus2_Buff <= ITEM(12, 512))
	{
		_asm
		{
			MOV EAX, 0x004EF18B//004689F7
			JMP EAX
		}
	}
	else
	{
		_asm
		{
			MOV EAX, 0x004EF160//004689D4
			JMP EAX
		}
	}
}

__declspec(naked) void WingEnableMoveIcarus()
{
	_asm
	{
		MOV iWingEnableMoveIcarus_Buff, EAX
	}


	if(iWingEnableMoveIcarus_Buff == ITEM(13, 30) || iWingEnableMoveIcarus_Buff >= ITEM(12, 36) && iWingEnableMoveIcarus_Buff <= ITEM(12, 512))
	{
		_asm
		{
			MOV EAX, 0x004EE99F//0046822F
			JMP EAX
		}
	}
	else
	{
		_asm
		{
			MOV EAX, 0x004EE974//0046820C
			JMP EAX
		}
	}
}

__declspec(naked) void WingEnableMoveKanturuEvent2()
{
	_asm
	{
		MOV ECX, 0x004BC090
		JMP ECX
	}
}

__declspec(naked) void WingShowDurability()
{
	_asm
	{
		MOV iWingShowDurability_Buff, AX
	}

	if( iWingShowDurability_Buff < ITEM(12, 0)
		|| (iWingShowDurability_Buff >= ITEM(12, 36) && iWingShowDurability_Buff <= ITEM(12, 250))
		|| (iWingShowDurability_Buff >= ITEM(13, 0) && iWingShowDurability_Buff < ITEM(14, 0)) )
	{
		_asm
		{
			MOV EDX, 0x005B6127 //00619DF3   > BA 01000000    MOV EDX,1
			JMP EDX
		}
	}

	_asm
	{
		MOV EDX, 0x005B6114//00619DD3 
		JMP EDX
	}
}

__declspec(naked) void WingEnableMoveKanturuEvent()
{
	_asm
	{
		MOV iWingEnableMoveKanturuEvent_Buff, EAX
	}


	if(iWingEnableMoveKanturuEvent_Buff == ITEM(13, 30) || iWingEnableMoveKanturuEvent_Buff >= ITEM(12, 36) && iWingEnableMoveKanturuEvent_Buff <= ITEM(12, 512))
	{
		_asm
		{
			MOV ECX, 0x004BBB33 //00434FBD 
			JMP ECX
		}
	}
	else
	{
		_asm
		{
			MOV ECX, 0x004BBB06//00434F90
			JMP ECX
		}
	}

}
