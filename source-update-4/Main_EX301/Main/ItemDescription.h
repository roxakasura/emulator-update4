#pragma once

#include "stdafx.h"

#define MAX_CUSTOM_DESCRIPTION 1000
#define MAX_CUSTOM_DESCRIPTION_LINES 10

struct CUSTOM_DESCRIPTION_INFO
{
	int Index;
	int ItemIndex;
	int Line;
	int Color;
	int Border;
	CHAR Description[128];
};

void ApplyDescription();
void DescriptionLevel2(int ItemCode);


class CCustomItemDescription
{
public:
	CCustomItemDescription();
	virtual ~CCustomItemDescription();
	void Load(CUSTOM_DESCRIPTION_INFO* info);
	void SetInfo(CUSTOM_DESCRIPTION_INFO info);
	CUSTOM_DESCRIPTION_INFO* GetInfo(int index);
	CUSTOM_DESCRIPTION_INFO* GetInfoByItem(int ItemIndex);
	short CheckItemDescriptionByItem(int ItemIndex);
	char* GetDescription(int ItemIndex);
	void AddText(char* Text,int Color,int Weight);
	void Init();
public:
	CUSTOM_DESCRIPTION_INFO m_Info[MAX_CUSTOM_DESCRIPTION];
};
extern CCustomItemDescription gCustomItemDescription;