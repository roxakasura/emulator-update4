// GoldenArcher.h: interface for the CGoldenArcher class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataServerProtocol.h"

//**********************************************//
//********** GameServer -> DataServer **********//
//**********************************************//

struct SDHP_GOLDEN_ARCHER_COUNT_RECV
{
	PSBMSG_HEAD header; // C1:94:00
	WORD index;
	char account[11];
};

struct SDHP_GOLDEN_ARCHER_ADD_COUNT_SAVE_RECV
{
	PSBMSG_HEAD header; // C1:94:30
	WORD index;
	char account[11];
	DWORD Count;
};

//**********************************************//
//********** DataServer -> GameServer **********//
//**********************************************//

struct SDHP_GOLDEN_ARCHER_COUNT_SEND
{
	PSBMSG_HEAD header; // C1:94:00
	WORD index;
	char account[11];
	DWORD count;
};

//**********************************************//
//**********************************************//
//**********************************************//

class CGoldenArcher
{
public:
	CGoldenArcher();
	virtual ~CGoldenArcher();
	void GDGoldenArcherCountRecv(SDHP_GOLDEN_ARCHER_COUNT_RECV* lpMsg, int index);
	void GDGoldenArcherAddCountSaveRecv(SDHP_GOLDEN_ARCHER_ADD_COUNT_SAVE_RECV* lpMsg);
};

extern CGoldenArcher gGoldenArcher;