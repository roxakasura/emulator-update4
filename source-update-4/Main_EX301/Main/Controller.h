#pragma once
// ----------------------------------------------------------------------------------------------
#include "WinDef.h"

class Controller
{
public:
	bool	Load(HINSTANCE hins);
	// ----
	static	LRESULT WINAPI Mouse(int Code, WPARAM wParam, LPARAM lParam);
	static	LRESULT WINAPI Keyboard(int Code, WPARAM wParam, LPARAM lParam);
	// ----
	HINSTANCE	Instance;
public:
	HHOOK		MouseHook;
	HHOOK		KeyboardHook;
	// ----
}; extern Controller gController;
// ----------------------------------------------------------------------------------------------