#include "stdafx.h"
#include "Camera.h"
#include "Controller.h"
#include "Offset.h"
#include "resource.h"
#include "Util.h"
#include "TrayMode.h"

Controller gController;

void Controller::Load(HINSTANCE hins)
{
	this->Instance = hins;

	if (!this->MouseHook)
	{
		this->MouseHook = SetWindowsHookEx(WH_MOUSE, this->Mouse, this->Instance, GetCurrentThreadId());

		if (!this->MouseHook)
		{
			return;
		}
	}

	if (!this->KeyboardHook)
	{
		this->KeyboardHook = SetWindowsHookEx(WH_KEYBOARD, this->Keyboard, this->Instance, GetCurrentThreadId());

		if (!this->KeyboardHook)
		{
			return;
		}
	}

	SetDword(0x006E8430, (DWORD)&GetAsyncKeyStateHook);
}

LRESULT Controller::Mouse(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		MOUSEHOOKSTRUCTEX* HookStruct = (MOUSEHOOKSTRUCTEX*)lParam;

		switch (wParam)
		{
			case WM_MOUSEMOVE:
			{
				if (GetForegroundWindow() == g_hWnd)
				{
					gCamera.Move(HookStruct);
				}

				break;
			}

			case WM_MBUTTONDOWN:
			{
				if (GetForegroundWindow() == g_hWnd)
				{
					gCamera.SetIsMove(1);

					gCamera.SetCursorX(HookStruct->pt.x);

					gCamera.SetCursorY(HookStruct->pt.y);
				}

				break;
			}

			case WM_MBUTTONUP:
			{
				if (GetForegroundWindow() == g_hWnd)
				{
					gCamera.SetIsMove(0);
				}

				break;
			}

			case WM_MOUSEWHEEL:
			{
				if (GetForegroundWindow() == g_hWnd)
				{
					gCamera.Zoom(HookStruct);
				}

				break;
			}

			default:
			{
				break;
			}
		}
	}

	return CallNextHookEx(gController.MouseHook, nCode, wParam, lParam);
}

LRESULT Controller::Keyboard(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		if (((DWORD)lParam & (1 << 30)) != 0 && ((DWORD)lParam & (1 << 31)) != 0)
		{
			switch (wParam)
			{
				case VK_F10:
				{
					if (GetForegroundWindow() == g_hWnd)
					{
						gCamera.Toggle();
					}

					break;
				}

				case VK_F11:
				{
					if (GetForegroundWindow() == g_hWnd)
					{
						gCamera.Restore();
					}

					break;
				}

				case VK_F12:
				{
					if (GetForegroundWindow() == g_hWnd)
					{
						gTrayMode.Toggle();
					}

					break;
				}

				default:
				{
					break;
				}
			}
		}
	}

	return CallNextHookEx(gController.KeyboardHook, nCode, wParam, lParam);
}

SHORT WINAPI Controller::GetAsyncKeyStateHook(int key)
{
	if (GetForegroundWindow() != g_hWnd)
	{
		return 0;
	}

	return GetAsyncKeyState(key);
}