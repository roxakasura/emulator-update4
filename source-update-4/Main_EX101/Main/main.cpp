#include "StdAfx.h"

std::string g_strSelectedML = "";

HINSTANCE hins;

HICON WINAPI IconProc(HINSTANCE hInstance,LPCSTR lpIconName) // OK
{
	FILE* file;

	gTrayMode.m_TrayIcon = (HICON)LoadImage(hins,".\\Data\\Logo\\main.ico",IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),LR_LOADFROMFILE | LR_DEFAULTCOLOR);

	return gTrayMode.m_TrayIcon;
}

SHORT WINAPI KeysProc(int nCode) // OK
{
	if(GetForegroundWindow() != *(HWND*)(MAIN_WINDOW))
	{
		return 0;
	}

	return GetAsyncKeyState(nCode);
}

extern "C" __declspec (dllexport) void __cdecl LABMU()
{
	DWORD OldProtect;
	// ---
	if (VirtualProtect(LPVOID(0x401000), 4452946, PAGE_EXECUTE_READWRITE, &OldProtect))
	{
		if (gProtect.ReadMainFile("Data/Local/Server.bmd") == 0)
		{
			MessageBox(0, "Main not found or invalid!", "Error", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}

		 *(BYTE*)(0x005FDABC + 2) = 0x7F; // Sword 
		 *(BYTE*)(0x005FDBDD + 2) = 0x7F; // axe  005FDBDD				|. 83FA 09        |CMP EDX,9
		 *(BYTE*)(0x005FDC08 + 2) = 0x7F; // Mace 005FDC08				|. 83F9 07        |CMP ECX,7
		 *(BYTE*)(0x005FDC4C + 2) = 0x7F; // Mace 005FDC4C				|. 83F8 05        |CMP EAX,5
		 *(BYTE*)(0x005FDC90 + 2) = 0x7F; // Spear 005FDC90			|. 83FA 0A        |CMP EDX,0A
		 *(BYTE*)(0x005FDCD4 + 2) = 0x7F; // Shields 005FDCD4			|. 83F9 0F        |CMP ECX,0F
		 *(BYTE*)(0x005FDD2E + 2) = 0x7F; // Staff 005FDD2E			|. 83F8 09        |CMP EAX,9
		 *(BYTE*)(0x005FDDF1 + 2) = 0x7F; // Bow 005FDDF1				|. 83FA 07        |CMP EDX,7
		 *(BYTE*)(0x005FDE1C + 2) = 0x7F; // CrossBow 005FDE1C			|. 83F9 07        |CMP ECX,7
		 *(BYTE*)(0x005FEE76 + 2) = 0x7F; // Textura 005FEE76			|. 83F9 11        |CMP ECX,11
		 *(BYTE*)(0x005FCC2C + 2) = 0x7F; // Textura 005FCC2C			|. 83F8 11        |CMP EAX,11
		 *(BYTE*)(0x005FBDBF + 2) = 0x7F; // HelM Male 005FBDBF		|. 83FA 0A        |CMP EDX,0A
		 *(BYTE*)(0x005FC2DF + 2) = 0x7F; // HelM MaleTesT 005FC2DF	|. 83F8 04        |CMP EAX,4
		 *(BYTE*)(0x005FC372 + 2) = 0x7F; // HelM Male 005FC372		|. 83FA 04        |CMP EDX,4
		 *(BYTE*)(0x005FC3FD + 2) = 0x7F; // Helm Male 005FC3FD		|. 83F8 04        |CMP EAX,4

		 gSmokeEffect.SetLoad();

		EmptyWorkingSet(GetCurrentProcess());

		//SetByte(0x00542854 + 2, 0); //AUTOCTRL ATIVO

		// Projeto completar interface downgrade s6 se basear por isso
		//MemorySet(0x005DCACD,0x90,0x5); //IAMGEM 1
		//MemorySet(0x005DCB02,0x90,0x5); //IMAGEM 2

		if(gProtect.m_MainInfo.TransparencyItem == 1)
		{
			//Sistema transparência 100%
			MemorySet(0x005F9D6D,0x90,0x5);
			MemorySet(0x005F9D4E,0x90,0x5);
			MemorySet(0x005F9D31,0x90,0x5);
			MemorySet(0x005F9C9B,0x90,0x5);
			MemorySet(0x005F9D09,0x90,0x5);
		
			//Inicia a transparência a partir do level 12
			SetByte(0x005F9C5C+2,13);
			SetByte(0x005F9BC8+2,12);
			////Inicia a transparência a partir do level 14
			//SetByte(0x005F9CB9+2,14);
			//SetByte(0x005F9C5C+2,14);
			//SetByte(0x005F9BC8+2,14);
			SetByte(0x00509F56+1,11); // Fix Elf Soldier Brilho + 13
		}
		
		if(gProtect.m_MainInfo.InterfaceType == 1)
		{
			// Remove Status Char + Position Name Character
			MemorySet(0x0062563F,0x90,0x5); //Remove status
			SetByte(0x0062553E+2,0);
		}

		SetDword(0x006A74D0,(DWORD)&IconProc);
		SetDword(0x006A74FC,(DWORD)&KeysProc);

		if(gProtect.m_MainInfo.ExperienceType == 1)
		{
			gAddons.Load();
		}

		SetByte(0x006B6654, 0xA0); // Accent
		SetByte(0x004B4305, 0xEB); // Crack (mu.exe)
		SetByte(0x004B47FE, 0x75); // config.ini read error
		SetByte(0x004B4856, 0xE9); // Crack (GameGuard)
		SetByte(0x004B4857, 0xA6); // Crack (GameGuard)
		SetByte(0x004B4858, 0x00); // Crack (GameGuard)
		SetByte(0x004B4859, 0x00); // Crack (GameGuard)
		SetByte(0x004B485A, 0x00); // Crack (GameGuard)
		SetByte(0x004BEA9F, 0xEB); // Crack (ResourceGuard)
		SetByte(0x004519F8, 0x02); // Ctrl Fix
		SetByte(0x006B7248, (gProtect.m_MainInfo.ClientVersion[0] + 1)); // Version
		SetByte(0x006B7249, (gProtect.m_MainInfo.ClientVersion[2] + 2)); // Version
		SetByte(0x006B724A, (gProtect.m_MainInfo.ClientVersion[3] + 3)); // Version
		SetByte(0x006B724B, (gProtect.m_MainInfo.ClientVersion[5] + 4)); // Version
		SetByte(0x006B724C, (gProtect.m_MainInfo.ClientVersion[6] + 5)); // Version*/
		SetWord(0x006C41BC, (gProtect.m_MainInfo.IpAddressPort)); // IpAddressPort
		MemoryCpy(0x006B6EFC, gProtect.m_MainInfo.WindowName, sizeof(gProtect.m_MainInfo.WindowName)); //WindowName
		SetDword(0x00628B89, (DWORD)gProtect.m_MainInfo.ScreenShotPath); //Screenshot
		MemoryCpy(0x006B6694, gProtect.m_MainInfo.IpAddress, sizeof(gProtect.m_MainInfo.IpAddress)); // IpAddress
		MemoryCpy(0x006B7250, gProtect.m_MainInfo.ClientSerial, sizeof(gProtect.m_MainInfo.ClientSerial)); // ClientSerial
		//MemorySet(0x0041DBB0, 0x90, 29); // Remove MuError.log

		//MemorySet(0x0063F835,0x90,0x5); // AQUI REMOVE O GUILD CREATE DATE

		//Liberar CS Skills
		if (gProtect.m_MainInfo.CSSkillCheck == 1)
		{
			*(BYTE*)(0x5951F9 + 1) = 0x2B;
			*(BYTE*)(0x5951FE + 1) = 0x26;
			*(BYTE*)(0x595203 + 1) = 0x21;
			*(BYTE*)(0x595208 + 1) = 0x1C;
			*(BYTE*)(0x59520D + 1) = 0x17;
			*(BYTE*)(0x595212)     = 0xEB;
			*(BYTE*)(0x5956D5 + 2) = 0x00;
			*(BYTE*)(0x5956DA + 2) = 0x00;
			*(BYTE*)(0x5956DF + 2) = 0x00;
			*(BYTE*)(0x5956E4 + 2) = 0x00;
			*(BYTE*)(0x5956E9 + 2) = 0x00;
			*(BYTE*)(0x5956EE + 2) = 0x00;
		}

		// Fix ServerList
		SetDword(0x61F3DA, 0xFF);
		SetDword(0x61F3E0, 0xFF);
		SetDword(0x61F431, 0x120);
		SetByte(0x61F463, 0x4C);
		SetDword(0x61F7E0, 0xFC);
		SetDword(0x61F814, 0x16D);
		SetDword(0x61F81F, 0x1F3);
		SetDword(0x61FE1D, 0xFF);
		SetDword(0x61FE24, 0xFF);
		SetDword(0x61FE8F, 0x118);
		SetDword(0x61FE9E, 0x127);
		SetDword(0x61FEC7, 0x127);
		SetDword(0x61FE8F, 0x11D);
		SetDword(0x61FF12, 0x3F700000);
		SetDword(0x6201B7, 0x3F700000);
		SetDword(0x6201D6, 0x43B68000);
		SetDword(0x620251, 0x1B0);
		SetFloat(0x6A9788, 383.0f);

		// Fix ServerList
		MemorySet(0x0062594A, 0x90, 0x05); // Remove Text Select Screen 1
		MemorySet(0x00625996, 0x90, 0x05); // Remove Text Select Screen 2
		MemorySet(0x006259E2, 0x90, 0x05); // Remove Text Select Screen 3

		// Fix Move Cursor
		MemorySet(0x004CBC66, 0x90, 0x06);

		// Fix Modo Janela
		SetDword(0x004B36EB, (DWORD)(&WndProc));

		//Protocolo
		SetCompleteHook(0xFF, 0x004DB63D, &ProtocolCoreEx);

		gCustomItem.Load(gProtect.m_MainInfo.CustomItemInfo);

		gCustomJewel.Load(gProtect.m_MainInfo.CustomJewelInfo);

		gCustomWing.Load(gProtect.m_MainInfo.CustomWingInfo);

		gCustomItemDescription.Load(gProtect.m_MainInfo.CustomDescriptionInfo);

		gCustomWingEffect.Load(gProtect.m_MainInfo.CustomWingEffectInfo);

		gDynamicWingEffect.Load(gProtect.m_MainInfo.DynamicWingEffectInfo);
	
		gSmokeEffect.Load(gProtect.m_MainInfo.CustomSmokeEffect);
		
		gCustomMap.Load(gProtect.m_MainInfo.CustomMapInfo);

		gCustomMonster.Load(gProtect.m_MainInfo.CustomMonsterInfo);

		gPacketManager.LoadEncryptionKey("Data\\Enc1.dat");

		gPacketManager.LoadDecryptionKey("Data\\Dec2.dat");

		gProtect.CheckClientFile();

		gProtect.CheckPlugin1File();

		gProtect.CheckPlugin2File();

		InitHackCheck();

		InitResolution();

		InitPrintPlayer();

		//InitReconnect();

		gInterface.Load();

		InitItem();

		InitJewel();

		InitWing();

		InitMap();

		InitMonster();

		if (gProtect.m_MainInfo.MiniMapCheck == 1)
		{
			ReadyMiniMap();
		}

		gController.Load();

		gFont.Load();

		if (gProtect.m_MainInfo.RemoveKeyM == 1)
		{
			*(BYTE*)(0x00594ADF + 1) = 0x2F;		// [#] Remove letra M
			MemorySet(0x00444417,0x90,0x5); //Remover M por completo
		}
		if (gProtect.m_MainInfo.RemoveKeyD == 1)
		{
			*(BYTE*)(0x00594B18 + 1) = 0x2F;		// [#] Remove letra D
			// - COMMAND FUNCTION
			*(BYTE*)(0x59028D) = 0x90;
			*(BYTE*)(0x59028D + 1) = 0x90;
			*(BYTE*)(0x59028D + 2) = 0x90;
			*(BYTE*)(0x59028D + 3) = 0x90;
			*(BYTE*)(0x59028D + 4) = 0x90;
			// - COMMAND TEXT
			*(BYTE*)(0x408ADF) = 0x90;
			*(BYTE*)(0x408ADF + 1) = 0x90;
			*(BYTE*)(0x408ADF + 2) = 0x90;
			*(BYTE*)(0x408ADF + 3) = 0x90;
			*(BYTE*)(0x408ADF + 4) = 0x90;
		}
		if (gProtect.m_MainInfo.RemoveKeyF == 1)
		{
			*(BYTE*)(0x00594AA6 + 1) = 0x2F;		// [#] Remove letra F
			// - FRIEND FUNCTION
			*(BYTE*)(0x590237) = 0x90;
			*(BYTE*)(0x590237 + 1) = 0x90;
			*(BYTE*)(0x590237 + 2) = 0x90;
			*(BYTE*)(0x590237 + 3) = 0x90;
			*(BYTE*)(0x590237 + 4) = 0x90;
			// - FRIEND TEXT
			*(BYTE*)(0x599764) = 0x90;
			*(BYTE*)(0x599764 + 1) = 0x90;
			*(BYTE*)(0x599764 + 2) = 0x90;
			*(BYTE*)(0x599764 + 3) = 0x90;
			*(BYTE*)(0x599764 + 4) = 0x90;

		}
		if (gProtect.m_MainInfo.RemoveKeyT == 1)
		{
			*(BYTE*)(0x005949BF + 1) = 0x2F;		// [#] Remove letra T
			// - BOTAO QUEST GRAPHICAL
			MemorySet(0x41AFDB, 0x90, 5);
			MemorySet(0x41B019, 0x90, 5);
			MemorySet(0x41B01E, 0x90, 5);
			MemorySet(0x41B052, 0x90, 5);
			MemorySet(0x419B62, 0x90, 2);
			MemorySet(0x419B6B, 0x90, 5);
		}
		if (gProtect.m_MainInfo.RemoveKeyS == 1)
		{
			*(BYTE*)(0x005D3DF6 + 1) = 0x2F;		// [#] Remove letra S
			// - PSHOP FUNCTION
			*(BYTE*)(0x5D3DB6) = 0x90;
			*(BYTE*)(0x5D3DB6 + 1) = 0x90;
			*(BYTE*)(0x5D3DB6 + 2) = 0x90;
			*(BYTE*)(0x5D3DB6 + 3) = 0x90;
			*(BYTE*)(0x5D3DB6 + 4) = 0x90;
			// - PSHOP GRAPHICAL
			*(BYTE*)(0x5E14A2) = 0xE9;
			*(BYTE*)(0x5E14A2 + 1) = 0x28;
			*(BYTE*)(0x5E14A2 + 2) = 0x02;
			*(BYTE*)(0x5E14A2 + 3) = 0x00;
			*(BYTE*)(0x5E14A2 + 4) = 0x00;
			*(BYTE*)(0x5E14A2 + 5) = 0x90;
		}

		if (gProtect.m_MainInfo.RemovePetDisplay == 1)
		{
			// - BOTAO  PET GRAPHICAL
			MemorySet(0x5E5C55, 0x90, 5);
			MemorySet(0x422CD2, 0x90, 5);
		}
		if (gProtect.m_MainInfo.InterfaceType == 1)
		{
			SetDword(0x006097CA + 1, (DWORD)"Interface\\Menu011_new.jpg");
			SetDword(0x00609802 + 1, (DWORD)"Interface\\Menu013_new.jpg");
		}

		if (gProtect.m_MainInfo.RemoveSetItemAncient == 1)
		{
			MemorySet(0x40CBE0, 0x90, 0x128); //Removido ItemSetOtion + Image
			MemorySet(0x0040C670, 0x90, 0x509); //Removido ToolTip ancient
		}

		if(gProtect.m_MainInfo.SelectCharAnime == 1)
		{
			gSelectChar.Load();
		}

		if (gProtect.m_MainInfo.ItemLevel15 == 1)
		{ 
			gcItem.ItemLoad();
		}

		if (gProtect.m_MainInfo.RightClick == 1)
		{
			RightClickLoad();
		}

		if (gProtect.m_MainInfo.LoadingWhite == 1)
		{
			LoadWebzenLogo();
		}

		MemorySet(0x0060F0A2,0x90,0x5); //remove filter data
		//MemorySet(0x548620,0x90,0xB2); //remove todos os textos de interface
		//MemorySet(0x0060EFD7,0x90,0x5);


		//MemorySet(0x5F8640,0x90,0x1921); antilag transparency chars
		//MemorySet(0x4E75B0,0x90,0x1CA); antilag objects
		//*(BYTE*)(0x00506FAD+1) = 0x8C;
		//*(BYTE*)(0x005F9CC2+2) = 0x10;// +15 com cor
		*(BYTE*)(0x4B4E6D + 1) = ANTIALIASED_QUALITY;
		*(BYTE*)(0x4B4DED + 1) = ANTIALIASED_QUALITY;
		*(BYTE*)(0x4B4E2D + 1) = ANTIALIASED_QUALITY;
		*(BYTE*)(0x6B6654) = DEFAULT_CHARSET; 

		// Character dragging - ao atacar não deslizar 
		if(gProtect.m_MainInfo.RemoveDraggingSkill == 1)
		{
			SetByte(0x550B25, 0xE9);
			SetByte(0x550B26, 0xEE);
			SetByte(0x550B27, 0x00);
			SetByte(0x550B28, 0x00);
			SetByte(0x550B29, 0x00);
			SetByte(0x550B2A, 0x90);
		}

		g_ServerInfo.Load();

		gCustomItemDescription.Init();

		gEffectManager.Load();
		
		gUser.Load();

		PlayerLoad();

		SetOp((LPVOID)0x00548B5F, (LPVOID)GlobalMessage, ASM::JMP);
		
		//OpenInitFile();
		//
		//Console.Init();
		//
		//if (_stricmp(gSelection, "ENG") == 0)
		//{
		//	SetDword(0x0060AFE8+1,(DWORD)"Data\\Local\\Eng\\Text_eng.bmd");
		//	SetDword(0x0060B006+1,(DWORD)"Data\\Local\\Eng\\Text_eng.bmd");
		//	SetDword(0x0060AD1E+1,(DWORD)"Data\\Local\\Eng\\Dialog_eng.bmd");
		//	SetDword(0x0060AD31+1,(DWORD)"Data\\Local\\Eng\\Quest_eng.bmd");
		//}
		//
		//if (_stricmp(gSelection, "POR") == 0)
		//{
		//	SetDword(0x0060AFE8+1,(DWORD)"Data\\Local\\Por\\Text_por.bmd");
		//	SetDword(0x0060B006+1,(DWORD)"Data\\Local\\Por\\Text_por.bmd");
		//	SetDword(0x0060AD1E+1,(DWORD)"Data\\Local\\Por\\Dialog_por.bmd");
		//	SetDword(0x0060AD31+1,(DWORD)"Data\\Local\\Por\\Quest_por.bmd");
		//}
		//
		//if (_stricmp(gSelection, "SPN") == 0)
		//{
		//	SetDword(0x0060AFE8+1,(DWORD)"Data\\Local\\Spn\\Text_spn.bmd");
		//	SetDword(0x0060B006+1,(DWORD)"Data\\Local\\Spn\\Text_spn.bmd");
		//	SetDword(0x0060AD1E+1,(DWORD)"Data\\Local\\Spn\\Dialog_spn.bmd");
		//	SetDword(0x0060AD31+1,(DWORD)"Data\\Local\\Spn\\Quest_spn.bmd");
		//}

		// ---
		if(gToolKit.Registry("WindowMode") > 0)
		{
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach((&(LPVOID&)(pCreateWindowExA)), dtCreateWindowExA);
			DetourAttach((&(LPVOID&)(pChangeDisplaySettingsA)), dtChangeDisplaySettingsA);
			DetourTransactionCommit();
		}
	}
	else
	{
		MessageBoxA(NULL, "Arquivo 'Main.dll' não foi carregado !'", "Main.exe - Erro !", MB_OK);
		ExitProcess(0);
	}
}

__declspec(naked) void GlobalMessage() // OK
{
	static DWORD ADDR = 0x00548B65;

	_asm
	{
		CMP EDX,1200
		JMP [ADDR]
	}

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// ---
		LABMU();
		// ---
		break;
	case DLL_PROCESS_DETACH:
		// ---
		if(gToolKit.Registry("WindowMode") > 0)
		{
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourDetach((&(LPVOID&)(pCreateWindowExA)), dtCreateWindowExA);
			DetourDetach((&(LPVOID&)(pChangeDisplaySettingsA)), dtChangeDisplaySettingsA);
			DetourTransactionCommit();
		}
		// ---
//		gController.Load();
		// ---
		break;
	}
	// ---
	return TRUE;
}