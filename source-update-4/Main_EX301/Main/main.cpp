#include "main.h"
#include "utils.h"
#include "stdafx.h"
#include "Resolution.h"
#include "Util.h"
#include "detours.h"
#include "TMemory.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "RightClick.h"
#include "Protect.h"
#include "Interface.h"
#include "PacketManager.h"
#include "Reconnect.h"
#include "User.h"
#include "HackCheck.h"
#include "CustomItem.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "ItemManager.h"
#include "Camera3D.h"
#include "Controller.h"
#include "SelectCharAnimation.h"
#include "Minimap.h"
#include "NewMaps.h"
#include "ItemDescription.h"
#include "Font.h"
#include "WeaponFix.h"
#include "ServerInfo.h"
#include "ItemSmoke.h"
#include "EffectManager.h"
#include "PlayerSystem.h"
#include "PcPoint.h"
#include "SelectServerS13.h"
#include "CtrlChar.h"
#include "Console.h"
#include "EventTime.h"
#include "Experience.h"
#include "ItemPosition.h"
#include "CustomMonster.h"
#include "Monster.h"
#include "Common.h"
#include "CustomMap.h"

HINSTANCE hins;

void ReduceRam(LPVOID lpThreadParameter)
{
	HANDLE v1;

	HANDLE v2;

	while (TRUE)
	{
		Sleep(5000);

		v1 = GetCurrentProcess();

		SetProcessWorkingSetSize(v1, 0xFFFFFFFF, 0xFFFFFFFF);

		v2 = GetCurrentProcess();

		SetThreadPriority(v2, -2);
	}
}

__declspec(naked) void ReduceCPU()
{
	static DWORD OptimizeBack = 0x00662725;

	__asm
	{
		PUSH 1;
		CALL DWORD PTR DS : [0x0075615C];
		CALL DWORD PTR DS : [0x00756140]; 

		JMP OptimizeBack;
	}
}


SHORT WINAPI KeysProc(int nCode) // OK
{
	if(GetForegroundWindow() != *(HWND*)(MAIN_WINDOW))
	{
		return 0;
	}

	return GetAsyncKeyState(nCode);
}

HICON WINAPI IconProc(HINSTANCE hInstance,LPCSTR lpIconName) // OK
{
	gTrayMode.m_TrayIcon = (HICON)LoadImage(hins,".\\Data\\Logo\\main.ico",IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),LR_LOADFROMFILE | LR_DEFAULTCOLOR);

	return gTrayMode.m_TrayIcon;
}


extern "C" _declspec(dllexport) void Init()
{
	DWORD OldProtect;
	if(VirtualProtect(LPVOID(0x401000),0x00875FFF,PAGE_EXECUTE_READWRITE,&OldProtect))
	{
		if (gProtect.ReadMainFile("Data/Local/Server.bmd") == 0)
		{
			MessageBox(0,"Main not found or invalid!","Error",MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}	

	//char Experiencia3[200];
	//sprintf(Experiencia3,"F:%d / A:%d / V:%d / E:%d",ViewStrength,ViewDexterity,ViewVitality,ViewEnergy);
	//Console.Write(Experiencia3,0,1);

	PlayerLoad();

	CButtonCharacterS13();

	if(gProtect.m_MainInfo.ExperienceType == 1)
	{
		gAddons.Load();
	}
	
	//MemorySet(0x0059F060, 0x90, 0x5); //Image SD
	//MemorySet(0x0059F114, 0x90, 0x5); //Tooltip SD
	//MemorySet(0x0059F07A, 0x90, 0x5); //Value SD
	//Console.Init();

	//CtrlChar();

	//SetByte(0x005426C5 + 2, 0); //AUTOCTRL ATIVO
	//SetByte(0x0054239A + 2, 0); //AUTOCTRL ATIVO
	//SetByte(0x00542854 + 2, 0); //AUTOCTRL ATIVO

	//SetDword(0x0065C343 + 1, 0); //aumentar zen do inventario e bau e personal
	//MemorySet(0x658280, 0x90, 0x49A4);

		// +11
	//SetCompleteHook(0xE9, 0x00627A41, 0x00627A5A);
	//SetCompleteHook(0xE9, 0x00627A8A, 0x00627ADF);
	if(gProtect.m_MainInfo.ItemTransparency == 1)
	{
		// +12
		SetCompleteHook(0xE9, 0x00627B39, 0x00627B52);
		SetCompleteHook(0xE9, 0x00627B80, 0x00627BA9);
		SetCompleteHook(0xE9, 0x00627BAC, 0x00627BD3);
		//
		//// +13
		SetCompleteHook(0xE9, 0x00627C2E, 0x00627C47);
		SetCompleteHook(0xE9, 0x00627C77, 0x00627C9E);
		//SetCompleteHook(0xE9, 0x00627CA1, 0x00627CCA);

		// +14
		SetCompleteHook(0xE9, 0x00627CF5, 0x00627D0B);
		// Fix Elf Soldier e Soley Scepter Select Server Brilho + 13
		SetByte(0x0052C1D0+6,11);
		SetByte(0x0052C1DA+6,11);
		SetByte(0x0052C1E4+6,11);
		SetByte(0x0052C1EE+6,11);
		SetByte(0x0052C1F8+6,11);
		SetByte(0x00531D65+6,11);
	}


	gPcPoint.InitPcPoint();
	SetByte(0x0076E2B0,0xA0); // Accent
	SetByte(0x00648D04,0xEB); // Crack(mu.exe)
	SetByte(0x00649085,0xE9); // Crack(GameGuard)
	SetByte(0x00649086,0x8A); // Crack(GameGuard)
	SetByte(0x00649087,0x00); // Crack(GameGuard)
	SetByte(0x00649088,0x00); // Crack(GameGuard)
	SetByte(0x00649089,0x00); // Crack(GameGuard)
	SetByte(0x00675D0A,0xEB); // Crack(ResourceGuard)
	SetByte(0x0064903C,0xEB); // Crack(ResourceGuard)
	SetByte(0x004F8B3B,0xEB); // Ctrl Fix
	SetByte(0x004F8B49,0x02); // Ctrl Fix
	SetByte(0x00648C71,0xEB); // Multi Instance
	SetByte(0x0065EB3C,0x7F); // Fix Enter Select Char
	SetByte(0x00661E9D,0xE9); // Website
	SetByte(0x00661E9E,0x38); // Website
	SetByte(0x00661E9F,0x02); // Website
	SetByte(0x00661EA0,0x00); // Website
	SetByte(0x0045B0A8,0xEB); // Fix Ancient Harmony
	SetByte(0x005B22E3,0x1D); // Fix Box of Luck
	MemorySet(0x00621EC9, 0x90, 0x5); //Fix Bug Visual no Halloween Ring
	MemorySet(0x0050CFD3, 0x90, 0x3F); // Remove Reflect Effect
	SetByte(0x0077F598, (gProtect.m_MainInfo.ClientVersion[0] + 1));
	SetByte(0x0077F599, (gProtect.m_MainInfo.ClientVersion[2] + 2));
	SetByte(0x0077F59A, (gProtect.m_MainInfo.ClientVersion[3] + 3));
	SetByte(0x0077F59B, (gProtect.m_MainInfo.ClientVersion[5] + 4));
	SetByte(0x0077F59C, (gProtect.m_MainInfo.ClientVersion[6] + 5));
	SetWord(0x0077EBA8, (gProtect.m_MainInfo.IpAddressPort));
	SetDword(0x00647CCB, (DWORD)gProtect.m_MainInfo.WindowName);
	SetDword(0x00662262, (DWORD)gProtect.m_MainInfo.ScreenShotPath);
	MemoryCpy(0x0076E2F0, gProtect.m_MainInfo.IpAddress, sizeof(gProtect.m_MainInfo.IpAddress));
	MemoryCpy(0x0077F5A0, gProtect.m_MainInfo.ClientSerial, sizeof(gProtect.m_MainInfo.ClientSerial));

	SetCompleteHook(0xFF, 0x0069C2C0, &ProtocolCoreEx);
	SetDword(0x007564B4,(DWORD)&KeysProc);
	SetDword(0x00756520,(DWORD)&IconProc);

	gCustomItem.Load(gProtect.m_MainInfo.CustomItemInfo);

	gCustomWing.Load(gProtect.m_MainInfo.CustomWingInfo);

	gCustomJewel.Load(gProtect.m_MainInfo.CustomJewelInfo);

	gCustomItemDescription.Load(gProtect.m_MainInfo.CustomDescriptionInfo);
	
	gSmokeEffect.Load(gProtect.m_MainInfo.CustomSmokeEffect);
	
	gCustomWingEffect.Load(gProtect.m_MainInfo.CustomWingEffectInfo);

	gDynamicWingEffect.Load(gProtect.m_MainInfo.DynamicWingEffectInfo);

	g_ServerInfo.Init(gProtect.m_MainInfo.m_ServerInfo);

	gPcPoint.Load(gProtect.m_MainInfo.m_PcPoint);

	gCustomEventTime.Load(gProtect.m_MainInfo.CustomEventInfo);

	//gCustomItemPosition.Load(gProtect.m_MainInfo.CustomPositionInfo);

	gCustomMonster.Load(gProtect.m_MainInfo.CustomMonsterInfo);

	gCustomMap.Load(gProtect.m_MainInfo.CustomMapInfo);

	if(gProtect.m_MainInfo.DWMaxAttackSpeed >= 65535)
	{
		SetByte((PVOID)(0x00510E50 + 6), 2); //Fix Skills Attack Speed
	}

	if(gProtect.m_MainInfo.DKMaxAttackSpeed >= 65535)
	{
		SetByte((PVOID)(0x00510E50 + 6), 2); //Fix Skills Attack Speed
	}

	if(gProtect.m_MainInfo.FEMaxAttackSpeed >= 65535)
	{
		SetByte((PVOID)(0x00510E50 + 6), 2); //Fix Skills Attack Speed
	}

	if(gProtect.m_MainInfo.MGMaxAttackSpeed >= 65535)
	{
		SetByte((PVOID)(0x00510E50 + 6), 2); //Fix Skills Attack Speed
	}

	if(gProtect.m_MainInfo.DLMaxAttackSpeed >= 65535)
	{
		SetByte((PVOID)(0x00510E50 + 6), 2); //Fix Skills Attack Speed
	}

	//MemorySet(0x005A20C0,0x90,0x439);
	//MemorySet(0x005A2408,0x90,0x5); //TOOLTIP EXPERIENCE
	//MemorySet(0x005A232D,0x90,0x5); //NUMERO AO LADO DA BARRA
	//MemorySet(0x005A22EA,0x90,0x5); //BARRA AMARELA

	//MemorySet(0x006F9E38, 0x90, 23); //MessageBox LoadImageJPG
	//MemorySet(0x006FA32D, 0x90, 23); //MessageBox LoadImageTGA

	gPacketManager.LoadEncryptionKey("Data\\Enc1.dat");

	gPacketManager.LoadDecryptionKey("Data\\Dec2.dat");

	gUser.Load();

	gInterface.Load();

	InitPrintPlayer();

	InitReconnect();

	gProtect.CheckClientFile();

	gProtect.CheckPlugin1File();

	gProtect.CheckPlugin2File();

	InitMonster();

	InitMap();

	//cursor - utilizada para fazer o select server s13
	//MemorySet(0x0065F153, 0x90, 0x5); //select char (usar esse)
	//MemorySet(0x0065FE00, 0x90, 0x5); //select server
	MemorySet(0x004F317C, 0x90, 0x142);

	InitResolution();

	InitHackCheck();

	InitItem();
	//
	InitWing();
	//
	InitJewel();

	InitCommon();

	if(gProtect.m_MainInfo.SelectCharAnimate == 1)
	{
		gSelectChar.Load();
	}

	gCustomItemDescription.Init();

	gFont.Load();

	//MemorySet(0x5B2070,0x90,0x5BA0);

	if (gProtect.m_MainInfo.RightClick == 1)
	{
		RightClick();
	}

	//MemorySet(0x50D920,0x90,0x2CC0);
	
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ReduceRam, 0, 0, 0);

	SetCompleteHook(0xE9,0x0066271F,&ReduceCPU);

	//MemorySet(0x005F686E,0x90,0x5); xp
	//MemorySet(0x5A20C0,0x90,0x439); //exp da barra da interface
	//MemorySet(0x59F330,0x90,0x3E5); //INTERFACE + EXP
	//MemorySet(0x0059FAF6,0x90,0x5);
	//MemorySet(0x0059FB07,0x90,0x5); life da barra
	//MemorySet(0x5B2070,0x90,0x5BA0); //tooltip da season 3
	//MemorySet(0x5F6180,0x90,0x2DD9); //menu C

	//SetByte(0x005F8ED7+1,0);//  |> 6A 67          PUSH 67
	//SetDword(0x005F8ED9+1,0);//  |. 68 BF000000    PUSH 0BF
	//SetDword(0x005F8EDE+1,0);//  |. 68 DF000000    PUSH 0DF
	//MemorySet(0x005F8F11,0x90,0x5); //remove dl stats
	//MemorySet(0x59D5B0,0x90,0x4F1);

	//MemorySet(0x006968B0,0x90,0x705); //remove messagebox
	//MemorySet(0x00696A7D,0x90,0x5);
	//MemorySet(0x00696D45,0x90,0x5);

	//MemorySet(0x5B2070,0x90,0x5BA0); //tooltip

	//MemorySet(0x00602D14,0x90,0x5);

	//MemorySet(0x004132BC,0x90,0x5);

	g_ServerInfo.Load();
	
	gSmokeEffect.SetLoad();

	gEffectManager.Load();

	//Liberar CS Skills
	if(gProtect.m_MainInfo.EnableCSSKill == 1 )
	{
		SetByte(0x00599C2F + 2, 0x00);
		SetByte(0x00599C34 + 2, 0x00);
		SetByte(0x00599C39 + 2, 0x00);
		SetByte(0x00599C3E + 2, 0x00);
		SetByte(0x00599C43 + 2, 0x00);
		SetByte(0x00599C48 + 2, 0x00);
		//----
		SetByte(0x00599734 + 2, 0x00);
		SetByte(0x00599739 + 2, 0x00);
		SetByte(0x0059973E + 2, 0x00);
		SetByte(0x00599743 + 2, 0x00);
		SetByte(0x00599748 + 2, 0x00);
		SetByte(0x0059974D + 2, 0x00);
	}

	ReadyWeapon();
	//SetByte(0x0054238E + 1, 0xFF);
	//SetByte(0x00542848 + 1, 0xFF);
	//SetByte(0x005426B9 + 1, 0xFF); --desativa ctrl

	//MemorySet(0x00602C03 ,0x90,0x5);
	
	//SetOp((LPVOID)0x00624E70, (LPVOID)ItemNoExcellent, ASM::JMP);
	SetOp((LPVOID)0x0053E26C, (LPVOID)GlobalMessage, ASM::JMP);

	//MemorySet(0x005E9185, 0x90, 0x5);
	//SetDword(0x005E71C8+2,0x0A8F); item position venon
//	SetFloat((LPVOID)0x758810,0.19f); //cima ou baixo venon
//	SetFloat((LPVOID)0x7581CC,0.19f); //lado ou outro venon

	//SetOp((LPVOID)0x004714C2, (LPVOID)CreatePetEffect, ASM::CALL);
	//SetOp((LPVOID)0x004E7786, (LPVOID)CreatePetEffect, ASM::CALL);

	gCustomItemPosition.PositionItemLoad();

	}
	else
	{
		ExitProcess(0);
	}
}


char CreatePetEffect(int Arg1, char Arg2)
{
	float v2; // ST14_4@3
	float v3; // ST10_4@3
	char v5; // [sp+17h] [bp-15h]@3
	int v6; // [sp+18h] [bp-14h]@18
	float v7; // [sp+1Ch] [bp-10h]@21
	float v8; // [sp+20h] [bp-Ch]@21
	float v9; // [sp+24h] [bp-8h]@21
	float v10; // [sp+28h] [bp-4h]@20

	vec3_t Color;
	Vector(0.f, 0.f, 0.f, Color);

	vec3_t Color2;
	Vector(0.f, 0.f, 0.f, Color2);

	vec3_t Color3;
	Vector(0.f, 0.f, 0.f, Color3);

	vec3_t Color4;
	Vector(0.f, 0.f, 0.f, Color4);

	vec3_t Color5;
	Vector(0.f, 0.f, 0.f, Color5);

	if (*(BYTE*)(Arg1)) //ok
	{
		if (Arg2)//ok
		{
			v5 = 1;//ok
		}
		else
		{
			v2 = *(float *)(Arg1 + 20) * 0.0099999998;//ok
			v3 = *(float *)(Arg1 + 16) * 0.0099999998;//ok
			v5 = pObjectGetAngle(v3, v2, -20);
		}
		*(BYTE*)(Arg1 + 416) = v5;
		if (*(BYTE*)(Arg1 + 416)) //ok
		{
			if (*(WORD *)(*(DWORD*)(Arg1 + 316) + 2) != 641 && *(WORD *)(Arg1 + 2) != 7305)
				return 1;
			if (Arg2)
			{
				*(DWORD*)(Arg1 + 12) = *(DWORD*)(Arg1 + 12);
			}
		
			else if (pMainState == 2)
			{
				*(DWORD*)(Arg1 + 12) = 1065353216;
			}
			else if (pMainState == 4)
			{
				*(DWORD*)(Arg1 + 12) = 1065353216;
			}
			else if (*(WORD *)(Arg1 + 2) != 364
				&& *(WORD *)(Arg1 + 2) != 366
				&& *(WORD *)(Arg1 + 2) != 365
				&& *(WORD *)(Arg1 + 2) != 367)
			{
				*(DWORD *)(Arg1 + 12) = 1065353216;
			}

			v6 = 0;
			if ((*(DWORD *)(*(DWORD *)(Arg1 + 316) + 168) & 0x4000) == 0x4000)
			v6 = 10;
			pObjectMaxBug(Arg1, 0, 0, v6);
			v10 = (double)(sub_007396FD() % 30 + 70) * 0.0099999998;
			// ----
			/*if (*(DWORD*)(Arg1 + 2) == ObjectId(13, 0))
			{
				v7 = v10 * 0.5;
				v8 = v10 * 0.80000001;
				v9 = v10 * 0.60000002;
				Vector(0.94, 0.812f, 0.5358f, Color);
				pCreateSpriteEx(1707, Arg1 + 16, 1065353216, (int)&Color, Arg1, 0, 0);
			}*/
			if (*(DWORD*)(Arg1 + 2) == ObjectId(13, 0))
			{
				Vector(1.0f, 0.58f, 0.00f, Color);
				//Vector(0.94f, 0.834f, 0.553f, Color);
				pCreateParticleEx(1733, Arg1 + 16, Arg1 + 24, (int)Color, 11, 0.5f, Arg1);
				Vector(1.0f, 0.58f, 0.00f, Color2);
				pCreateParticleEx(1733, Arg1 + 16, Arg1 + 24, (int)Color2, 11, 0.4f, Arg1);
				Vector(1.0f, 0.58f, 0.00f, Color3);
				pCreateParticleEx(1733, Arg1 + 16, Arg1 + 24, (int)Color3, 11, 0.3f, Arg1);
				Vector(1.0f, 0.58f, 0.00f, Color4);
				pCreateParticleEx(1733, Arg1 + 16, Arg1 + 24, (int)Color4, 11, 0.2f, Arg1);
				Vector(1.0f, 0.58f, 0.00f, Color5);
				pCreateParticleEx(1733, Arg1 + 16, Arg1 + 24, (int)Color5, 11, 0.1f, Arg1);
			}

			// -----------
		}
	}
	return 1;
}

__declspec(naked) void GlobalMessage() // OK
{
	static DWORD ADDR = 0x0053E272;

	_asm
	{
		CMP EDX,1200
		JMP [ADDR]
	}

}

void __declspec(naked) ItemNoExcellent()
{
	static DWORD ItemNoExcellent_Address2 = 0x00624E7C;

	_asm
	{
		MOV EDX,DWORD PTR SS:[EBP+0x8]
		MOVSX EAX,WORD PTR DS:[EDX+0x2]
		CMP EAX,0x29F
		JMP [ItemNoExcellent_Address2]
	}

}

BOOL APIENTRY DllMain(HMODULE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			gController.Load((HINSTANCE)hModule);
			break;
		case DLL_PROCESS_DETACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}