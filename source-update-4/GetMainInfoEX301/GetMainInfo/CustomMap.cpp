// CustomMap.cpp: implementation of the CCustomMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomMap.h"
#include "MemScript.h"

CCustomMap gCustomMap;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool CCustomMap::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR, path);
		return 0;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return 0;
	}

	for(int n=0;n< MAX_CUSTOM_MAP;n++)
	{
		this->m_CustomMapInfo[n].Index = -1;
	}

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			CUSTOM_MAP_INFO info;

			memset(&info,0,sizeof(info));

			static int CustomItemGloveCount = 0;

			info.Index = CustomItemGloveCount++;

			info.MapIndex = lpMemScript->GetNumber();

			strcpy_s(info.MapName,lpMemScript->GetAsString());

			strcpy_s(info.TitlePath,lpMemScript->GetAsString());

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
		return 0;
	}

	delete lpMemScript;

	return 1;
}

void CCustomMap::SetInfo(CUSTOM_MAP_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_MAP)
	{
		return;
	}

	this->m_CustomMapInfo[info.Index] = info;
}
