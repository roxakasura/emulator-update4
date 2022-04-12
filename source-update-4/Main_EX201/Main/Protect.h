#pragma once

#include "CustomItem.h"
#include "CustomWing.h"

struct MAIN_FILE_INFO
{
	char CustomerName[32];
	BYTE LauncherType;
	char LauncherName[32];
	char IpAddress[32];
	WORD IpAddressPort;
	char ClientVersion[8];
	char ClientSerial[17];
	char WindowName[32];
	char ScreenShotPath[50];
	char ClientName[32];
	char PluginName[32];
	DWORD ClientCRC32;
	DWORD PluginCRC32;
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
};

class CProtect
{
public:

	CProtect();

	~CProtect();

	bool ReadMainFile(char* name);

	void CheckLauncher();

	void CheckInstance();

	void CheckClientFile();

	void CheckPluginFile();

public:

	MAIN_FILE_INFO m_MainInfo;

	DWORD m_ClientFileCRC;
};

extern CProtect gProtect;