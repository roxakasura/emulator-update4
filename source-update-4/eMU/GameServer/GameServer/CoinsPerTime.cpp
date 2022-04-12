#include "stdafx.h"
#include "CoinsPerTime.h"
#include "DSProtocol.h"
#include "Notice.h"
#include "ServerInfo.h"
#include "User.h"

CCoinsPerTime gCoinsPerTime;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CCoinsPerTime::MainProc() // OK
{
	if(gServerInfo.m_CoinsPerTimeSwitch == 0)
	{
		return;
	}

	for(int n=OBJECT_START_USER;n < MAX_OBJECT;n++)
	{
		if(gObjIsConnectedGP(n) == 0)
		{
			continue;
		}

		LPOBJ lpObj = &gObj[n];

		if((GetTickCount()-lpObj->CoinsPerTime) >= ((DWORD)gServerInfo.m_CoinsPerTimeDelay *60000))
		{
			lpObj->CoinsPerTime = GetTickCount();
			GDSetCoinSend(lpObj->Index, gServerInfo.m_CoinsPerTimeType1[lpObj->AccountLevel], gServerInfo.m_CoinsPerTimeType2[lpObj->AccountLevel], gServerInfo.m_CoinsPerTimeType3[lpObj->AccountLevel], "CustomPerTime");
		}
	}

}
