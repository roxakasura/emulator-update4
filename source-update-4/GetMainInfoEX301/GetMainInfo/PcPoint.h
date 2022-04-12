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
	CPcPoint();
	virtual ~CPcPoint();
	void Init();
	void Load(char* path);
	void SetInfo(PCPOINT_ITEM_INFO info);
public:
	PCPOINT_ITEM_INFO m_PcPointInfo[MAX_ITEM_PCPOINT];
};

extern CPcPoint gPcPoint;
