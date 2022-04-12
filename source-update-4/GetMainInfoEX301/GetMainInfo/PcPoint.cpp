// PcPoint.cpp: implementation of the CPcPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcPoint.h"
#include "MemScript.h"

CPcPoint gPcPoint;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPcPoint::CPcPoint() // OK
{
	this->Init();
}

CPcPoint::~CPcPoint() // OK
{

}

void CPcPoint::Init() // OK
{
	for(int n=0;n < MAX_ITEM_PCPOINT;n++)
	{
		this->m_PcPointInfo[n].Index = -1;
	}
}

void CPcPoint::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

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

			PCPOINT_ITEM_INFO info;

			memset(&info,0,sizeof(info));

			static int CustomItemIndexCount = 0;

			info.Index = CustomItemIndexCount++;

			info.ItemIndex = lpMemScript->GetNumber();

			info.Level = lpMemScript->GetAsNumber();

			info.Value = lpMemScript->GetAsNumber();

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CPcPoint::SetInfo(PCPOINT_ITEM_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_ITEM_PCPOINT)
	{
		return;
	}

	this->m_PcPointInfo[info.Index] = info;
}
