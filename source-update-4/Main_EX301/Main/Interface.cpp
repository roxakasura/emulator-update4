#include "stdafx.h"
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
#include "Console.h"
#include "EventTime.h"

int JanelaTeste = 0;

Interface	gInterface;

void Interface::Load()
{
	SetOp((LPVOID)0x0059D3F8, this->Work, ASM::CALL);
	//SetCompleteHook(0xE8, 0x005E9185, &TestandoItemDraw);
	//MemorySet(0x404E87, 0x90, 0x230);
	//MemorySet(0x40542A, 0x90, 0x1FF);
}
void Interface::Work()
{
	((void(__cdecl*)()) 0x004D7566)();

	ReconnectMainProc();
	//Novas Janelas
	gCustomEventTime.DrawEventTimePanelWindow();
		
//	gInterface.DebugFuction();

	HWND MuWnd = FindWindow(gProtect.m_MainInfo.WindowName, NULL);

	if (GetKeyState(VK_TAB) & 0x4000)
	{
		if (GetForegroundWindow() == MuWnd)
		{
			if (gProtect.m_MainInfo.MiniMapCheck == 1)
			{
				HookMiniMap();
			}
		}
	}

	//if(pCheckMouseOver(412,215,15,15,1) && pClickCursor)

	if (GetKeyState('H') & 0x4000 && GetTickCount() >= gInterface.timeboolVar + 250)
	{
		if (GetForegroundWindow() == MuWnd && !pChatWindow)
		{
			if (JanelaTeste == 0)
			{
				JanelaTeste = 1;

				gInterface.SetCursorFocus(1);

				gCustomEventTime.ClearCustomEventTime();

				PMSG_CUSTOM_EVENTTIME_SEND pMsg;

				pMsg.header.set(0xF3, 0xE8, sizeof(pMsg));

				DataSend((BYTE*)&pMsg, pMsg.header.size);
			}
			else
			{

				JanelaTeste = 0;

				gInterface.SetCursorFocus(0);
			}

			gInterface.timeboolVar = GetTickCount();
		}
	}

	if (GetKeyState(VK_ESCAPE) < 0)
	{
		if (JanelaTeste == 1)
		{
			JanelaTeste = 0;
			gInterface.SetCursorFocus(0);
		}
	}
}

void Interface::SetCursorFocus(int state)
{
	if(state != 1)
	{
		//Primeira Verificação (Button OK)
		SetDword(0x00654CB2 + 1, 40); //40
		SetDword(0x00654CB7 + 1, 323); //323
		SetDword(0x00654CA6 + 1, 70); //70
		SetDword(0x00654CAB + 1, 234); //234
		//Segunda Verificação (Button Cancel)
		SetDword(0x00656B13 + 1, 40); //40
		SetDword(0x00656B18 + 1, 373); //373
		SetDword(0x00656B07 + 1, 70); //70
		SetDword(0x00656B0C + 1, 334); //334

		SetCompleteHook(0xE8, 0x0065D4A9, 0x00658280);  //DISABLE PSETCURSORFOCUS INTERFACE
		SetCompleteHook(0xE8, 0x0065F112, 0x00658280);  //DISABLE PSETCURSORFOCUS INTERFACE
		SetCompleteHook(0xE8, 0x0065FDBE, 0x00658280);  //DISABLE PSETCURSORFOCUS INTERFACE
		SetCompleteHook(0xE8, 0x006619BB, 0x00658280);  //DISABLE PSETCURSORFOCUS INTERFACE

		pSetCursorFocus = 0;
	}
	else
	{
		pSetCursorFocus = 125;
		MemorySet(0x0065D4A9, 0x90, 0x5);  //DISABLE PSETCURSORFOCUS INTERFACE
		MemorySet(0x0065F112, 0x90, 0x5);  //DISABLE PSETCURSORFOCUS INTERFACE
		MemorySet(0x0065FDBE, 0x90, 0x5);  //DISABLE PSETCURSORFOCUS INTERFACE
		MemorySet(0x006619BB, 0x90, 0x5);  //DISABLE PSETCURSORFOCUS INTERFACE
		//Primeira Verificação (Button OK)
		SetDword(0x00654CB2 + 1, 0); //40
		SetDword(0x00654CB7 + 1, 0); //323
		SetDword(0x00654CA6 + 1, 0); //70
		SetDword(0x00654CAB + 1, 0); //234
		//Segunda Verificação (Button Cancel)
		SetDword(0x00656B13 + 1, 0); //40
		SetDword(0x00656B18 + 1, 0); //373
		SetDword(0x00656B07 + 1, 0); //70
		SetDword(0x00656B0C + 1, 0); //334
	}
}

void Interface::DebugFuction()
{
	char szBuffer[256] = {0};
	// ---
	pSetBlend(true);
	// ---
	sprintf(szBuffer, "x: %d // y: %d",pCursorX,pCursorY);
	// ---
	pDrawText(pTextThis(), 50, 80, szBuffer, 500, 0, (LPINT)3, 0);
}

void Interface::LoadImagem(int Type, char * Folder, int ImageID)
{
	switch(Type)
	{
	case 0:
		{
			pLoadImageJPG(Folder, ImageID, 0x2600, 0x2900, 0, 1); // -> JPG
		}
		break;
	case 1:
		{
			pLoadImageTGA(Folder, ImageID, 0x2600, 0x2900, 0, 1); // -> TGA
		}
		break;
	}
}

void Interface::DrawGUI(int ObjectId, float X, float Y, float Width, float Height, float ScaleX, float ScaleY)
{
	pDrawGUI(ObjectId, X, Y, Width, Height, 0, 0, ScaleX, ScaleY, 1, 1);
}

bool Interface::IsWorkZone(short ObjectID)
{
	if ((gUser.m_CursorX < this->Data[ObjectID].X || gUser.m_CursorX > this->Data[ObjectID].MaxX) || (gUser.m_CursorY < this->Data[ObjectID].Y || gUser.m_CursorY > this->Data[ObjectID].MaxY))
		return false;

	return true;
}

void Interface::DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}
/*
void WindowCustom()
{
	if (JanelaTeste != 0)
	{
		int result;
		float v1; float v2; float v3; float v4; float v5; float v6;
		signed int i;

		v1 = (double)60;	//Posição Y das Janelas
		v2 = (double)220;	//Largura das Janelas
		v4 = (double)210;	//Posição X das Janelas

		v3 = (double)(12); //Y barra de cima
		RenderBitmap(252, v4, v3 + v1, v2, 5.0, 0, 0, 0.83203125, 0.625, 1, 1, 0.0);

		for (i = 0; i < 7; ++i)
		{
			v5 = (double)12 + (double)(40 * i + 5); //Y do fundo
			RenderBitmap(251, v4, v5 + v1, v2, 40.0, 0, 0, 0.83203125, 0.625, 1, 1, 0.0);
		}

		v6 = (double)(12) + 280.0; //Y barra de baixo
		RenderBitmap(252, v4, v6 + v1, v2, 5.0, 0, 0, 0.83203125, 0.625, 1, 1, 0.0);

		char Title[256];
		char TitleEvent[256];
		char TitleTime[256];
		// --- Título
		pSetBlend(true);
		pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
		wsprintf(Title, "Time Events");
		pDrawText(pTextThis(), v4 + 90, v1 + 30, Title, 0, 0, (PINT)3, 0);
		// --- Event Name
		pSetBlend(true);
		pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
		wsprintf(TitleEvent, "Event:");
		pDrawText(pTextThis(), v4 + 45, v1 + 41, TitleEvent, 0, 0, (PINT)3, 0);
		// --- Event Time
		pSetBlend(true);
		pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
		wsprintf(TitleTime, "Time:");
		pDrawText(pTextThis(), v4 + 145, v1 + 41, TitleTime, 0, 0, (PINT)3, 0);

	}
}*/

int TestandoItemDraw(int ItemID, int a2, int a3, int a4, int a5, int a6, char a7)
{
	return pDrawItemModel(ITEM2(14, 13), a2, a3, a4, a5, a6 + 5, a7 +5);
}
