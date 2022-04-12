// CustomNpcCollector.h: interface for the CCustomNpcCollector class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "User.h"

#define MAX_ITEM_LIST  50
// ---
struct CUSTOM_COLLECTOR_DATA
{
	int  m_Cat;
	int  m_Item;
	int  m_Coin1;
	int  m_Coin2;
	int  m_Coin3;
};
// ---

// ---
class CCustomNpcCollector
{
public:
	void Load(char* path);
	bool NpcTalk(LPOBJ lpNpc, LPOBJ lpObj);

private:
	int m_count;
	int m_active;
	int m_npcindex;
	int m_quantity;
	// ---
	CUSTOM_COLLECTOR_DATA m_Data[MAX_ITEM_LIST];
};
extern CCustomNpcCollector gCustomNpcCollector;
// ---
