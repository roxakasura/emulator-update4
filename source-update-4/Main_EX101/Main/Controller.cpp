#include "stdafx.h"
// ----------------------------------------------------------------------------------------------

Controller	gController;
// ----------------------------------------------------------------------------------------------

bool Controller::Load()
{
	if( !this->MouseHook )
	{
		this->MouseHook = SetWindowsHookEx(WH_MOUSE, this->Mouse, gController.Instance, GetCurrentThreadId());
		// ----
		if( !this->MouseHook )
		{
			return false;
		}
	}
	// ----
	if( !this->KeyboardHook )
	{

	}
	// ----
	return true;
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Mouse(int Code, WPARAM wParam, LPARAM lParam)
{
	HWND MuWnd = FindWindow(gProtect.m_MainInfo.WindowName, NULL);

	if( GetForegroundWindow() != MuWnd )
	{
		return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
	}
	// ----
	MOUSEHOOKSTRUCTEX * Mouse	= (MOUSEHOOKSTRUCTEX*)lParam;
	// ----
	gCamera.Run(Mouse, wParam);
	// ----
	switch(wParam)
	{
	}
	// ----
	return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Keyboard(int Code, WPARAM wParam, LPARAM lParam)
{
	HWND MuWnd = FindWindow(gProtect.m_MainInfo.WindowName, NULL);

	if( GetForegroundWindow() != MuWnd )
	{
		return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
	}

	if (Code < 0) return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
	
	if( (Code == HC_ACTION) && (wParam == WM_KEYDOWN))
	{
		KBDLLHOOKSTRUCT Hook = *((KBDLLHOOKSTRUCT*)lParam);
	
		switch(Hook.vkCode)
		{

	case VK_F10:
		if(GetForegroundWindow() == MuWnd)
		{
			if(!gCamera.bSelect)
			{
				gCamera.ViewType(1);
			}
			else
			{
				gCamera.ViewType(2);
			}
		}
		break;

	case VK_F11:
		if(GetForegroundWindow() == MuWnd)
		{
			gCamera.Reset();
		}
		break;
		default:
		break;
		}
	} 
	return (LRESULT) NULL;
	
}
// ----------------------------------------------------------------------------------------------
