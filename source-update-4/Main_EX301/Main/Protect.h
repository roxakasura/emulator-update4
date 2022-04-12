// Protect.h: interface for the CProtect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "ItemDescription.h"
#include "ItemSmoke.h"
#include "ServerInfo.h"
#include "PcPoint.h"
#include "EventTime.h"
#include "ItemPosition.h"
#include "CustomMonster.h"
#include "CustomMap.h"

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
	DWORD EnableCSSKill;
	DWORD MiniMapCheck;
	DWORD SelectCharAnimate;	
	DWORD ItemLevel15;
	DWORD RightClick;
	DWORD PlayerInfoGuildLogo;
	DWORD ExperienceType;
	DWORD ItemTransparency;
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_DESCRIPTION_INFO CustomDescriptionInfo[MAX_CUSTOM_DESCRIPTION];
	CUSTOM_SMOKEEFFECT CustomSmokeEffect[MAX_SMOKE_ITEMS];	
	CUSTOM_WING_EFFECT_INFO CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
	DYNAMIC_WING_EFFECT_INFO DynamicWingEffectInfo[MAX_DYNAMIC_WING_EFFECT];
	SERVERINFO_DATA m_ServerInfo[MAX_SERVER_CLASS];
	PCPOINT_ITEM_INFO m_PcPoint[MAX_ITEM_PCPOINT];
	CUSTOM_EVENT_INFO CustomEventInfo[MAX_EVENTTIME];
//	CUSTOM_POSITION_INFO CustomPositionInfo[MAX_CUSTOM_POSITION];
	CUSTOM_MONSTER_INFO CustomMonsterInfo[MAX_CUSTOM_MONSTER];
	CUSTOM_MAP_INFO CustomMapInfo[MAX_CUSTOM_MAP];
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
