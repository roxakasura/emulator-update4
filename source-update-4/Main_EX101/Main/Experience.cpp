#include "stdafx.h"
#include "Experience.h"
#include "Interface.h"
#include "Util.h"
#include "User.h"
#include "Protocol.h"
#include "Protect.h"
#include "Reconnect.h"
#include "PrintPlayer.h"
#include "Camera3D.h"
#include "Minimap.h"
#include "PlayerSystem.h"
#include "RightClick.h"

CAddons gAddons;

char gSelection[4] = {'\0'};

BOOL OpenInitFile()
{
	HKEY hKey;
	DWORD dwDisp;
	DWORD dwSize;

	if ( ERROR_SUCCESS == RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, & hKey, &dwDisp))
	{
		dwSize = 4;
		if ( RegQueryValueEx (hKey, "LangSelection", 0, NULL, (LPBYTE)gSelection, &dwSize) != ERROR_SUCCESS)
		{
			strcpy(gSelection, "Eng");
		}
	}

	RegCloseKey( hKey);

	return TRUE;
}


void CAddons::Load()
{
	this->gLevelExperience[0] = 0;

	int over = 1;

	for(int n=1;n <= 1000;n++)
	{
		//this->gLevelExperience[n] = (((n+9)*n)*n)*10;

		if(n > 255)
		{	
			this->gLevelExperience[n] += (((over + 9)*over)*over) * 2 + (over + 9)*over*over * 1;
			//this->gLevelExperience[n] += (((over+9)*over)*over)*1000;
			over++;
		}
	}

	SetCompleteHook(0xE9, 0x0059B560,this->ExperienceSettings);
}

void CAddons::ExperienceSettings()
{
	int v0; // ebp@1
	unsigned int v1; // eax@1
	bool v2; // cf@4
	BYTE *v3; // eax@6
	unsigned int v4; // ecx@8
	int v5; // eax@8
	int v6; // eax@11
	double v7; // st7@11
	double v8; // st6@11
	unsigned int v9; // eax@16
	int v10; // eax@17
	unsigned __int8 v11; // cl@19
	double v12; // st7@21
	float v13; // ST14_4@24
	int v14; // eax@24
	double v15; // st7@25
	double v16; // st7@27
	DWORD *v17; // eax@30
	void *v18; // eax@33
	int v19; // ST18_4@35
	char *v20; // ebp@36
	unsigned int v21; // edx@36
	unsigned int v22; // eax@42
	unsigned int v23; // eax@43
	char v24; // cl@45
	char v25; // [sp+Ch] [bp-84h]@0
	float v26; // [sp+1Ch] [bp-74h]@1
	__int64 v27; // [sp+20h] [bp-70h]@1
	int v28; // [sp+28h] [bp-68h]@11
	CHAR String; // [sp+2Ch] [bp-64h]@35
	
	float fNeedExp = gUser.m_Player.NextExperience - gAddons.gLevelExperience[gUser.m_Player.Level-1];

	// Experience
	float fExp = gUser.m_Player.Experience - gAddons.gLevelExperience[gUser.m_Player.Level-1];

	if(gUser.m_Player.Experience < gAddons.gLevelExperience[gUser.m_Player.Level-1])
	{
		fExp = 0.f;
	}

	// Progess Bar (0 ~ 9)
	float fExpBarNum = 0.f;

	if(fExp > 0.f && fNeedExp > 0)
	{
		fExpBarNum = (fExp / fNeedExp) * 10.f;
	}

	int iExp = (int)fExpBarNum;

	float ReduceRate	= 0.0;

	DWORD PreviousExp = gUser.m_Player.Experience - gAddons.gLevelExperience[gUser.m_Player.Level-1];
	DWORD TotalExp    = gUser.m_Player.NextExperience - gAddons.gLevelExperience[gUser.m_Player.Level-1];

//	char Experiencia3[200];
//	sprintf(Experiencia3,"Exp2:%d / Next2:%d / Level2: %d",gUser.m_Player.Experience,gUser.m_Player.NextExperience,gUser.m_Player.Level);
//	Console.Write(Experiencia3,0,1);
//
//	char Experiencia2[200];
//	sprintf(Experiencia2,"Exp:%d / Next:%d / Level: %d",ViewExperience,ViewNextExperience,gUser.m_Player.Level);
//	Console.Write(Experiencia2,0,1);

	if ( TotalExp > 0 )
		ReduceRate = ((float)TotalExp - (float)PreviousExp) / (float)TotalExp;

	if (ReduceRate < 0)
		ReduceRate = 1.0;
	
	float Width		= 198.0;
	float Height	= 4.0;
	float PosX		= 221.0;
	float PosY		= 439.0;

	float FinalW	= Width - ReduceRate * Width;

	if ( *(WORD *)(*(DWORD*)0x7666A78 + 14) )
	{
		glColor3f(0.92000002, 0.80000001, 0.34);
		pDrawBarForm(PosX, PosY, FinalW, Height, 0.0, 0);
		pSetBlend(1);
		glColor3f(0.91000003, 0.81, 0.60000002);
		((double(*)(double))0x0068EF68)(v26);
		((void(*)(float,float,DWORD,float,float))0x0060DA80)(425.0, 434.0, iExp, 9.0, 10.0);
		((void(*)())0x60CB10);
		glColor3f(1.0, 1.0, 1.0);
	}

	if(pCursorX  >= 219.0 && pCursorX < 421.0 &&  pCursorY >= 439.0 && pCursorY < 445.0 )
	{
		char Experiencia[200];
		sprintf(Experiencia,"Exp : %d/%d",ViewExperience,ViewNextExperience);
		pDrawToolTip(223, 424,Experiencia);
	}
}




















/*	__int64 dwNexExperience = *(DWORD *)(*(DWORD*)0x074D2C58 + 20);
	__int64 dwExperience	= *(DWORD *)(*(DWORD*)0x074D2C58 + 16);
	
	char XPCommon[256];
		// Next Experience
	float fNeedExp = gUser.m_Player.NextExperience - gAddons.gLevelExperience[gUser.m_Player.Level-1];

	// Experience
	float fExp = gUser.m_Player.Experience - gAddons.gLevelExperience[gUser.m_Player.Level-1];

	if(gUser.m_Player.Experience < gAddons.gLevelExperience[gUser.m_Player.Level-1])
	{
		fExp = 0.f;
	}

	// Progess Bar (0 ~ 9)
	float fExpBarNum = 0.f;

	if(fExp > 0.f && fNeedExp > 0)
	{
		fExpBarNum = (fExp / fNeedExp) * 10.f;
	}

	int iExp = (int)fExpBarNum;

	float ReduceRate	= 0.0;

	double PreviousExp = gUser.m_Player.Experience - gAddons.gLevelExperience[gUser.m_Player.Level-1];
	double TotalExp    = gUser.m_Player.NextExperience - gAddons.gLevelExperience[gUser.m_Player.Level-1];

	//char Experiencia[200];
	//sprintf(Experiencia,"Exp:%d / Next:%d / Level: %d",gUser.m_Player.Experience,gUser.m_Player.NextExperience,gUser.m_Player.Level);
	//Console.Write(Experiencia,0,1);

	char Experiencia2[200];
	sprintf(Experiencia2,"Exp:%d / Next:%d / Level: %d",ViewExperience,ViewNextExperience,gUser.m_Player.Level);
	Console.Write(Experiencia2,0,1);

	if ( TotalExp > 0 )
		ReduceRate = (TotalExp - PreviousExp) / TotalExp;

	if (ReduceRate < 0)
		ReduceRate = 1.0;
	
	float Width		= 198.0;
	float Height	= 4.0;
	float PosX		= 221.0;
	float PosY		= 439.0;

	float FinalW	= Width - ReduceRate * Width;

	 pSetBlend(1);
	 glColor3f(0.92000002, 0.80000001, 0.34);
	 pDrawBarForm(PosX, PosY, FinalW, Height, 0.0, 0);
	 ((void(*)())0x64388A);
	 pSetBlend(1);
	 glColor3f(0.91000003, 0.81, 0.60000002);
	 glColor3f(1.0, 1.0, 1.0);
	 ((void(*)(float,float,DWORD,float,float))0x006435D6)(425.0, 434.0, iExp, 9.0, 10.0);
	 ((void(*)())0x642209);
     glColor3f(1.0, 1.0, 1.0);*/