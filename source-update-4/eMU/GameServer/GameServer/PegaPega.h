// CEventRunAndCatch.h: interface for the CEventRunAndCatch class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

//GameServer > Client

struct PMSG_PEGAPEGA_SEND
{
	PSBMSG_HEAD	header;
	int Active;
};


class CEventRunAndCatch
{
public:
	CEventRunAndCatch();
	virtual ~CEventRunAndCatch();
	void MainProc();
	void Clear();
	void CommandEventRunAndCatch(LPOBJ lpObj,char* arg);
	void EventRunAndCatchHit(int aIndex, int bIndex);
    void CommandEventRunAndCatchJoin(LPOBJ lpObj,char* arg);
	void State(LPOBJ lpObj);
	int m_EventRunAndCatchActive;
	int m_Active;
private:
	int m_GmIndex;
	int m_RemainTime;
	int m_TickCount;
	int m_TotalTime;
	int m_Map;
	int m_MapX;
	int m_MapY;
	int m_Members;
	int m_EventRunAndCatchEnter;
};

extern CEventRunAndCatch gEventRunAndCatch;
