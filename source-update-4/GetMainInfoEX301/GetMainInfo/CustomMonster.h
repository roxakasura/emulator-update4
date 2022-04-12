// CustomMonster.h: interface for the CCustomMonster class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_MONSTER 100

struct CUSTOM_MONSTER_INFO
{
	int Index;
	int MonsterIndex;
	int Type;
	float Size;
	char FolderPath[128];
	char ModelPath[32];
	char Name[25];
};

class CCustomMonster
{
public:
	bool Load(char* path);
	void SetInfo(CUSTOM_MONSTER_INFO info);
	CUSTOM_MONSTER_INFO m_CustomMonsterInfo[MAX_CUSTOM_MONSTER];
};

extern CCustomMonster gCustomMonster;
