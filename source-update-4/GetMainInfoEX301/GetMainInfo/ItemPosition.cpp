// CustomItem.cpp: implementation of the CCustomItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemPosition.h"
#include "MemScript.h"

CCustomItemPosition gCustomItemPosition;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomItemPosition::CCustomItemPosition() // OK
{
	this->Init();
}

CCustomItemPosition::~CCustomItemPosition() // OK
{

}

void CCustomItemPosition::Init() // OK
{
	for (int n = 0; n < MAX_CUSTOM_POSITION; n++)
	{
		this->m_Info[n].Index = -1;
	}
}

void CCustomItemPosition::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if (lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if (strcmp("end", lpMemScript->GetString()) == 0)
			{
				break;
			}

			CUSTOM_POSITION_INFO info;

			memset(&info, 0, sizeof(info));

			static int CustomItemIndexCount = 0;

			info.Index = CustomItemIndexCount++;

			info.ItemIndex = lpMemScript->GetNumber();

			info.X = lpMemScript->GetAsFloatNumber();

			info.Y = lpMemScript->GetAsFloatNumber();

			info.Size = lpMemScript->GetNumber();

			this->SetInfo(info);
		}
	}
	catch (...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomItemPosition::SetInfo(CUSTOM_POSITION_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_CUSTOM_POSITION)
	{
		return;
	}

	this->m_Info[info.Index] = info;
}
