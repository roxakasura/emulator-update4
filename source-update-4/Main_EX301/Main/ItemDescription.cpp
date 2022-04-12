#include "stdafx.h"
#include "ItemDescription.h"
#include "Util.h"
#include "TMemory.h"

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
	*(&*(DWORD*)oItemText_Color + *(DWORD*)oItemText_Line)	= Color;
	*(&*(DWORD*)oItemText_Weight + *(DWORD*)oItemText_Line)	= Weight;

	pSetItemTextLine(100 * (*(DWORD*)oItemText_Line) + oItemText_Index,Text);

	*(DWORD*)oItemText_Line += 1;
}

__declspec(naked) void DescriptionLevel()
{
	static DWORD ItemCode;
	static int n;
	static int j;
	static DWORD DescAddress1 = 0x005B4FE8; //1.04j 005B4FE8  |> 66:813E 0E1C   CMP WORD PTR DS:[ESI],1C0E
	static DWORD DescAddress2 = 0x005B4FA2; //1.04j 005B4FA2  |. 75 44          JNZ SHORT olllysea.005B4FE8

	_asm
	{
			movsx edx, word ptr ss : [ESI]
			mov ItemCode, edx
	}

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
							gCustomItemDescription.AddText(gCustomItemDescription.m_Info[n].Description,gCustomItemDescription.m_Info[n].Color,gCustomItemDescription.m_Info[n].Border);
						}
					}
				}
			}
		}
	}

	_asm
	{
		cmp     word ptr [esi], 1C0Dh
		JMP		[DescAddress2]
	}

}


void CCustomItemDescription::Init()
{	
	//SetCompleteHook(0xE9,0x005B4F9D,(DWORD)&DescriptionLevel);	// -> Cima
	SetCompleteHook(0xE9,0x005B72BA,&ApplyDescription);			// -> Baixo
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
							gCustomItemDescription.AddText(gCustomItemDescription.m_Info[n].Description,gCustomItemDescription.m_Info[n].Color,gCustomItemDescription.m_Info[n].Border);
						}
					}
				}
			}
		}
	}
}

__declspec(naked) void ApplyDescription()
{
	static DWORD JewelApplyDescriptionAddress1 = 0x005B72C2;

	_asm
	{
		Pushad;
		Movzx Ecx, Word Ptr Ss : [Edi] ;
		Push Ecx;
		Call[DescriptionLevel2];
		Add Esp, 0x04;
		Popad;
		Mov Eax, Dword Ptr Ds : [0x7672F38] ;
		Lea Eax, Dword Ptr Ds : [Eax + Eax * 0x4] ;
		Push 0x770138;
		Jmp[JewelApplyDescriptionAddress1];
	}
}

