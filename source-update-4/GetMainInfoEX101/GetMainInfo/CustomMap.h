// CustomMap.h: interface for the CCustomMap class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_MAP 20

struct CUSTOM_MAP_INFO
{
	int Index;
	int MapIndex;
	char MapName[32];
	char TitlePath[100];
};

class CCustomMap
{
public:
	bool Load(char* path);
	void SetInfo(CUSTOM_MAP_INFO info);
	CUSTOM_MAP_INFO m_CustomMapInfo[MAX_CUSTOM_MAP];
};

extern CCustomMap gCustomMap;