#include "stdafx.h"
#include "SelectServerS13.h"
#include "Reconnect.h"
#include "Util.h"

bool SEASON3B_CheckMouseIn(int a1, int a2, int a3, int a4)
{
  return MouseX >= a1 && MouseX < a1 + a3 && MouseY >= a2 && MouseY < a4 + a2;
}

void CharacterSelect360()
{
	int Model;

	for (int i = 0; i < 5; i++)
	{	
		Model = 1148 * i + *(int*)0x74D2B28;
		*(float *)(Model + 36) = *(float *)(Model + 36) + 5.0;  //AQUI É A VELOCIDADE DO GIRO DA 360
	}
}

void CSetInfo(float X, float Y, int Class)
{
	int cHero = *(DWORD *)((sub_463272() + 36584) + 4) + 368 * Class;
	int m_szName = cHero + 176;
	int m_szClass = sub_532400(*(BYTE *)(*(DWORD *)(cHero + 168) + 524));
	char m_szLevel[256];
	wsprintf(m_szLevel, "%d", *(WORD *)(*(DWORD *)(cHero + 168) + 526));
	int m_szGuild = cHero + 240;
	CUIRenderText_SetFont(pTextThis(),g_hFontBold);
	pSetBlend(true);
	pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
	pSetTextColor(pTextThis(), 255, 255, 255, 255);
	pDrawText(pTextThis(), X + 35, Y + 20, (const char *)m_szName, 190, 0, (LPINT)2, 0);
	pDrawText(pTextThis(), X + 11, Y + 7, (const char *)m_szClass, 190, 0, (LPINT)0, 0);
	pDrawText(pTextThis(), X - 50, Y + 20, (const char *)m_szLevel, 190, 0, (LPINT)4, 0);
	pDrawText(pTextThis(), X - 50, Y + 7, (const char *)m_szGuild, 190, 0, (LPINT)4, 0);
}

void CharacterTeleport(int Index, float X, float Y, float Scale, float Rotate)
{
	int Model;
	for(int i = 0 ; i < MAX_CHARACTER ; i++)
	{
		Model = 1148 * i + *(int*)0x74D2B28;
		if(Model)
		{
			if(Index == i)
			{
				*(float *)(Model + 16) = X;
				*(float *)(Model + 20) = Y;
				*(float *)(Model + 12) = Scale;
			}
			else
			{
				*(float *)(Model + 16) = 0;
				*(float *)(Model + 20) = 0;
				*(float *)(Model + 12) = Scale;
			}
		}
	}
}

void ButtonCharacter()
{
	BeginBitmap();
	glColor3f(1.0, 1.0, 1.0);
	CharacterSelect360();
	float X = 471, Y = 51;

	if ( !*(BYTE *)(Instance() + 34244) )
	{
		for ( int i = 0; i < MAX_CHARACTER; ++i )
		{
			//Textura de los Botones
			RenderBitmap(240, X, 37*i+Y, 150, 35, 0, 0, 0.83203125, 1.0, 1, 1, 0.0);
			if (SEASON3B_CheckMouseIn(X, 37*i+Y, 150, 35) || SelectedHero == i)
			{
				glColor3f(0.8, 0.6, 0.4);
				EnableAlphaBlend();
				RenderBitmap(240, X, 37*i+Y, 150, 35, 0, 0, 0.83203125, 1.0, 1, 1, 0.0);
				glColor3f(1.0, 1.0, 1.0);
				DisableAlphaBlend();
			}
			//
			//Informacion de los Botones
			if ( *(BYTE *)(*(int*)0x74D2B28 + 1148 * i) )
			{	
				if (SEASON3B_CheckMouseIn(X, 37*i+Y, 150, 35))
				{
					SelectedCharacter = i;
					{
						if (PressKey(1))
						{
							PlayBuffer(25, 0, 0);
							SelectedHero = i;
							CharacterTeleport(i,12974,15425,1.0,50);
						}
					}
				}
				CSetInfo(X,37*i+Y,i);
			}
			else
			{
				if (SEASON3B_CheckMouseIn(X, 37*i+Y, 150, 35) && PressKey(1))
				{
					PlayBuffer(25, 0, 0);
					ShowWin(Instance(), Instance() + 34232);
				}	
				CUIRenderText_SetFont(pTextThis(),g_hFontBold);
				pSetBlend(true);
				pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
				pSetTextColor(pTextThis(), 255, 255, 255, 255);
				pDrawText(pTextThis(), X-29, 37*i+(Y+13), "Empty Character Slot", 210, 0, (LPINT)3, 0);
			}
			//
		}
	}
}

void CSelectedHero()
{
	((int(*)())0x0045D7C8)();
	CharacterSelect360();
	for ( int i = 0; i < MAX_CHARACTER; ++i )
	{
		if ( *(BYTE *)(*(int*)0x74D2B28 + 1148 * i) )
		{
			SelectedCharacter = i;
			SelectedHero = i;
			CharacterTeleport(i,12974,15425,1.0,50);
			break;
		}
	}
}

void CCreateCharacterPointer(int a1, int a2, char a3, int a4, int a5, int a6)
{
	((int(__cdecl*)(int a1, int a2, char a3, int a4, int a5, int a6))0x00531C16)(a1,a2,a3,0,0,0);
}


void CButtonCharacterS13()
{
	//SetCompleteHook(0xE8,0x0065F0FE, &ButtonCharacter);
	//SetCompleteHook(0xE8,0x0065E9C7, &CSelectedHero);
	//SetCompleteHook(0xE8,0x00673748, &CCreateCharacterPointer);
	//SetByte(0x00402005+6, 0);//Hide character_ex.ozt 
	//SetDword(0x004E7641+3, 0x3fc00000);//Scale Pet
}