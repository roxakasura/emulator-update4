#include "stdafx.h"
#include "Controller.h"
#include "Patchs.h"
#include "Protect.h"
#include "Resolution.h"
#include "TrayMode.h"
#include "Util.h"
#include "Window.h"
#include "HackCheck.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "ItemManager.h"
#include "WingManager.h"

HINSTANCE hins;

extern "C" _declspec(dllexport) void _cdecl EntryProc()
{
	if (gProtect.ReadMainFile("Data/Local/Server.bmd") == 0)
	{
		MessageBoxA(NULL, "Main not found or invalid", "Error", MB_OK);

		ExitProcess(0);
	}
	
	gCustomItem.Load(gProtect.m_MainInfo.CustomItemInfo);

	gCustomWing.Load(gProtect.m_MainInfo.CustomWingInfo);

	gProtect.CheckLauncher();
	
	gProtect.CheckInstance();

	gProtect.CheckClientFile();

	gProtect.CheckPluginFile();

	InitHackCheck();

	//InitConsole();

	InitPatchs();

	InitResolution();

	InitPrintPlayer();

	InitItem();

	InitWing();
}

BOOL APIENTRY DllMain(HMODULE hModule,DWORD ul_reason_for_call,LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			hins = (HINSTANCE)hModule;

			gWindow.WindowModeLoad(hins);

			gController.Load(hins);

			gTrayMode.Init(hins);

			break;
		}

		case DLL_PROCESS_DETACH:
		{
			break;
		}

		case DLL_THREAD_ATTACH:
		{
			break;
		}

		case DLL_THREAD_DETACH:
		{
			break;
		}
	}

	return 1;
}