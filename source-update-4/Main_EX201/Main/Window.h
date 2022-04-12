#pragma once

class cWindow
{
public:

	cWindow();

	~cWindow();

	void WindowModeLoad(HINSTANCE hins);

private:

	void ChangeDisplaySettingsFunction();

	static HWND StartWindow(HINSTANCE hCurrentInst, int nCmdShow);

	static LONG WINAPI MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HINSTANCE Instance;
};

extern cWindow gWindow;