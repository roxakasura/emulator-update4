// TrayMode.cpp: implementation of the CTrayMode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Protect.h"
#include "TrayMode.h"

CTrayMode gTrayMode;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrayMode::CTrayMode() // OK
{
	this->m_MainWndProc = 0;
}

void CTrayMode::Toggle() // OK
{
	if(this->GetMainWndProc() != 0)
	{
		if(IsWindowVisible(*(HWND*)(MAIN_WINDOW)) == 0)
		{
			ShowWindow(*(HWND*)(MAIN_WINDOW),SW_SHOW);

			this->ShowNotify(0);
		}
		else
		{
			ShowWindow(*(HWND*)(MAIN_WINDOW),SW_HIDE);

			this->ShowNotify(1);
		}
	}
}

LONG CTrayMode::GetMainWndProc() // OK
{
	return ((this->m_MainWndProc==0)?((LONG)(this->m_MainWndProc=(WNDPROC)SetWindowLong(*(HWND*)(MAIN_WINDOW),GWL_WNDPROC,(LONG)CTrayMode::TrayModeWndProc))):((LONG)this->m_MainWndProc));
}

void CTrayMode::ShowNotify(bool mode) // OK
{
	NOTIFYICONDATA nid;

	memset(&nid,0,sizeof(nid));

	nid.cbSize = sizeof(NOTIFYICONDATA);

	nid.hWnd = *(HWND*)(MAIN_WINDOW);

	nid.uID = WM_TRAY_MODE_ICON;

	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;

	nid.uCallbackMessage = WM_TRAY_MODE_MESSAGE;

	nid.hIcon = this->m_TrayIcon;

	wsprintf(nid.szTip,"SSeMU Client");

	Shell_NotifyIcon(((mode==0)?NIM_DELETE:NIM_ADD),&nid);
}

LRESULT CALLBACK CTrayMode::TrayModeWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) // OK
{
	switch(message)
	{
		case WM_TRAY_MODE_MESSAGE:
			switch(lParam)
			{
				case WM_LBUTTONDBLCLK:
					gTrayMode.Toggle();
					break;
				default:
					break;
			}
		default:
			break;
	}

	return CallWindowProc((WNDPROC)gTrayMode.GetMainWndProc(),hWnd,message,wParam,lParam);
}