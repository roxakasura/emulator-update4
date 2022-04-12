// GoldenArcher.cpp: implementation of the CGoldenArcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GoldenArcher.h"
#include "QueryManager.h"
#include "SocketManager.h"

CGoldenArcher gGoldenArcher;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGoldenArcher::CGoldenArcher() // OK
{

}

CGoldenArcher::~CGoldenArcher() // OK
{

}

void CGoldenArcher::GDGoldenArcherCountRecv(SDHP_GOLDEN_ARCHER_COUNT_RECV* lpMsg,int index) // OK
{
	SDHP_GOLDEN_ARCHER_COUNT_SEND pMsg;

	pMsg.header.set(0x94,0x00,sizeof(pMsg));

	pMsg.index = lpMsg->index;

	memcpy(pMsg.account,lpMsg->account,sizeof(pMsg.account));

	pMsg.count = 0;

	if(gQueryManager.ExecQuery("SELECT * FROM EventGoldenArcher WHERE Account='%s'",lpMsg->account) == 0 || gQueryManager.Fetch() == SQL_NO_DATA)
	{
		gQueryManager.Close();

		gQueryManager.ExecQuery("INSERT INTO EventGoldenArcher (Account,RenaCount) VALUES ('%s',0)",lpMsg->account);

		gQueryManager.Close();
	}
	else
	{
		pMsg.count = gQueryManager.GetAsInteger("RenaCount");

		gQueryManager.Close();
	}

	gSocketManager.DataSend(index,(BYTE*)&pMsg,sizeof(pMsg));
}

void CGoldenArcher::GDGoldenArcherAddCountSaveRecv(SDHP_GOLDEN_ARCHER_ADD_COUNT_SAVE_RECV* lpMsg) // OK
{
	if(gQueryManager.ExecQuery("SELECT * FROM EventGoldenArcher WHERE Account='%s'",lpMsg->account) == 0 || gQueryManager.Fetch() == SQL_NO_DATA)
	{
		gQueryManager.Close();

		gQueryManager.ExecQuery("INSERT INTO EventGoldenArcher (Account,RenaCount) VALUES ('%s',%d)",lpMsg->account,lpMsg->Count);

		gQueryManager.Close();
	}
	else
	{
		DWORD RenaCount = gQueryManager.GetAsInteger("RenaCount");

		gQueryManager.Close();

		gQueryManager.ExecQuery("UPDATE EventGoldenArcher SET RenaCount=%d WHERE Account='%s'",(((RenaCount+lpMsg->Count)>0x7FFFFFFF)?0x7FFFFFFF:(RenaCount+lpMsg->Count)),lpMsg->account);

		gQueryManager.Close();
	}
}