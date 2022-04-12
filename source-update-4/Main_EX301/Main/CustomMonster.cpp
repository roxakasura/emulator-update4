// CustomMonster.cpp: implementation of the CCustomMonster class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomMonster.h"

CCustomMonster gCustomMonster;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomMonster::CCustomMonster() // OK
{
	this->Init();
}

CCustomMonster::~CCustomMonster() // OK
{

}

void CCustomMonster::Init() // OK
{
	for (int n=0; n<MAX_CUSTOM_MONSTER;n++)
	{
		this->m_CustomMonsterInfo[n].Index = -1;
	}
}

void CCustomMonster::Load(CUSTOM_MONSTER_INFO* info) // OK
{
	for (int n=0; n<MAX_CUSTOM_MONSTER;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomMonster::SetInfo(CUSTOM_MONSTER_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_CUSTOM_MONSTER)
	{
		return;
	}

	this->m_CustomMonsterInfo[info.Index] = info;
}

CUSTOM_MONSTER_INFO* CCustomMonster::GetInfo(int index) // OK
{
	if (index < 0 || index >= MAX_CUSTOM_MONSTER)
	{
		return 0;
	}

	if (this->m_CustomMonsterInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomMonsterInfo[index];
}

CUSTOM_MONSTER_INFO* CCustomMonster::GetInfoByIndex(int MonsterIndex) // OK
{
	for (int n=0; n<MAX_CUSTOM_MONSTER;n++)
	{
		CUSTOM_MONSTER_INFO* lpInfo = this->GetInfo(n);

		if (lpInfo == 0)
		{
			continue;
		}

		if (lpInfo->MonsterIndex == MonsterIndex)
		{
			return lpInfo;
		}
	}

	return 0;
}