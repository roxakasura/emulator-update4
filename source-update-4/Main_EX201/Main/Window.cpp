#include "StdAfx.h"
#include "Window.h"
#include "Offset.h"
#include "Protect.h"
#include "resource.h"
#include "TrayMode.h"
#include "Util.h"

cWindow	gWindow;

cWindow::cWindow()
{

}

cWindow::~cWindow()
{

}

void cWindow::WindowModeLoad(HINSTANCE hins)
{
	this->Instance = hins;

	SetCompleteHook(0xE9, 0x004D4640, 0x004D48D1);

	SetCompleteHook(0xE9, 0x004D32B0, &this->StartWindow);
}

void cWindow::ChangeDisplaySettingsFunction()
{
	DEVMODE DevMode;

	int nModes = 0;

	while (EnumDisplaySettings(NULL, nModes, &DevMode))
	{
		nModes++;
	}

	DEVMODE* pDevmodes = new DEVMODE[nModes + 1];

	nModes = 0;

	while (EnumDisplaySettings(NULL, nModes, &pDevmodes[nModes]))
	{
		nModes++;
	}

	DWORD dwBitsPerPel = 32;

	for (int n1 = 0; n1 < nModes; n1++)
	{
		if (pDevmodes[n1].dmBitsPerPel == 24 || pDevmodes[n1].dmBitsPerPel == 32)
		{
			dwBitsPerPel = pDevmodes[n1].dmBitsPerPel;

			break;
		}
	}

	for (int n2 = 0; n2 < nModes; n2++)
	{
		if (pDevmodes[n2].dmPelsWidth == WindowWidth && pDevmodes[n2].dmPelsHeight == WindowHeight && pDevmodes[n2].dmBitsPerPel == dwBitsPerPel)
		{
			ChangeDisplaySettings(&pDevmodes[n2], 0);

			break;
		}
	}

	delete[] pDevmodes;
}

HWND cWindow::StartWindow(HINSTANCE hCurrentInst, int nCmdShow)
{
	char* windowName = "MU";

	WNDCLASS wndClass;

	wndClass.style = CS_OWNDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

	wndClass.lpfnWndProc = gWindow.MyWndProc;

	wndClass.cbClsExtra = 0;

	wndClass.cbWndExtra = 0;

	wndClass.hInstance = hCurrentInst;

	wndClass.hIcon = LoadIcon(gWindow.Instance, MAKEINTRESOURCE(IDI_ICON));

	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	wndClass.lpszMenuName = NULL;

	wndClass.lpszClassName = windowName;

	RegisterClass(&wndClass);

	HWND hWnd;

	if (g_bUseWindowMode == false)
	{
		hWnd = CreateWindowExA(WS_EX_APPWINDOW | WS_EX_TOPMOST, windowName, gProtect.m_MainInfo.WindowName, WS_POPUP, 0, 0, WindowWidth, WindowHeight, NULL, NULL, hCurrentInst, NULL);

		gWindow.ChangeDisplaySettingsFunction();
	}
	else
	{
		RECT rc = { 0, 0, WindowWidth, WindowHeight };

		AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER | WS_CLIPCHILDREN, NULL);

		hWnd = CreateWindowA(windowName, gProtect.m_MainInfo.WindowName, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER | WS_CLIPCHILDREN, (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2, rc.right, rc.bottom + 28, NULL, NULL, hCurrentInst, NULL);
	}

	return hWnd;
}

LRESULT WINAPI cWindow::MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_NCACTIVATE:
		{
			return 0;
		}
	}

	return CallWindowProc(WndProc, hwnd, msg, wParam, lParam);
}