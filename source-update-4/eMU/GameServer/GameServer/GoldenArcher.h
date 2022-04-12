// GoldenArcher.h: interface for the CGoldenArcher class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Protocol.h"

//**********************************************//
//************ Client -> GameServer ************//
//**********************************************//

struct PMSG_GOLDEN_ARCHER_COUNT_RECV
{
	PBMSG_HEAD header; // C1:95
	BYTE type;
	BYTE slot;
};

//**********************************************//
//************ GameServer -> Client ************//
//**********************************************//

struct PMSG_GOLDEN_ARCHER_COUNT_SEND
{
	PBMSG_HEAD header; // C1:94
	BYTE type;
	DWORD count;
	WORD code[3];
};

//**********************************************//
//********** DataServer -> GameServer **********//
//**********************************************//

struct SDHP_GOLDEN_ARCHER_COUNT_RECV
{
	PSBMSG_HEAD header; // C1:94:00
	WORD index;
	char account[11];
	DWORD count;
};

//**********************************************//
//********** GameServer -> DataServer **********//
//**********************************************//

struct SDHP_GOLDEN_ARCHER_COUNT_SEND
{
	PSBMSG_HEAD header; // C1:94:00
	WORD index;
	char account[11];
};

struct SDHP_GOLDEN_ARCHER_ADD_COUNT_SAVE_SEND
{
	PSBMSG_HEAD header; // C1:94:30
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
	void Load(char* path);
	void CGGoldenArcherCountRecv(int aIndex);
	void CGGoldenArcherRegisterRecv(PMSG_GOLDEN_ARCHER_COUNT_RECV* lpMsg,int aIndex);
	void CGGoldenArcherCloseRecv(int aIndex);
	void DGGoldenArcherCountRecv(SDHP_GOLDEN_ARCHER_COUNT_RECV* lpMsg);
	void GDGoldenArcherAddCountSaveSend(int aIndex, DWORD count);
	void GoldenArcherReward(int aIndex, DWORD count);
private:
	int m_count;
	int m_active;
	int m_type;
	int m_quantity;
	//atributos
	int m_resets;
	int m_leveluppoint;
	int m_money;
	//coins
	int m_coin1;
	int m_coin2;
	int m_coin3;
	//vip
	int m_viptype;
	int m_days;
};

extern CGoldenArcher gGoldenArcher;
