#pragma once

#include "stdafx.h"

#define MAX_ITEM_PCPOINT 200

struct PCPOINT_ITEM_INFO
{
	int Index;
	int ItemIndex;
	int Level;
	int Value;
};

class CPcPoint
{
public:
	void InitPcPoint();
	void Load(PCPOINT_ITEM_INFO* info);
	int GetInfo(int item, int level);
public:
	PCPOINT_ITEM_INFO m_PointDate[MAX_ITEM_PCPOINT];
private:
	std::map<int,PCPOINT_ITEM_INFO> m_ItemInfo;

};
extern CPcPoint gPcPoint;

int PricePcPoint(int a1,int a2);
	