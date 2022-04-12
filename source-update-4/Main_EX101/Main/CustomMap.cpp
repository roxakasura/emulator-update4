// CustomMap.cpp: implementation of the CCustomMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomMap.h"

CCustomMap gCustomMap;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomMap::CCustomMap() // OK
{
	this->Init();
}

CCustomMap::~CCustomMap() // OK
{

}

void CCustomMap::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_MAP;n++)
	{
		this->m_CustomMapInfo[n].Index = -1;
	}
}

void CCustomMap::Load(CUSTOM_MAP_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_MAP;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomMap::SetInfo(CUSTOM_MAP_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_MAP)
	{
		return;
	}

	this->m_CustomMapInfo[info.Index] = info;
}

CUSTOM_MAP_INFO* CCustomMap::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_MAP)
	{
		return 0;
	}

	if(this->m_CustomMapInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomMapInfo[index];
}

CUSTOM_MAP_INFO* CCustomMap::GetInfoByNumber(int MapNumber) // OK
{
	for(int n=0;n < MAX_CUSTOM_MAP;n++)
	{
		CUSTOM_MAP_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->MapIndex == MapNumber)
		{
			return lpInfo;
		}
	}

	return 0;
}