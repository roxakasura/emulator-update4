#include "stdafx.h"

int valor = 0;

void PlayerGuildLogo(int a1, int a2, char *a3)
{
	int guild = 1;
	int result = *(DWORD *)(a3 + 628);

	if (*(BYTE *)(result + 856) == 255)
	{
		guild = 0;
	}

	//-- Revisão se tem guild ou não
	if (guild == 0)
	{
		valor = 0;
	}
	else
	{
		CreateGuildMark(*(WORD *)(result + 482), 1);
		RenderBitmap(0x22, a1 - 18, a2 + 2, 16.0, 16.0, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
	}
	
	RenderBoolean(a1,a2,a3);
}

void Testando001(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{	
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

		// - Função Modificada
	char path20[200];
	sprintf_s(path20, "Logo\\Interface015.tga");
	pLoadImageTga(path20, 100, 9728, 10496, 0, 1);
	RenderBitmap(100, 64.0, 448.0, 256.0, 32.0, 0, 0, 1.0, 1.0, 1, 1, 0); //webzenlogo recriado

	// - Função Modificada
	char path[200];
	sprintf_s(path, "Logo\\Interface011.tga");
	pLoadImageTga(path, 12, 9728, 10496, 0, 1);
	RenderBitmap(12, 320.0, 0.0, 256.0, 86.0, 0, 0, 1.0, 0.671875, a10, a11, a12); //webzenlogo recriado
}

void Testando011(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2+ 64.0, a3, 256.0, 86.0, a6, a7, a8, 0.671875, a10, a11, a12); //webzenlogo original redimensionado
}

void Testando002(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path2[200];
	sprintf_s(path2, "Logo\\Interface012.tga");
	pLoadImageTga(path2, 13, 9728, 10496, 0, 1);
	RenderBitmap(13, 576.0, 0.0, 64.0, 256.0, a6, a7, a8, a9, a10, a11, a12); //webzenlogo recriado
}

void Testando012(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, 0.0, 0.0, 64.0, 256.0, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado
}


void Testando003(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path3[200];
	sprintf_s(path3, "Logo\\Interface013.tga");
	pLoadImageTga(path3, 14, 9728, 10496, 0, 1);
	RenderBitmap(14, 576.0, 256.0, 64.0, 224.0, a6, a7, a8, a9, a10, a11, a12); //webzenlogo recriado
}

void Testando013(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	//DEBUG
	//char Status[50], Status2[50];

	//sprintf_s(Status, "X: %d", CursorX);
	//sprintf_s(Status2, "Y: %d", CursorY);
	//// ---
	//pDrawInfo(100, 105, Status, (160 * *(GLsizei*)MAIN_RESOLUTION_X / 640), 7, 1);
	//pDrawInfo(100, 115, Status2, (160 * *(GLsizei*)MAIN_RESOLUTION_X / 640), 7, 1);
	
	// - Função Original
	RenderBitmap(a1, 0.0, 256.0, 64.0, 224.0, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado
}

void Testando004(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path4[200];
	sprintf_s(path4, "Logo\\Interface014.tga");
	pLoadImageTga(path4, 15, 9728, 10496, 0, 1);
	RenderBitmap(15, 320.0, 448.0, 256.0, 32.0, 0, 0, 1.0, 1.0, 1, 1, 0); //webzenlogo recriado

}

void TestandoDelete(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path5[200];
	sprintf_s(path5, "Logo\\Delete011.tga");
	pLoadImageTga(path5, 18, 9728, 10496, 0, 1);
	RenderBitmap(18, a2, 116.0, 205.0, 88.0, 0, 0, 0.80078125, 0.6875, 1, 1, 0); //webzenlogo recriado
}

void TestandoConfirm(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path6[200];
	sprintf_s(path6, "Logo\\Ok011.tga");
	pLoadImageTga(path6, 20, 9728, 10496, 0, 1);
	RenderBitmap(20, a2, 116.0, 205.0, 88.0, 0, 0, 0.80078125, 0.6875, 1, 1, 0); //webzenlogo recriado
}

void TestandoCreateChar(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path8[200];
	sprintf_s(path8, "Logo\\New_Character211.tga");
	pLoadImageTga(path8, 16, 9728, 10496, 0, 1);
	RenderBitmap(16, 221.0, a3 - 30, 199.0, 109.0, 0, 0, 0.77734375, 0.8515625, 1, 1, 0); //webzenlogo recriado
}

void TestandoDisplayCreateChar01(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path7[200];
	sprintf_s(path7, "Logo\\New_Character011.tga");
	pLoadImageTga(path7, 22, 9728, 10496, 0, 1);
	RenderBitmap(22, 214.0, a3 - 30, 213.0, 256.0, 0, 0, 0.83203125, 1.0, 1, 1, 0); //webzenlogo recriado
}

void TestandoDisplayCreateChar02(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path9[200];
	sprintf_s(path9, "Logo\\New_Character021.tga");
	pLoadImageTga(path9, 23, 9728, 10496, 0, 1);
	RenderBitmap(23, 214.0, a3 - 30, 213.0, 119.0, 0, 0, 0.83203125, 0.9296875, 1, 1, 0); //webzenlogo recriado
}

void TestandoClassTypeMove(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)
{
	// ---
	pDrawInfo(a1 - 0, a2 - 7, a3, a4, a5, a6);
}

void TestandoDisplayCreateCharButtonOK(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path10[200];
	sprintf_s(path10, "Logo\\New_Character97_Ok.jpg");
	pLoadImage(path10, 25, 9728, 10496, 0, 1);
	RenderBitmap(25, 335.0, a3, 72.0, 21.0, 0, 0, 0.5625, 0.65625, 1, 1, 0); //webzenlogo recriado
}

void TestandoDisplayCreateCharButtonCancel(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path14[200];
	sprintf_s(path14, "Logo\\New_Character97_Cancel.jpg");
	pLoadImage(path14, 24, 9728, 10496, 0, 1);
	RenderBitmap(24, 235.0, a3, 72.0, 21.0, 0, 0, 0.5625, 0.65625, 1, 1, 0); //webzenlogo recriado
}

void TestandoDisplayCreateCharButtonPrevious(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	RenderBitmap(a1, 363.0, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo recriado
}

void TestandoDisplayCreateCharButtonNext(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	RenderBitmap(a1, 384.0, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo recriado
}

void TestandoConfirm1(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path11[200];
	sprintf_s(path11, "Logo\\Ok021.jpg");
	pLoadImage(path11, 21, 9728, 10496, 0, 1);
	RenderBitmap(21, a2, 148.0, 70.0, 19.0, 0, 0, 0.546875, 0.59375, 1, 1, 0); //webzenlogo recriado
}

void TestandoDelete1(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path12[200];
	sprintf_s(path12, "Logo\\Delete021.jpg");
	pLoadImage(path12, 19, 9728, 10496, 0, 1);
	RenderBitmap(19, a2, 148.0, 70.0, 19.0, 0, 0, 0.546875, 0.59375, 1, 1, 0); //webzenlogo recriado
}

void TestandoCreateChar1(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2 - 25000, a3 - 25000, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado

	// - Função Modificada
	char path13[200];
	sprintf_s(path13, "Logo\\New_Character212.jpg");
	pLoadImage(path13, 17, 9728, 10496, 0, 1);
	RenderBitmap(17, 286.0, a3 - 1, 70.0, 25.0, 0, 0, 0.546875, 0.78125, 1, 1, 0); //webzenlogo recriado
}

__declspec(naked) void TestandoPositionCreateCharEventClick()
{
	static DWORD ADDSx = 0x006232C0;

	_asm
	{
		LEA EAX, DWORD PTR DS : [ECX + 76]
		JMP [ADDSx]
	}
}

__declspec(naked) void TestandoPositionDeleteImage()
{
	static DWORD ADDSx = 0x00626138;

	_asm
	{
		LEA EAX, DWORD PTR DS : [ESI + 128] //0x67
		TEST BL, BL
		MOV DWORD PTR SS : [EBP - 0xC], EAX
		JMP[ADDSx]
	}
}

__declspec(naked) void TestandoPositionDeleteEventClick01()
{
	static DWORD ADDSx = 0x006233BD;

	_asm
	{
		ADD EAX, 0x80
		TEST DL, DL
		JMP[ADDSx]
	}
}
__declspec(naked) void TestandoPositionDeleteEventClick02()
{
	static DWORD ADDSx = 0x006233D0;

	_asm
	{
		ADD EAX, 0x46
		CMP EDI, EAX
		JMP[ADDSx]
	}
}

void PlayerLoad()
{
	if (gProtect.m_MainInfo.InterfaceType == 1)
	{
		MemorySet(0x006249E5, 0x90, 0x5); //imagem final de baixo
		//
		//Cenários - Imagens Redimensionadas (97d)
		MemorySet(0x006092D6, 0x90, 0x5);
		SetCompleteHook(0xE8, 0x006248D4, &Testando001);
		SetCompleteHook(0xE8, 0x006248FE, &Testando011);
		//
		MemorySet(0x006092F0, 0x90, 0x5);
		SetCompleteHook(0xE8, 0x0062492E, &Testando002);
		SetCompleteHook(0xE8, 0x0062495B, &Testando012);
		//
		MemorySet(0x0060930A, 0x90, 0x5);
		SetCompleteHook(0xE8, 0x0062498B, &Testando003);
		SetCompleteHook(0xE8, 0x006249B8, &Testando013);
		//
		MemorySet(0x00609327, 0x90, 0x5);
		SetCompleteHook(0xE8, 0x006249E5, &Testando004);

		//Botão OK, Create Char e Delete
		//Botão Delete 100%
		MemorySet(0x00609378, 0x90, 5); //delete
		MemorySet(0x00609392, 0x90, 5);
		SetCompleteHook(0xE8, 0x00626128, &TestandoDelete);
		SetCompleteHook(0xE8, 0x00626188, &TestandoDelete1);
		SetCompleteHook(0xE9, 0x006233B8, &TestandoPositionDeleteEventClick01);//EventClick
		SetCompleteHook(0xE9, 0x006233CB, &TestandoPositionDeleteEventClick02);//EventClick
		SetCompleteHook(0xE9, 0x00626130, &TestandoPositionDeleteImage);//image
		SetDword(0x006233E3 + 2, 0x0A7);//EventClick
		SetByte(0x00626144 + 2, 70); //image
		SetDword(0x00626150 + 1, 148); //image
		SetDword(0x00626157 + 1, 167); //image
		SetByte(0x00626106 + 2, 0); //image
		//Botão OK 100%
		MemorySet(0x006093AC, 0x90, 5); //ok
		MemorySet(0x006093C9, 0x90, 5); //Button OK
		SetCompleteHook(0xE8, 0x006261CA, &TestandoConfirm);
		SetCompleteHook(0xE8, 0x00626229, &TestandoConfirm1);
		SetByte(0x006261D2 + 2, 7);
		SetByte(0x006261E5 + 2, 70);
		SetDword(0x006261F1 + 1, 148);
		SetDword(0x006261F8 + 1, 167);
		SetDword(0x0062619A + 1, 434);
		//Botão Create 100%
		MemorySet(0x00609341, 0x90, 0x5); //create
		MemorySet(0x0060935B, 0x90, 0x5); //
		SetCompleteHook(0xE8, 0x0062605C, &TestandoCreateChar);
		SetCompleteHook(0xE8, 0x006260BB, &TestandoCreateChar1);
		SetCompleteHook(0xE9, 0x006232BA, &TestandoPositionCreateCharEventClick);//eventclick y
		SetDword(0x006232B4 + 2, 286); //eventclick x
		SetDword(0x006232C6 + 2, 356); //eventclick
		SetByte(0x006232E0 + 2, 0x19); //eventclick
		SetDword(0x0062606D + 2, 0x11E); //image
		SetDword(0x00626078 + 2, 0x164); //image
		SetByte(0x0062606A + 2, 0x2E); //image y
		SetByte(0x0062608A + 2, 0x19); //image

		//Tela de criação de personagem  - Imagens 
		MemorySet(0x006093E3, 0x90, 0x5); //display create part1
		SetCompleteHook(0xE8, 0x00625A80, &TestandoDisplayCreateChar01);
		MemorySet(0x006093FD, 0x90, 0x5); //display create part1
		SetCompleteHook(0xE8, 0x00625ABB, &TestandoDisplayCreateChar02);
		MemorySet(0x00609434, 0x90, 0x5); //display create button ok
		SetCompleteHook(0xE8, 0x00625D20, &TestandoDisplayCreateCharButtonOK);
		SetDword(0x00625CD8 + 2, 335); //valor 1 button ok
		SetDword(0x00625CE3 + 2, 407); //valor 2 button ok
		SetDword(0x00625C63 + 2, 349 - 30); //valor 3 button ok
		SetByte(0x00625CEF + 2, 0x15); //valor 4 button ok
		MemorySet(0x0060941A, 0x90, 0x5); //display create button cancel
		SetCompleteHook(0xE8, 0x00625CBC, &TestandoDisplayCreateCharButtonCancel);
		SetDword(0x0062386F + 2, 349 - 30); //Event Click OK + Cancel
		//Display Previous
		SetCompleteHook(0xE8, 0x00625B26, &TestandoDisplayCreateCharButtonPrevious);
		SetDword(0x00625AC9 + 2, 196-30);
		SetDword(0x00625ACF + 2, 363);
		SetDword(0x00625ADA + 2, 383);
		SetByte(0x00625AEC + 2, 0x13);
		SetDword(0x00625B60 + 1, 0x43B68000);
		SetDword(0x00623721 + 1, 363);
		SetDword(0x00623735 + 1, 383);
		SetDword(0x00623729 + 2, 196 - 30);
		SetByte(0x00623746 + 2, 0x13);
		//Display Next
		SetCompleteHook(0xE8, 0x00625BF7, &TestandoDisplayCreateCharButtonNext);
		SetDword(0x00625B9A + 2, 196 - 30);
		SetDword(0x00625BA0 + 2, 384);
		SetDword(0x00625BAB + 2, 404);
		SetByte(0x00625BBD + 2, 0x13);
		SetDword(0x00625C33 + 1, 0x43C00000);
		SetDword(0x006237BB + 1, 0x167);
		SetDword(0x006237C6 + 1, 0x194);
		SetByte(0x006237DE + 2, 0x13);
		SetDword(0x00623729 + 2, 196 - 30);
		//
		//Mover Texto de classes - Textos
		SetCompleteHook(0xE8, 0x00625E44, &TestandoClassTypeMove);
		SetDword(0x000625F0C + 1, 283); //PosX dos Avatares
		SetByte(0x00625F06 + 2, 60); //PosY dos Avatares
		SetDword(0x00625D3C + 2, 180-30);	//Y Nomes do personagem a se criar
		SetDword(0x00625DB3 + 1, 284);	//X Nomes do personagem a se criar
		SetByte(0x00609578 + 1, 6); // - Uso do Logo06.bmd

		//Remove Effects Scene 99b
		MemorySet(0x00624A8D,0x90,0x5);	
		MemorySet(0x00624ABA,0x90,0x5);
		MemorySet(0x00624B08,0x90,0x5);
		MemorySet(0x00624B43,0x90,0x5);
		MemorySet(0x00624B8A,0x90,0x5);
		MemorySet(0x00624BE2,0x90,0x5);
		MemorySet(0x00624C53,0x90,0x5);
		MemorySet(0x00624CA2,0x90,0x5);
		MemorySet(0x00624D05,0x90,0x5);
		MemorySet(0x00624D54,0x90,0x5);
		MemorySet(0x00624DAC,0x90,0x5);
		MemorySet(0x00624E11,0x90,0x5);
		MemorySet(0x00624E71,0x90,0x5);
		MemorySet(0x00624EE2,0x90,0x5);
		MemorySet(0x00624F60,0x90,0x5);
		MemorySet(0x00624FC5,0x90,0x5);
		MemorySet(0x00625022,0x90,0x5);
		MemorySet(0x0062506E,0x90,0x5);
		MemorySet(0x006250BD,0x90,0x5);
		MemorySet(0x0062510C,0x90,0x5);
	}

	//
	// - Para ativá-lo o Logo05.bmd têm que estar ativo
	//
	if (gProtect.m_MainInfo.InterfaceType == 0)
	{
		SetDword(0x006094BA+1,(DWORD)"Logo\\back11.jpg"); //push    offset aLogoBack1_jpg; "Logo\\back1.jpg"
		SetDword(0x006094D7+1,(DWORD)"Logo\\back12.jpg"); //push    offset aLogoBack2_jpg; "Logo\\back2.jpg"
		SetDword(0x00609531+1,(DWORD)"Logo\\back13.jpg"); //push    offset aLogoBack3_jpg; "Logo\\back3.jpg"
		SetDword(0x0060954E+1,(DWORD)"Logo\\back14.jpg"); //push    offset aLogoBack4_jpg; "Logo\\back4.jpg"
	}

	if (gProtect.m_MainInfo.PlayerInfoGuildLogo == 1)
	{
		SetCompleteHook(0xE8, 0x00598C11, &PlayerGuildLogo);
	}
}