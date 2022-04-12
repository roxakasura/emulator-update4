// CustomMove.cpp: implementation of the CCustomMove class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommandManager.h"
#include "MoveCustom.h"
#include "Log.h"
#include "Map.h"
#include "MapManager.h"
#include "MemScript.h"
#include "Message.h"
#include "Notice.h"
#include "Util.h"
#include "EffectManager.h"

CCustomMove gCustomMove;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomMove::CCustomMove() // OK
{
	this->m_CustomMoveInfo.clear();
}

CCustomMove::~CCustomMove() // OK
{

}

void CCustomMove::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_CustomMoveInfo.clear();

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

			CUSTOMMOVE_INFO info;

			info.Index = lpMemScript->GetNumber();

			strcpy_s(info.Name,lpMemScript->GetAsString());

			info.Map = lpMemScript->GetAsNumber();

			info.X = lpMemScript->GetAsNumber();

			info.Y = lpMemScript->GetAsNumber();

			info.MinLevel = lpMemScript->GetAsNumber();

			info.MaxLevel = lpMemScript->GetAsNumber();

			info.MinReset = lpMemScript->GetAsNumber();

			info.MaxReset = lpMemScript->GetAsNumber();

			info.MinMReset = lpMemScript->GetAsNumber();

			info.MaxMReset = lpMemScript->GetAsNumber();

			info.AccountLevel = lpMemScript->GetAsNumber();

			info.PkMove = lpMemScript->GetAsNumber();

			this->m_CustomMoveInfo.insert(std::pair<int,CUSTOMMOVE_INFO>(info.Index,info));
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

bool CCustomMove::GetInfo(int index,CUSTOMMOVE_INFO* lpInfo) // OK
{
	std::map<int,CUSTOMMOVE_INFO>::iterator it = this->m_CustomMoveInfo.find(index);

	if(it == this->m_CustomMoveInfo.end())
	{
		return 0;
	}
	else
	{
		(*lpInfo) = it->second;
		return 1;
	}
}

bool CCustomMove::GetInfoByName(char* message,CUSTOMMOVE_INFO* lpInfo) // OK
{
	char command[32] = {0};

	memset(command,0,sizeof(command));

	gCommandManager.GetString(message,command,sizeof(command),0);


	for(std::map<int,CUSTOMMOVE_INFO>::iterator it=this->m_CustomMoveInfo.begin();it != this->m_CustomMoveInfo.end();it++)
	{
		if(_stricmp(it->second.Name,command) == 0)
		{
			(*lpInfo) = it->second;
			return 1;
		}
	}

	return 0;
}

void CCustomMove::GetMove(LPOBJ lpObj,int index) // OK
{
	CUSTOMMOVE_INFO CustomMoveInfo;

	if(this->GetInfo(index,&CustomMoveInfo) == 0)
	{
		return;
	}

	gObjTeleport(lpObj->Index,CustomMoveInfo.Map,CustomMoveInfo.X,CustomMoveInfo.Y);
	gLog.Output(LOG_COMMAND,"[CustomMove][%s][%s] - (MoveIndex: %d)",lpObj->Account,lpObj->Name,index);
}