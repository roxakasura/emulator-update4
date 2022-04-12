#include "stdafx.h"
#include "CCRC32.H"
#include "ThemidaSDK.h"
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

int _tmain(int argc, _TCHAR* argv[])
{
	CLEAR_START

	ENCODE_START

	MAIN_FILE_INFO info;

	memset(&info, 0, sizeof(info));

	GetPrivateProfileString("MainInfo","CustomerName","",info.CustomerName,sizeof(info.CustomerName),".\\MainInfo.ini");

	info.LauncherType = GetPrivateProfileInt("MainInfo", "LauncherType", 0, ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "LauncherName", "XTLauncherExecutable", info.LauncherName, sizeof(info.LauncherName), ".\\MainInfo.ini");

	info.IpAddressPort = GetPrivateProfileInt("MainInfo", "IpAddressPort", 44405, ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "IpAddress", "", info.IpAddress, sizeof(info.IpAddress), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "ClientVersion", "", info.ClientVersion, sizeof(info.ClientVersion), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "ClientSerial", "", info.ClientSerial, sizeof(info.ClientSerial), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "WindowName", "", info.WindowName, sizeof(info.WindowName), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "ScreenShotPath", "", info.ScreenShotPath, sizeof(info.ScreenShotPath), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "ClientName", "", info.ClientName, sizeof(info.ClientName), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "PluginName", "", info.PluginName, sizeof(info.PluginName), ".\\MainInfo.ini");

	/*=================================================================
								CUSTOM
	==================================================================*/

	gCustomItem.Load("ItemManager/CustomItem.txt");

	gCustomWing.Load("ItemManager/CustomWing.txt");

	memcpy(info.CustomItemInfo,gCustomItem.m_CustomItemInfo,sizeof(info.CustomItemInfo));

	memcpy(info.CustomWingInfo,gCustomWing.m_CustomWingInfo,sizeof(info.CustomWingInfo));


	CCRC32 CRC32;

	if (CRC32.FileCRC(info.ClientName, &info.ClientCRC32, 1024) == 0)
	{
		info.ClientCRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName, &info.PluginCRC32, 1024) == 0)
	{
		info.PluginCRC32 = 0;
	}

	for (int n = 0; n < sizeof(MAIN_FILE_INFO); n++)
	{
		((BYTE*)&info)[n] ^= (BYTE)(0xA7 ^ LOBYTE(n));
		((BYTE*)&info)[n] -= (BYTE)(0x5D ^ HIBYTE(n));
	}

	system("mkdir \"Data\\Local\\\"");
	HANDLE file = CreateFile("Data/Local/Server.bmd",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);


	if (file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if (WriteFile(file, &info, sizeof(MAIN_FILE_INFO), &OutSize, 0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);

	ENCODE_END

		CLEAR_END

		return 0;
}
