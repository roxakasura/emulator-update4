#include "stdafx.h"

Interface	gInterface;

void Interface::Load()
{
	SetOp((LPVOID)0x00596E7F, this->Work, ASM::CALL);
}

void Interface::Work()
{
	ReconnectMainProc();

	HWND MuWnd = FindWindow(gProtect.m_MainInfo.WindowName, NULL);

	if (GetKeyState(VK_F10) & 0x4000) 
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

	if (GetKeyState(VK_F11) & 0x4000) 

		if(GetForegroundWindow() == MuWnd)
		{
			gCamera.Reset();
		}


	((void(__cdecl*)()) 0x00598C30)();
}

void Interface::LoadImage(int Type, char * Folder, int ImageID)
{
	switch(Type)
	{
	case 0:
		{
			pLoadImage(Folder, ImageID, 0x2600, 0x2900, 0, 1); // -> JPG
		}
		break;
	case 1:
		{
			pLoadImageTga(Folder, ImageID, 0x2600, 0x2900, 0, 1); // -> TGA
		}
		break;
	}
}