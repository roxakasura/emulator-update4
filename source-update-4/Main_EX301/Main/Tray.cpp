#include "stdafx.h"
#include "Tray.h"

// ----------------------------------------------------------------------------------------------

TrayMode gTrayMode;

HWND MuWnd_traymode = FindWindow("MU", NULL);

// ----------------------------------------------------------------------------------------------

void TrayMode::Load()
{
	this->TempWindowProc	= NULL;
	this->TempIconProc		= NULL;
	this->InTray			= false;
}
// ----------------------------------------------------------------------------------------------


void TrayMode::SwitchState()
{

	if( FindWindow("MU", NULL) )

	{

		ShowWindow(FindWindow("MU", NULL), SW_HIDE);

		UpdateWindow(FindWindow("MU", NULL));
		this->ShowNotify(true);
		this->ShowMessage(NIIF_INFO, "MU Online", "Game has been minimized");
	}

	
	
	else
	{

		ShowWindow(FindWindow("MU Online", NULL), SW_SHOW);
		UpdateWindow(FindWindow("MU Online", NULL));
		this->ShowNotify(false);
	}
	
	

	
}


void TrayMode::Windows()
{

	if( FindWindow("MU", NULL) )
	{
		ShowWindow(FindWindow("MU", NULL), SW_SHOW);
		UpdateWindow(FindWindow("MU", NULL));
		this->ShowNotify(false);
	}



}




// ----------------------------------------------------------------------------------------------

void TrayMode::ShowNotify(bool Mode)
{
	this->InTray = Mode;
	NOTIFYICONDATA Icon		= { 0 };
	// ----
	Icon.cbSize				= sizeof(NOTIFYICONDATA);
	Icon.uID				= TRAYMODE_ICON_ID;
	Icon.uFlags				= NIF_ICON|NIF_MESSAGE|NIF_TIP;
	
	Icon.hIcon				= static_cast<HICON>(::LoadImage(NULL,
    MAKEINTRESOURCE(IDI_WARNING),
    IMAGE_ICON,
    0, 0,
    LR_DEFAULTCOLOR | LR_SHARED | LR_DEFAULTSIZE));

	

	this->TempIconProc		= Icon.hIcon;
	Icon.hWnd				= FindWindow("MU", NULL);
	
	Icon.uCallbackMessage	= TRAYMODE_ICON_MESSAGE;
	// ----
	strcpy_s(Icon.szTip, sizeof(Icon.szTip), "MU Online");
	
	if( Mode )
	{
		Shell_NotifyIcon(NIM_ADD, &Icon);
	}
	else
	{
		Shell_NotifyIcon(NIM_DELETE, &Icon);
	}
	// ----
	DeleteObject(Icon.hIcon);
}
// ----------------------------------------------------------------------------------------------

void TrayMode::ShowMessage(DWORD Type, char * Title, char * Message)
{
	NOTIFYICONDATA Icon		= { 0 };
	// ----
	Icon.cbSize				= sizeof(NOTIFYICONDATA);
	Icon.uID				= TRAYMODE_ICON_ID;
	Icon.hWnd				= FindWindow("MU", NULL);
	
	Icon.uFlags				= NIF_ICON | NIF_MESSAGE | NIF_INFO;
	Icon.hIcon				= this->TempIconProc;
	Icon.uCallbackMessage	= TRAYMODE_ICON_MESSAGE;
	Icon.dwInfoFlags		= Type;
	Icon.uTimeout			= 5000;
	// ----
	strcpy(Icon.szInfo, Message);
	strcpy(Icon.szInfoTitle, Title);
	// ----
	Shell_NotifyIcon(NIM_MODIFY, &Icon);
}
// ----------------------------------------------------------------------------------------------