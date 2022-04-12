#include "stdafx.h"

CCustomItemDescription gCustomItemDescription;

CCustomItemDescription::CCustomItemDescription()
{

}

CCustomItemDescription::~CCustomItemDescription()
{

}

void CCustomItemDescription::Load(CUSTOM_DESCRIPTION_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_DESCRIPTION;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomItemDescription::SetInfo(CUSTOM_DESCRIPTION_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_DESCRIPTION)
	{
		return;
	}

	this->m_Info[info.Index] = info;
}

CUSTOM_DESCRIPTION_INFO* CCustomItemDescription::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_DESCRIPTION)
	{
		return 0;
	}

	if(this->m_Info[index].Index != index)
	{
		return 0;
	}

	return &this->m_Info[index];
}

CUSTOM_DESCRIPTION_INFO* CCustomItemDescription::GetInfoByItem(int ItemIndex) // OK
{
	for(int n=0;n < MAX_CUSTOM_DESCRIPTION;n++)
	{
		CUSTOM_DESCRIPTION_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->ItemIndex == ItemIndex)
		{
			return lpInfo;
		}
	}
	return 0;
}

short CCustomItemDescription::CheckItemDescriptionByItem(int ItemIndex) // OK
{
	if(this->GetInfoByItem(ItemIndex) != 0)
	{
		return 1;
	}
	return 0;
}

char* CCustomItemDescription::GetDescription(int ItemIndex) // OK
{
	CUSTOM_DESCRIPTION_INFO* lpInfo = this->GetInfoByItem(26);

	if(lpInfo == 0)
	{
		return 0;
	}

	return lpInfo->Description;
}

void CCustomItemDescription::AddText(char* Text,int Color,int Weight)
{
	//*(&*(DWORD*)oItemText_Color + *(DWORD*)oItemText_Line)	= Color;
	//*(&*(DWORD*)oItemText_Weight + *(DWORD*)oItemText_Line)	= Weight;

	
	((void(*)(DWORD,char*,...))0x0068EFC7)((100 * (*(DWORD*)oItemText_Line) + oItemText_Index), Text);

	*(DWORD*)oItemText_Line += 1;
}

__declspec(naked) void DescriptionLevel()
{
	static WORD ItemCode;
	static WORD ItemBuffer;
	static int n;
	static int j;
	static DWORD DescAddress1 = 0x005A503B; //1.04j 005B4FE8  |> 66:813E 0E1C   CMP WORD PTR DS:[ESI],1C0E
	static DWORD DescAddress2 = 0x005A5005; //1.04j 005B4FA2  |. 75 44          JNZ SHORT olllysea.005B4FE8

	_asm
	{		
		Pushad;
			MOV ItemBuffer, AX
			mov ax, word ptr ss : [ESI]
			mov ItemCode, ax
	}

	 //---
    if(gCustomItemDescription.CheckItemDescriptionByItem(ItemCode) == 1)
	{
		for(n=0;n < MAX_CUSTOM_DESCRIPTION;n++)
		{
			if(gCustomItemDescription.m_Info[n].ItemIndex == 0)
			{
				if(gCustomItemDescription.m_Info[n].Description[0])
				{
					for(j = 0;j < MAX_CUSTOM_DESCRIPTION_LINES;j++)
					{
						if(gCustomItemDescription.m_Info[n].Line == j)
						{
							gCustomItemDescription.AddText("MeuCu",0,0);
						}
					}
				}
			}
		}
	}

	_asm
	{
		MOV AX, ItemBuffer
		MOV ESI, 0x005A503B
		JMP	ESI
	}

}


void DescriptionLevel2(int ItemCode)
{
	static int n;
	static int j;


	 //---
    if(gCustomItemDescription.CheckItemDescriptionByItem(ItemCode) == 1)
	{
		for(n=0;n < MAX_CUSTOM_DESCRIPTION;n++)
		{
			if(gCustomItemDescription.m_Info[n].ItemIndex == ItemCode)
			{
				if(gCustomItemDescription.m_Info[n].Description[0])
				{
					for(j = 0;j < MAX_CUSTOM_DESCRIPTION_LINES;j++)
					{
						if(gCustomItemDescription.m_Info[n].Line == j)
						{
							gCustomItemDescription.TextColor(gCustomItemDescription.m_Info[n].Description,gCustomItemDescription.m_Info[n].Color,gCustomItemDescription.m_Info[n].Border);
						}
					}
				}
			}
		}
	}
}

__declspec(naked) void ApplyDescription()
{
	static DWORD JewelApplyDescriptionAddress1 = 0x005A7428;

	_asm
	{
		Pushad;
		Movzx Ecx, Word Ptr Ss : [Edi] ;
		Push Ecx;
		Call[DescriptionLevel2];
		Add Esp, 0x04;
		Popad;
		Mov Eax, Dword Ptr Ds : [0x788C850] ; //1.04j 0x7672F38
		Lea Eax, Dword Ptr Ds : [Eax + Eax * 0x4] ;
		Push 0x6B8B64;			//1.04j 770138;
		Jmp[JewelApplyDescriptionAddress1];
	}
}

void CCustomItemDescription::Init()
{	
	//SetCompleteHook(0xE9,0x005A5000,&DescriptionLevel);	// -> Cima
	SetCompleteHook(0xE9,0x005A7420,&ApplyDescription);			// -> Baixo
	//gToolKit.SetRange((LPVOID)0x005A50F6, 59, ASM::NOP);
	//gToolKit.SetJmp((LPVOID)0x005A50F6, this->LoadDescription); // 006178B5

}

WORD  wItemDescriptionText_Pointer;
WORD  wItemDescriptionText_Buff;

__declspec(naked) void CCustomItemDescription::LoadDescription()
{
	_asm
	{
		MOV wItemDescriptionText_Buff, AX
		// ---
		MOV AX, WORD PTR SS:[ESI] // EBP
		MOV wItemDescriptionText_Pointer, AX
	}
	// ---
	if(wItemDescriptionText_Pointer == ITEM(12, 15))
	{
		gCustomItemDescription.TextColor("Para ser usado(a) na Chaos Machine.", 0, 0);
	}
	else if(wItemDescriptionText_Pointer == ITEM(12,12))
	{
		gCustomItemDescription.TextColor("Usada para adicionar excelentes opções em itens", 0, 0);
		gCustomItemDescription.TextColor("Taxa de Sucesso: 100%%", 0, 0);
		gCustomItemDescription.TextColor("Custom Jewel", 0, 0);
		
	}
	// ---
	_asm
	{
		MOV AX, wItemDescriptionText_Buff
		// ---
		MOV ESI, 0x005A5131 // 006178F1
		JMP ESI
	}
}

void CCustomItemDescription::TextColor(char * Text, int Color, int Weight, ...)
{
	char szBuffer[1024] = {0};
	// ---
	va_list pArguments;
	// ---
	va_start(pArguments, Text);
	// ---
	vsprintf(szBuffer, Text, pArguments);
	// ---
	va_end(pArguments);
	// ---
	*(&*(DWORD*)0x785B2A8 /*79F3F04*/ + *(DWORD*)0x788C850 /* 7A25A60*/) = Color;
	*(&*(DWORD*)0x7889F60 /*7A22F00*/+ *(DWORD*)0x788C850) = Weight;
	// ---
	pTextDescription(100 * (*(DWORD*)0x788C850) + 0x0785A110 /* 79F2D68*/, szBuffer);
	// ---
	*(DWORD*)0x788C850 += 1;
}