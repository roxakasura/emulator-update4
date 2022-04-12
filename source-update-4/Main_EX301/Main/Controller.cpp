#include "stdafx.h"
#include "Controller.h"
#include "Camera3D.h"
#include "Protocol.h"
#include "Protect.h"
#include "Interface.h"
#include "Minimap.h"
// ----------------------------------------------------------------------------------------------

Controller	gController;
// ----------------------------------------------------------------------------------------------

bool Controller::Load(HINSTANCE hins)
{
	if( !this->MouseHook )
	{
		this->MouseHook = SetWindowsHookEx(WH_MOUSE, this->Mouse, hins, GetCurrentThreadId());
		// ----
		if( !this->MouseHook )
		{
			return false;
		}
	}
	// ----
	if( !this->KeyboardHook )
	{
		this->KeyboardHook = SetWindowsHookEx(WH_KEYBOARD, this->Keyboard, hins, GetCurrentThreadId());
		
		if (!this->KeyboardHook)
		{
			return false;
		}
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
	// ----
	switch(wParam)
	{
	case WM_MOUSEMOVE:
		if(GetForegroundWindow() == MuWnd)
		{
			gCamera.Move(Mouse);
		}
		break;
	case WM_MBUTTONDOWN:
		if(GetForegroundWindow() == MuWnd)
		{
			gCamera.SetIsMove(1);
			gCamera.SetCursorX(Mouse->pt.x);
			gCamera.SetCursorY(Mouse->pt.y);
		}
		break;
	case WM_MBUTTONUP:
		if(GetForegroundWindow() == MuWnd)
		{
			gCamera.SetIsMove(0);
		}
		break;
	case WM_MOUSEWHEEL:
		if(GetForegroundWindow() == MuWnd)
		{
			gCamera.Zoom(Mouse);
		}
		break;
	}
	// ----
	return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Keyboard(int nCode, WPARAM wParam, LPARAM lParam) // OK
{
	HWND MuWnd = FindWindow(gProtect.m_MainInfo.WindowName, NULL);

	if (nCode == HC_ACTION)
	{
		if (((DWORD)lParam & (1 << 30)) != 0 && ((DWORD)lParam & (1 << 31)) != 0)
		{
			switch (wParam)
			{
			case VK_F10:
				if (GetForegroundWindow() == MuWnd)
				{
					gCamera.Toggle();
				}
				break;
			case VK_F11:
				if (GetForegroundWindow() == MuWnd)
				{
					gCamera.Restore();
				}
				break;
			default:
				break;
			}
		}
	}

	return CallNextHookEx(gController.KeyboardHook, nCode, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------
