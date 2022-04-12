#pragma once

#include "stdafx.h"

#define MAX_CUSTOM_POSITION 1000

struct CUSTOM_POSITION_INFO
{
	int Index;
	int ItemIndex;
	float X;
	float Y;
	int Size;
};

class CCustomItemPosition
{
public:
	CCustomItemPosition();
	virtual ~CCustomItemPosition();
	void Init();
	void Load(char* path);
	void SetInfo(CUSTOM_POSITION_INFO info);
public:
	CUSTOM_POSITION_INFO m_Info[MAX_CUSTOM_POSITION];
};

extern CCustomItemPosition gCustomItemPosition;
