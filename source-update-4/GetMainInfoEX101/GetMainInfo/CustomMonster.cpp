// CustomMonster.cpp: implementation of the CCustomMonster class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomMonster.h"
#include "MemScript.h"

CCustomMonster gCustomMonster;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool CCustomMonster::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return 0;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return 0;
	}

	for(int n=0;n < MAX_CUSTOM_MONSTER;n++)
	{
		this->m_CustomMonsterInfo[n].Index = -1;
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

			CUSTOM_MONSTER_INFO info;

			memset(&info,0,sizeof(info));

			static int CustomMonsterIndexCount = 0;

			info.Index = CustomMonsterIndexCount++;

			info.MonsterIndex = lpMemScript->GetNumber();

			info.Type = lpMemScript->GetAsNumber();

			info.Size = lpMemScript->GetAsFloatNumber();

			strcpy_s(info.FolderPath,lpMemScript->GetAsString());

			strcpy_s(info.ModelPath,lpMemScript->GetAsString());

			strcpy_s(info.Name,lpMemScript->GetAsString());

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

void CCustomMonster::SetInfo(CUSTOM_MONSTER_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_MONSTER)
	{
		return;
	}

	this->m_CustomMonsterInfo[info.Index] = info;
}
