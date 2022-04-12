// Protect.h: interface for the CProtect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"


struct MAIN_FILE_INFO
{
	char CustomerName[32];
	char IpAddress[32];
	WORD IpAddressPort;
	char ClientVersion[8];
	char ClientSerial[17];
	char WindowName[32];
	char ScreenShotPath[50];
	char ClientName[32];
	char PluginName1[32];
	char PluginName2[32];
	DWORD ClientCRC32;
	DWORD Plugin1CRC32;
	DWORD Plugin2CRC32;
	DWORD DWMaxAttackSpeed;
	DWORD DKMaxAttackSpeed;
	DWORD FEMaxAttackSpeed;
	DWORD MGMaxAttackSpeed;
	DWORD DLMaxAttackSpeed;
	DWORD MiniMapCheck;
	DWORD CSSkillCheck;
	DWORD SelectCharAnime;
	DWORD RemoveDraggingSkill;
	//
	DWORD ItemLevel15;
	DWORD TransparencyItem;
	DWORD RightClick;
	DWORD PlayerInfoGuildLogo;
	DWORD LoadingWhite;
	//
	DWORD RemoveKeyM;
	DWORD RemoveKeyD;
	DWORD RemoveKeyF;
	DWORD RemoveKeyT;
	DWORD RemoveKeyS;
	DWORD RemovePetDisplay;
	DWORD RemoveSetItemAncient;
	DWORD InterfaceType;
	DWORD ExperienceType;
	//
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_WING_EFFECT_INFO CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
	DYNAMIC_WING_EFFECT_INFO DynamicWingEffectInfo[MAX_DYNAMIC_WING_EFFECT];
	CUSTOM_DESCRIPTION_INFO CustomDescriptionInfo[MAX_CUSTOM_DESCRIPTION];
	CUSTOM_SMOKEEFFECT CustomSmokeEffect[MAX_SMOKE_ITEMS];	
	CUSTOM_MAP_INFO CustomMapInfo[MAX_CUSTOM_MAP];
	CUSTOM_MONSTER_INFO CustomMonsterInfo[MAX_CUSTOM_MONSTER];
};

class CProtect
{
public:
	CProtect();
	virtual ~CProtect();
	bool ReadMainFile(char* name);
	void CheckClientFile();
	void CheckPlugin1File();
	void CheckPlugin2File();
public:
	MAIN_FILE_INFO m_MainInfo;
	DWORD m_ClientFileCRC;
};

extern CProtect gProtect;
