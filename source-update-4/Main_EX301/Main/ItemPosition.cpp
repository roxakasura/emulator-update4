#include "stdafx.h"
#include "ItemPosition.h"
#include "Util.h"
#include "utils.h"


CCustomItemPosition gCustomItemPosition;

CCustomItemPosition::CCustomItemPosition()
{

}

CCustomItemPosition::~CCustomItemPosition()
{

}

void CCustomItemPosition::Load(CUSTOM_POSITION_INFO* info) // OK
{
	for (int n = 0; n < MAX_CUSTOM_POSITION; n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomItemPosition::SetInfo(CUSTOM_POSITION_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_CUSTOM_POSITION)
	{
		return;
	}

	this->m_Info[info.Index] = info;
}

CUSTOM_POSITION_INFO* CCustomItemPosition::GetInfo(int index) // OK
{
	if (index < 0 || index >= MAX_CUSTOM_POSITION)
	{
		return 0;
	}

	if (this->m_Info[index].Index != index)
	{
		return 0;
	}

	return &this->m_Info[index];
}

CUSTOM_POSITION_INFO* CCustomItemPosition::GetInfoByItem(int ItemIndex) // OK
{
	for (int n = 0; n < MAX_CUSTOM_POSITION; n++)
	{
		CUSTOM_POSITION_INFO* lpInfo = this->GetInfo(n);

		if (lpInfo == 0)
		{
			continue;
		}

		if (lpInfo->ItemIndex == ItemIndex)
		{
			return lpInfo;
		}
	}
	return 0;
}

short CCustomItemPosition::CheckItemPositionByItem(int ItemIndex) // OK
{
	if (this->GetInfoByItem(ItemIndex) != 0)
	{
		return 1;
	}
	return 0;
}

int PositionItem(float PosResuX, float PosResuY, float X, float Y, int IDItems, int Level, int a7, int a8, int Tamanho)
{
	int n;

	if (gCustomItemPosition.CheckItemPositionByItem(IDItems) == 1)
	{
		for (n = 0; n < MAX_CUSTOM_POSITION; n++)
		{
			if (IDItems = gCustomItemPosition.m_Info[n].ItemIndex)
			{
				PosResuX = PosResuX + 1;
				PosResuY = PosResuY + 2;
				X = -12;
				Y = 42;
				Level = 11;
				Tamanho = 10;

				return ItemPosition(PosResuX, PosResuY, X, Y, IDItems, Level, a7, a8, Tamanho);
			}
		}
	}

	return	ItemPosition(PosResuX, PosResuY, X, Y, IDItems, Level, a7, a8, Tamanho);
}

void CCustomItemPosition::PositionItemLoad()
{
//	SetCompleteHook(0xE8, 0x005EAC8E, &PositionItem);
}