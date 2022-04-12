// Duel.cpp: implementation of the CDuel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Duel.h"
#include "CastleSiege.h"
#include "DarkSpirit.h"
#include "DSProtocol.h"
#include "EffectManager.h"
#include "Guild.h"
#include "Map.h"
#include "MapServerManager.h"
#include "Message.h"
#include "Monster.h"
#include "Notice.h"
#include "ServerInfo.h"
#include "User.h"
#include "Util.h"

CDuel gDuel;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDuel::CDuel() // OK
{

}

CDuel::~CDuel() // OK
{

}

bool CDuel::CheckDuel(LPOBJ lpObj, LPOBJ lpTarget) // OK
{
	BOOL bRetVal = 0;

	if (lpObj->Type == OBJECT_USER || lpTarget->Type == OBJECT_USER)
	{
		if (lpObj->DuelUser == lpTarget->Index && lpTarget->DuelUser == lpObj->Index)
		{
			bRetVal = 1;
		}
	}

	return bRetVal;
}

void CDuel::CheckDuelScore(LPOBJ lpObj, LPOBJ lpTarget) // OK
{
	if (this->CheckDuel(lpObj, lpTarget) == 0)
	{
		return;
	}

	lpTarget->KillerType = 3;

	if (lpObj->DuelScore >= 10)
	{
		this->ResetDuel(lpObj);

		this->GCDuelEndSend(lpObj->Index, 0);

		GDRankingDuelSaveSend(lpObj->Index, 1, 0);

		this->ResetDuel(lpTarget);

		this->GCDuelEndSend(lpTarget->Index, 0);

		GDRankingDuelSaveSend(lpTarget->Index, 0, 1);

		GCFireworksSend(lpObj, lpObj->X, lpObj->Y);
	}
}

void CDuel::CheckDuelUser() // OK
{
	for (int i = OBJECT_START_USER; i < MAX_OBJECT; i++) //HermeX Fix
	{
		if (gObj[i].Connected == 3)
		{
			if (gObj[i].Type == OBJECT_USER)
			{
				if (OBJECT_RANGE(gObj[i].DuelUser))
				{
					if (GetTickCount() - gObj[i].DuelTickCount > 1260000)
					{
						this->GCDuelEndSend(gObj[i].DuelUser,0);
						this->GCDuelEndSend(gObj[i].DuelUser,0);
						this->ResetDuel(&gObj[i]);
					}
				}
			}
		}
	}

}

void CDuel::ResetDuel(LPOBJ lpObj) // OK
{
	gDarkSpirit[lpObj->Index].ResetTarget(lpObj->DuelUser);

	lpObj->DuelUserReserved = -1;
	lpObj->DuelUserRequested = -1;
	lpObj->DuelScore = 0;
	lpObj->DuelUser = -1;
	lpObj->DuelTickCount = 0;
}

void CDuel::RespawnDuelUser(LPOBJ lpObj) // OK
{
	gMap[lpObj->Map].GetMapRandomPos(&lpObj->X, &lpObj->Y, 18);
}

void CDuel::UserDieProc(LPOBJ lpObj, LPOBJ lpTarget) // OK
{
	if (this->CheckDuel(lpObj, lpTarget) == 0)
	{
		return;
	}

	lpTarget->DuelScore++;

	this->GCDuelScoreSend(lpObj->Index, lpTarget->Index);
}

void CDuel::CGDuelStartRecv(PMSG_DUEL_START_RECV* lpMsg, int aIndex)
{
	if (gServerInfo.m_DuelSwitch == 0)
	{
		return;
	}

	int iDuelIndex = -1;
	char szTempText[256];

	if (gObj[aIndex].CloseType != -1)
		return;


	if (OBJECT_RANGE(gObj[aIndex].DuelUserReserved) != 0 || OBJECT_RANGE(gObj[aIndex].DuelUserRequested) != 0 || OBJECT_RANGE(gObj[aIndex].DuelUser) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(163));
		return;
	}

	if (CA_MAP_RANGE(gObj[aIndex].Map) != 0 || DS_MAP_RANGE(gObj[aIndex].Map) != 0 || BC_MAP_RANGE(gObj[aIndex].Map) != 0 || CC_MAP_RANGE(gObj[aIndex].Map) != 0 || IT_MAP_RANGE(gObj[aIndex].Map) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167));
		return;
	}

#if(GAMESERVER_TYPE==1)

	if (gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_NOTIFY || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_READYSIEGE || gCastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(168));
		return;
	}

#endif

	LPOBJ lpObj = &gObj[aIndex];

	iDuelIndex = MAKE_NUMBERW(lpMsg->index[0], lpMsg->index[1]);

	if (!OBJECT_RANGE(iDuelIndex))
	{
		LogAdd(LOG_RED,"Error Duel: (%d) / Line: %d", iDuelIndex, __LINE__);
		return;
	}

	if (iDuelIndex == aIndex)
	{
		LogAdd(LOG_RED, "Error Duel: (%d) / Line: %d", iDuelIndex, __LINE__);
		return;
	}
	char szDuelName[11] = { 0 };
	char szDuelName2[11] = { 0 };
	memcpy(szDuelName, gObj[iDuelIndex].Name, 10);
	szDuelName[10] = 0;
	memcpy(szDuelName2, lpMsg->name, 10);
	szDuelName2[10] = 0;

	if (strcmp(szDuelName, szDuelName2))
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(169));
		return;
	}

	for (int n = 0; n < MAX_SELF_DEFENSE; n++)
	{
		if (lpObj->SelfDefense[n] >= 0)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(170));
			return;
		}

		if (gObj[iDuelIndex].SelfDefense[n] >= 0)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(171));
			return;
		}
	}

	if (IsDuelEnable(iDuelIndex) == FALSE)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(163));
		return;
	}

	if (lpObj->Guild && lpObj->Guild->WarState == 1)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(165));
		return;
	}

	if (gObj[iDuelIndex].Guild && gObj[iDuelIndex].Guild->WarState == 1)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(166));
		return;
	}

	if (gObjIsConnected(iDuelIndex) == FALSE)
		return;

	if (gObj[iDuelIndex].Type == OBJECT_MONSTER)
		return;

	if (gObj[iDuelIndex].CloseCount >= 0)
		return;


	if (CA_MAP_RANGE(gObj[iDuelIndex].Map) != 0 || DS_MAP_RANGE(gObj[iDuelIndex].Map) != 0 || BC_MAP_RANGE(gObj[iDuelIndex].Map) != 0 || CC_MAP_RANGE(gObj[iDuelIndex].Map) != 0 || IT_MAP_RANGE(gObj[iDuelIndex].Map) != 0 || DA_MAP_RANGE(gObj[iDuelIndex].Map) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167));
		return;
	}

	if (lpObj->Interface.use != 0 || gObj[iDuelIndex].Interface.use != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(161));
		return;
	}

	if ((gObj[iDuelIndex].Option & 2) == 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(162));
		return;
	}

	if (OBJECT_RANGE(gObj[iDuelIndex].DuelUserReserved) != 0 || OBJECT_RANGE(gObj[iDuelIndex].DuelUserRequested) != 0 || OBJECT_RANGE(gObj[iDuelIndex].DuelUser) != 0)
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(164));
		return;
	}

	lpObj->DuelUserReserved = iDuelIndex;
	lpObj->DuelUser = -1;
	gObj[iDuelIndex].DuelUserRequested = aIndex;

	PMSG_DUEL_OK_SEND pMsg;

	pMsg.header.set(0xAC, sizeof(pMsg));
	pMsg.index[0] = SET_NUMBERHB(aIndex);
	pMsg.index[1] = SET_NUMBERLB(aIndex);
	memcpy(pMsg.name, gObj[aIndex].Name, sizeof(pMsg.name));

	DataSend(iDuelIndex, (LPBYTE)&pMsg, pMsg.header.size);
}

void CDuel::CGDuelOkRecv(PMSG_DUEL_OK_RECV* lpMsg, int aIndex) // OK
{
	int iDuelIndex;
	PMSG_DUEL_START_SEND pMsgSend;

	iDuelIndex = -1;

	pMsgSend.header.set(0xAA, sizeof(pMsgSend));

	if (gObj[aIndex].CloseType != -1)
		return;

	iDuelIndex = MAKE_NUMBERW(lpMsg->index[0], lpMsg->index[1]);

	if (OBJECT_RANGE(iDuelIndex))
	{

		if (gObj[aIndex].DuelUserReserved != -1)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(163));
			return;
		}

		if (!gObjIsConnected(iDuelIndex))
			return;

		if (gObj[iDuelIndex].Type == OBJECT_MONSTER)
			return;

		if (gObj[iDuelIndex].CloseCount >= 0)
			return;

		if (lpMsg->flag)
		{
			if (BC_MAP_RANGE(gObj[iDuelIndex].Map) ||
				CC_MAP_RANGE(gObj[iDuelIndex].Map) ||
				DS_MAP_RANGE(gObj[iDuelIndex].Map))
			{
				gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(167));
				gObj[aIndex].DuelUserRequested = -1;
				gObj[iDuelIndex].DuelUserReserved = -1;
				memcpy(pMsgSend.name, gObj[aIndex].Name, sizeof(pMsgSend.name));
				pMsgSend.result = false;
				DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.header.size);
				return;
			}
		}

		if (OBJECT_RANGE(gObj[aIndex].DuelUser))
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(163));
			gObj[aIndex].DuelUserRequested = -1;
			gObj[iDuelIndex].DuelUserReserved = -1;
			memcpy(pMsgSend.name, gObj[aIndex].Name, sizeof(pMsgSend.name));
			pMsgSend.result = false;

			DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.header.size);
			return;
		}

		if (OBJECT_RANGE(gObj[aIndex].DuelUserReserved))
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(163));
			gObj[aIndex].DuelUserRequested = -1;
			gObj[iDuelIndex].DuelUserReserved = -1;
			memcpy(pMsgSend.name, gObj[aIndex].Name, sizeof(pMsgSend.name));
			pMsgSend.result = false;

			DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.header.size);
			return;
		}

		if (gObj[iDuelIndex].DuelUserReserved == aIndex)
		{
			char szDuelName[11] = { 0 };
			char szDuelName2[11] = { 0 };
			memcpy(szDuelName, gObj[iDuelIndex].Name, 10);
			szDuelName[10] = 0;
			memcpy(szDuelName2, lpMsg->name, 10);
			szDuelName2[10] = 0;

			if (!strcmp(szDuelName, szDuelName2))
			{
				if (lpMsg->flag == false)
				{
					gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(172));
					gObj[aIndex].DuelUserRequested = -1;
					gObj[iDuelIndex].DuelUserReserved = -1;
					memcpy(pMsgSend.name, gObj[aIndex].Name, sizeof(pMsgSend.name));
					pMsgSend.result = false;
					DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.header.size);
				}
				else if (lpMsg->flag == true)
				{
					gObj[iDuelIndex].DuelUserReserved = -1;
					gObj[iDuelIndex].DuelScore = 0;
					gObj[iDuelIndex].DuelUser = aIndex;
					gObj[iDuelIndex].DuelTickCount = GetTickCount();
					gObj[aIndex].DuelUserRequested = -1;
					gObj[aIndex].DuelUserReserved = -1;
					gObj[aIndex].DuelScore = 0;
					gObj[aIndex].DuelUser = iDuelIndex;
					gObj[aIndex].DuelTickCount = GetTickCount();

					pMsgSend.result = true;
					pMsgSend.index[0] = SET_NUMBERHB(iDuelIndex);
					pMsgSend.index[1] = SET_NUMBERLB(iDuelIndex);
					memcpy(pMsgSend.name, szDuelName, sizeof(pMsgSend.name));

					DataSend(aIndex, (LPBYTE)&pMsgSend, pMsgSend.header.size);

					pMsgSend.index[0] = SET_NUMBERHB(aIndex);
					pMsgSend.index[1] = SET_NUMBERLB(aIndex);
					memcpy(pMsgSend.name, gObj[aIndex].Name, sizeof(pMsgSend.name));

					DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.header.size);

					this->GCDuelScoreSend(gObj[aIndex].Index, gObj[iDuelIndex].Index);

					if (gServerInfo.m_DuelArenaAnnounceSwitch != 0) 
					{
						gNotice.GCNoticeSendToAll(0, 0, 0, 0, 0, 0, gMessage.GetMessage(174), gObj[aIndex].Name, gObj[iDuelIndex].Name); 
					}
				}
			}
			else
			{
				gObj[aIndex].DuelUserRequested = -1;
				gObj[iDuelIndex].DuelUserReserved = -1;
				pMsgSend.result = false;
				DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.header.size);
			}
		}
		else
		{
			gObj[aIndex].DuelUserRequested = -1;
			gObj[iDuelIndex].DuelUserReserved = -1;
			pMsgSend.result = false;
			DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.header.size);
		}
	}
}

void CDuel::CGDuelEndRecv(PMSG_DUEL_END_RECV * lpMsg, int aIndex) // OK
{
	int iDuelIndex;
	PMSG_DUEL_END_SEND pMsg;

	iDuelIndex = -1;

	if (gObj[aIndex].CloseType != -1)
		return;

	if (OBJECT_RANGE(gObj[aIndex].DuelUserReserved))
	{
		gObj[aIndex].DuelUserReserved = -1;
	}

	if (OBJECT_RANGE(gObj[aIndex].DuelUser))
	{
		iDuelIndex = gObj[aIndex].DuelUser;
		gObj[aIndex].DuelUser = -1;

		pMsg.header.set(0xAB, sizeof(pMsg));
		pMsg.index[0] = SET_NUMBERHB(iDuelIndex);
		pMsg.index[1] = SET_NUMBERLB(iDuelIndex);
		memcpy(pMsg.name, gObj[iDuelIndex].Name, sizeof(pMsg.name));
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.header.size);

		if (iDuelIndex == aIndex)
		{
			return;
		}
	}
	else
	{
		LogAdd(LOG_RED, "Error Duel: (%d) / Line: %d", iDuelIndex, __LINE__);
		return;
	}

	if (OBJECT_RANGE(gObj[iDuelIndex].DuelUser))
	{
		if (gObj[iDuelIndex].DuelUser == aIndex)
		{
			gObj[iDuelIndex].DuelUser = -1;

			pMsg.header.set(0xAB, sizeof(pMsg));
			pMsg.index[0] = SET_NUMBERHB(aIndex);
			pMsg.index[1] = SET_NUMBERLB(aIndex);
			memcpy(pMsg.name, gObj[aIndex].Name, sizeof(pMsg.name));
			DataSend(iDuelIndex, (LPBYTE)&pMsg, pMsg.header.size);
		}
	}
}

void CDuel::GCDuelStartSend(int aIndex, bool flag, int bIndex) // OK
{
	PMSG_DUEL_START_SEND pMsg;

	pMsg.header.set(0xAA, sizeof(pMsg));
	
	pMsg.result = flag;
	
	pMsg.index[0] = SET_NUMBERHB(aIndex);
	pMsg.index[1] = SET_NUMBERLB(aIndex);
	
	memcpy(pMsg.name, gObj[bIndex].Name, sizeof(pMsg.name));
	
	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}

void CDuel::GCDuelEndSend(int aIndex, BYTE result) // OK
{
	PMSG_DUEL_END_SEND pMsg;
	
	pMsg.header.set(0xAB, sizeof(pMsg));
	
	pMsg.index[0] = SET_NUMBERHB(aIndex);
	pMsg.index[1] = SET_NUMBERLB(aIndex);
	
	memcpy(pMsg.name, gObj[aIndex].Name, sizeof(pMsg.name));

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
}

void CDuel::GCDuelScoreSend(int aIndex, int bIndex) // OK
{
	PMSG_DUEL_SCORE_SEND pMsg;

	pMsg.header.set(0xAD, sizeof(pMsg));

	pMsg.index1[0] = SET_NUMBERHB(aIndex);
	pMsg.index1[1] = SET_NUMBERLB(aIndex);

	pMsg.index2[0] = SET_NUMBERHB(bIndex);
	pMsg.index2[1] = SET_NUMBERLB(bIndex);

	pMsg.score[0] = gObj[aIndex].DuelScore;
	pMsg.score[1] = gObj[bIndex].DuelScore;

	DataSend(aIndex, (BYTE*)&pMsg, pMsg.header.size);
	DataSend(bIndex, (BYTE*)&pMsg, pMsg.header.size);
}