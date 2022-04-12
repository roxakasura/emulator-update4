// ServerDisplayer.cpp: implementation of the CServerDisplayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServerDisplayer.h"
#include "GameMain.h"
#include "Log.h"
#include "Protect.h"
#include "ServerInfo.h"
#include "SocketManager.h"
#include "User.h"
#include "resource.h"

CServerDisplayer gServerDisplayer;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerDisplayer::CServerDisplayer() // OK
{
	for(int n=0;n < MAX_LOG_TEXT_LINE;n++)
	{
		memset(&this->m_log[n],0,sizeof(this->m_log[n]));
	}

	this->m_font = CreateFont(50,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Times");
	this->m_font3 = CreateFont(15,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"MS Sans Serif");

	this->m_brush[0] = CreateSolidBrush(RGB(105,105,105));
	this->m_brush[1] = CreateSolidBrush(RGB(110,240,120));

	strcpy_s(this->m_DisplayerText[0],"STANDBY MODE");
	strcpy_s(this->m_DisplayerText[1],"ACTIVE MODE");
}

CServerDisplayer::~CServerDisplayer() // OK
{
	DeleteObject(this->m_font);
	DeleteObject(this->m_brush[0]);
	DeleteObject(this->m_brush[1]);
}

void CServerDisplayer::Init(HWND hWnd) // OK
{
	PROTECT_START

	this->m_hwnd = hWnd;

	PROTECT_FINAL

	gLog.AddLog(1,"LOG");

	gLog.AddLog(gServerInfo.m_WriteChatLog,"CHAT_LOG");

	gLog.AddLog(gServerInfo.m_WriteCommandLog,"COMMAND_LOG");

	gLog.AddLog(gServerInfo.m_WriteTradeLog,"TRADE_LOG");

	gLog.AddLog(gServerInfo.m_WriteConnectLog,"CONNECT_LOG");

	gLog.AddLog(gServerInfo.m_WriteHackLog,"HACK_LOG");

	gLog.AddLog(gServerInfo.m_WriteCashShopLog,"CASH_SHOP_LOG");

	gLog.AddLog(gServerInfo.m_WriteChaosMixLog,"CHAOS_MIX_LOG");
}

void CServerDisplayer::Run() // OK
{
	this->LogTextPaint(); //First paint Logs
	
	this->SetWindowName();

	this->PaintAllInfo(); //After paint header
}

void CServerDisplayer::SetWindowName() // OK
{
	char buff[256];

	wsprintf(buff,"[%s] %s - RoxGaming.com.br",GAMESERVER_VERSION,gServerInfo.m_ServerName);

	SetWindowText(this->m_hwnd,buff);

	HWND hWndStatusBar = GetDlgItem(this->m_hwnd, IDC_STATUSBAR);

	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	RECT rect2;

	GetClientRect(hWndStatusBar,&rect2);

	MoveWindow(hWndStatusBar,0,rect.bottom-rect2.bottom+rect2.top,rect.right,rect2.bottom-rect2.top,true);

    int iStatusWidths[] = {90,240,400,580,-1, -1};

    char text[256];

    SendMessage(hWndStatusBar, SB_SETPARTS, 6, (LPARAM)iStatusWidths);

	wsprintf(text, "Update %d", GAMESERVER_CLIENTE_UPDATE);

    SendMessage(hWndStatusBar, SB_SETTEXT, 0,(LPARAM)text);

	wsprintf(text, "Players Online: %d/%d", gObjTotalUser,gServerInfo.m_ServerMaxUserNumber);

    SendMessage(hWndStatusBar, SB_SETTEXT, 1,(LPARAM)text);

	wsprintf(text, "%s",GAMESERVER_TITLE);

    SendMessage(hWndStatusBar, SB_SETTEXT, 2,(LPARAM)text);

	wsprintf(text, "Monsters: %d/%d", gObjTotalMonster,MAX_OBJECT_MONSTER);

    SendMessage(hWndStatusBar, SB_SETTEXT, 3,(LPARAM)text);

    SendMessage(hWndStatusBar, SB_SETTEXT, 4,(LPARAM)NULL);

	SendMessage(hWndStatusBar, SB_SETTEXT, 5,(LPARAM)NULL);

    ShowWindow(hWndStatusBar, SW_SHOW);
}

void CServerDisplayer::PaintAllInfo() // OK
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	rect.top = 0;
	rect.bottom = 80;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font);

	if(gJoinServerConnection.CheckState() == 0 || gDataServerConnection.CheckState() == 0)
	{
		SetTextColor(hdc,RGB(200,200,200));
		FillRect(hdc,&rect,this->m_brush[0]);
		TextOut(hdc,120,20,this->m_DisplayerText[0],strlen(this->m_DisplayerText[0]));
	}
	else
	{
		gGameServerDisconnect = 0;
		SetTextColor(hdc,RGB(250,250,250));
		FillRect(hdc,&rect,this->m_brush[1]);
		TextOut(hdc,120,20,this->m_DisplayerText[1],strlen(this->m_DisplayerText[1]));
	}

	SelectObject(hdc,OldFont);
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::LogTextPaint() // OK
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	rect.top = 80;

	HDC hdc = GetDC(this->m_hwnd);

	FillRect(hdc,&rect,(HBRUSH)GetStockObject(0));

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font3);

	int line = MAX_LOG_TEXT_LINE;

	int count = (((this->m_count-1)>=0)?(this->m_count-1):(MAX_LOG_TEXT_LINE-1));

	for(int n=0;n < MAX_LOG_TEXT_LINE;n++)
	{
		switch(this->m_log[count].color)
		{
			case LOG_BLACK:
				SetTextColor(hdc,RGB(0,0,0));
				break;
			case LOG_RED:
				SetTextColor(hdc,RGB(255,0,0));
				break;
			case LOG_GREEN:
				SetTextColor(hdc,RGB(0,255,0));
				break;
			case LOG_BLUE:
				SetTextColor(hdc,RGB(0,0,255));
				break;
		}

		int size = strlen(this->m_log[count].text);

		if(size > 1)
		{
			TextOut(hdc,0,(65+(line*15)),this->m_log[count].text,size);
			line--;
		}

		count = (((--count)>=0)?count:(MAX_LOG_TEXT_LINE-1));
	}

	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::LogAddText(eLogColor color,char* text,int size) // OK
{
	PROTECT_START

	size = ((size>=MAX_LOG_TEXT_SIZE)?(MAX_LOG_TEXT_SIZE-1):size);

	memset(&this->m_log[this->m_count].text,0,sizeof(this->m_log[this->m_count].text));

	memcpy(&this->m_log[this->m_count].text,text,size);

	this->m_log[this->m_count].color = color;

	this->m_count = (((++this->m_count)>=MAX_LOG_TEXT_LINE)?0:this->m_count);

	PROTECT_FINAL

	gLog.Output(LOG_GENERAL,"%s",&text[9]);
}