#pragma once

#include <vector>
#include "User.h"

struct NPC_TALK_INFOs
{
	int MonsterClass;
	char Message[60];
};

class CNpcTalkMessage
{
public:
	CNpcTalkMessage();
	virtual ~CNpcTalkMessage();
	void Load(char* path);
	bool NpcTalk(LPOBJ lpNpc,LPOBJ lpObj);
private:
	int m_npcindex;
	std::vector<NPC_TALK_INFOs> m_NpcTalkInfos;
};

extern CNpcTalkMessage gNpcTalkMessagek;
