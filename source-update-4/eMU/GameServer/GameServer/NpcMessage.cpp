#include "stdafx.h"
#include "NpcMessage.h"
#include "MemScript.h"
#include "Protocol.h"
#include "User.h"
#include "Util.h"

CNpcTalkMessage gNpcTalkMessagek;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpcTalkMessage::CNpcTalkMessage() // OK
{
	this->m_NpcTalkInfos.clear();
}

CNpcTalkMessage::~CNpcTalkMessage() // OK
{

}


void CNpcTalkMessage::Load(char* path) // OK
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

	this->m_NpcTalkInfos.clear();

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

			NPC_TALK_INFOs info;

			memset(&info,0,sizeof(info));

			info.MonsterClass = lpMemScript->GetNumber();

			strcpy_s(info.Message,lpMemScript->GetAsString());

			this->m_NpcTalkInfos.push_back(info);

			if(IsValidMonster(info.MonsterClass) == 0){LogAdd(LOG_RED,"[%d] Invalid MonsterIndex. [%s]",info.MonsterClass,path);}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

bool CNpcTalkMessage::NpcTalk(LPOBJ lpNpc,LPOBJ lpObj) // OK
{
	for(std::vector<NPC_TALK_INFOs>::iterator it = this->m_NpcTalkInfos.begin(); it != this->m_NpcTalkInfos.end(); it++)
	{
		SYSTEMTIME SystemTime;

		GetLocalTime(&SystemTime);

		if(lpNpc->Class != it->MonsterClass)
		{
			continue;
		}

		GCChatTargetSend(lpObj,lpNpc->Index,it->Message);	
		return 1;
	}
	return 1;
}
