#include "StdAfx.h"

HWND (WINAPI* pCreateWindowExA)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID) = CreateWindowExA;
LONG (WINAPI* pChangeDisplaySettingsA)(DEVMODEA*, DWORD) = ChangeDisplaySettingsA;

HWND WINAPI dtCreateWindowExA(DWORD ExStyle, LPCSTR ClassName, LPCSTR WindowName, DWORD Style, int X, int Y, int Width, int Height, HWND Parent, HMENU Menu, HINSTANCE Instance, LPVOID Parameter)
{
	if (IS_INTRESOURCE(ClassName))
	{
		return pCreateWindowExA(ExStyle, ClassName, WindowName, Style, X, Y, Width, Height, Parent, Menu, Instance, Parameter);
	}
	// ---
	if (_stricmp(ClassName, gProtect.m_MainInfo.WindowName) == 0) //WS_MINIMIZEBOX | 
	{
		int SizeX = Width, SizeY = Height, ScreenX = GetSystemMetrics(SM_CXSCREEN), ScreenY = GetSystemMetrics(SM_CYSCREEN), X2 = (ScreenX / 2) - (SizeX / 2), Y2 = (ScreenY / 2) - (SizeY / 2);
		// ---
		HWND Window = pCreateWindowExA(0, ClassName, WindowName, WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, X2, Y2, SizeX, SizeY +28, 0, 0, Instance, Parameter);
		// ---
		SetWindowPos(Window, NULL, X2, Y2, 0, 0, SWP_NOSIZE);
		// ---
		return Window;
	}
	// ---
	return pCreateWindowExA(ExStyle, ClassName, WindowName, Style, X, Y, Width, Height, Parent, Menu, Instance, Parameter);
}

LONG WINAPI dtChangeDisplaySettingsA(DEVMODEA* DevMode, DWORD Flag)
{
	 UNREFERENCED_PARAMETER(DevMode);
	 UNREFERENCED_PARAMETER(Flag);
	 // ---
	 return DISP_CHANGE_SUCCESSFUL;
}

LRESULT CALLBACK WndProc(HWND Window, UINT Message, WPARAM W, LPARAM L)
{
	switch (Message)
	{
		case WM_NCACTIVATE:
		{
			return 0;
		}
		break;
	}
	// ---
	return CallWindowProc(eWndProc, Window, Message, W, L);
}