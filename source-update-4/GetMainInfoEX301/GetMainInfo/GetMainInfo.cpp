#include "stdafx.h"
#include "..\..\Util\CCRC32.H"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomMessage.h"
#include "CustomWing.h"
#include "CustomEffectStatic.h"
#include "CustomEffectDynamic.h"
#include "SmokeEffect.h"
#include "ThemidaSDK.h"
#include "ItemDescription.h"
#include "CustomServerInfo.h"
#include "PcPoint.h"
#include "CustomEventTimeText.h"
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

int _tmain(int argc,_TCHAR* argv[]) // OK
{
	CLEAR_START

	ENCODE_START

	MAIN_FILE_INFO info;

	memset(&info,0,sizeof(info));

	info.IpAddressPort = GetPrivateProfileInt("MainInfo","IpAddressPort",44405,".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","CustomerName","",info.CustomerName,sizeof(info.CustomerName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","IpAddress","",info.IpAddress,sizeof(info.IpAddress),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientVersion","",info.ClientVersion,sizeof(info.ClientVersion),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientSerial","",info.ClientSerial,sizeof(info.ClientSerial),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","WindowName","",info.WindowName,sizeof(info.WindowName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ScreenShotPath","",info.ScreenShotPath,sizeof(info.ScreenShotPath),".\\MainInfo.ini");
	
	GetPrivateProfileString("MainInfo","ClientName","",info.ClientName,sizeof(info.ClientName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","PluginName1","",info.PluginName1,sizeof(info.PluginName1),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","PluginName2","",info.PluginName2,sizeof(info.PluginName2),".\\MainInfo.ini");

	info.DWMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DWMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.DKMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DKMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.FEMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","FEMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.MGMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","MGMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.DLMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DLMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.EnableCSSKill = GetPrivateProfileInt("Custom","EnableCsSkillsAllMaps",0,".\\MainInfo.ini");

	info.MiniMapCheck  = GetPrivateProfileInt("Custom","MiniMapCheck",0,".\\MainInfo.ini");

	info.SelectCharAnimate  = GetPrivateProfileInt("Custom","SelectCharAnimation",0,".\\MainInfo.ini");

	info.ItemLevel15 = GetPrivateProfileInt("Custom", "ItemLevel15", 0, ".\\MainInfo.ini");

	info.RightClick = GetPrivateProfileInt("Custom", "RightClick", 0, ".\\MainInfo.ini");

	info.PlayerInfoGuildLogo = GetPrivateProfileInt("Custom", "PlayerInfoGuildLogo", 0, ".\\MainInfo.ini");

	info.ExperienceType = GetPrivateProfileInt("Custom", "ExperienceType", 0, ".\\MainInfo.ini");

	info.ItemTransparency = GetPrivateProfileInt("Custom", "ItemTransparency", 0, ".\\MainInfo.ini");

	gCustomItem.Load("ItemManager/CustomItem.txt");

	gCustomWing.Load("ItemManager/CustomWing.txt");

	gCustomJewel.Load("ItemManager/CustomJewel.txt");

	gCustomItemDescription.Load("ItemManager/CustomItemDescription.txt");

	gSmokeEffect.Load("EffectManager/CustomSmokeEffect.txt");

	gCustomWingEffect.Load("EffectManager/CustomEffectStatic.txt");

	gDynamicWingEffect.Load("EffectManager/CustomEffectDynamic.txt");

	g_ServerInfo.Load("CommonManager/CustomServerInfo.txt");

	gPcPoint.Load("ItemManager/CustomPcPoint.txt");

	gCustomEventTimeText.Load("CommonManager/CustomEventTimeText.txt");

	//gCustomItemPosition.Load("ItemManager/CustomItemPosition.txt");
	
	if(gCustomMonster.Load("CommonManager/CustomMonster.txt") == 0) { system("pause"); return 0; }

	if(gCustomMap.Load("CommonManager/CustomMap.txt") == 0) { system("pause"); return 0; }

	memcpy(info.CustomItemInfo,gCustomItem.m_CustomItemInfo,sizeof(info.CustomItemInfo));
	
	memcpy(info.CustomWingInfo,gCustomWing.m_CustomWingInfo,sizeof(info.CustomWingInfo));
		
	memcpy(info.CustomJewelInfo,gCustomJewel.m_CustomJewelInfo,sizeof(info.CustomJewelInfo));
	
	memcpy(info.CustomDescriptionInfo,gCustomItemDescription.m_Info,sizeof(info.CustomDescriptionInfo));
	
	memcpy(info.CustomSmokeEffect,gSmokeEffect.m_CustomSmokeEffect,sizeof(info.CustomSmokeEffect));

	memcpy(info.CustomWingEffectInfo,gCustomWingEffect.m_CustomWingEffectInfo,sizeof(info.CustomWingEffectInfo));

	memcpy(info.DynamicWingEffectInfo,gDynamicWingEffect.m_DynamicWingEffectInfo,sizeof(info.DynamicWingEffectInfo));	
	
	memcpy(info.m_ServerInfo, g_ServerInfo.m_data, sizeof(info.m_ServerInfo));

	memcpy(info.m_PcPoint, gPcPoint.m_PcPointInfo, sizeof(info.m_PcPoint));

	memcpy(info.CustomEventInfo, gCustomEventTimeText.m_CustomEventInfo, sizeof(info.CustomEventInfo));

//	memcpy(info.CustomPositionInfo, gCustomItemPosition.m_Info, sizeof(info.CustomPositionInfo));

	memcpy(info.CustomMonsterInfo,gCustomMonster.m_CustomMonsterInfo,sizeof(info.CustomMonsterInfo));

	memcpy(info.CustomMapInfo,gCustomMap.m_CustomMapInfo,sizeof(info.CustomMapInfo));

	CCRC32 CRC32;

	if(CRC32.FileCRC(info.ClientName,&info.ClientCRC32,1024) == 0)
	{
		info.ClientCRC32 = 0;
	}

	if(CRC32.FileCRC(info.PluginName1,&info.Plugin1CRC32,1024) == 0)
	{
		info.Plugin1CRC32 = 0;
	}

	if(CRC32.FileCRC(info.PluginName2,&info.Plugin2CRC32,1024) == 0)
	{
		info.Plugin2CRC32 = 0;
	}

	for(int n=0;n < sizeof(MAIN_FILE_INFO);n++)
	{
		((BYTE*)&info)[n] ^= (BYTE)(0xCA^LOBYTE(n));
		((BYTE*)&info)[n] -= (BYTE)(0x95^HIBYTE(n));
	}

	system("mkdir \"Data\\Local\\\"");
	HANDLE file = CreateFile("Data/Local/Server.bmd", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, 0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if(WriteFile(file,&info,sizeof(MAIN_FILE_INFO),&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);

	ENCODE_END

	CLEAR_END

	return 0;
}
