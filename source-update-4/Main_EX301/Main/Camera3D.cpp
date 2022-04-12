#include "stdafx.h"
#include "Camera3D.h"
#include "Util.h"

CCamera gCamera;

CCamera::CCamera()
{
	this->m_Enable = 0;

	this->m_IsMove = 0;

	this->m_CursorX = 0;

	this->m_CursorY = 0;

	this->m_Zoom.MinPercent = 50.0;

	this->m_Zoom.MaxPercent = 300.0;

	this->m_Zoom.Precision = 2.0;

	this->m_Address.Zoom = (float*)0x00660390; //35.0f (zooming in/out)

	this->m_Address.RotX = (float*)0x07AFE994; //-45.0f (rotate left/right)

	this->m_Address.RotY = (float*)0x00758A30; //-48.5f (rotate up/down)

	this->m_Address.PosZ = (float*)0x00757994; //150.0f (additional value for correct Y rotating)

	this->m_Address.ClipX = (float*)0x007588B4; //1190.0f (area filled with textures, x value)

	this->m_Address.ClipY = (float*)0x00608347; //2400.0f (area filled with textures, y value)

	this->m_Address.ClipZ = (float*)0x006606B8; //2000.0f (camera range of view x,y,z -> background)

	this->m_Address.ClipXCS = (float*)0x007588C0; //580.0f

	this->m_Address.ClipYCS = (float*)0x006081B3; //3300.0f

	this->m_Address.ClipZCS = (float*)0x00660657; //2000.0f (camera range of view x,y,z -> background)

	this->m_Default.IsLoad = 0;

	SetCompleteHook(0xE9, 0x006435AF, &RotateFix);
}

void CCamera::Toggle()
{
	if (*(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_Enable ^= 1;

		if (((this->m_Default.IsLoad == 0) ? (this->m_Default.IsLoad++) : this->m_Default.IsLoad) == 0)
		{
			this->m_Default.Zoom = (*this->m_Address.Zoom);

			this->m_Default.RotX = (*this->m_Address.RotX);

			this->m_Default.RotY = (*this->m_Address.RotY);

			this->m_Default.PosZ = (*this->m_Address.PosZ);

			this->m_Default.ClipX = (*this->m_Address.ClipX);

			this->m_Default.ClipY = (*this->m_Address.ClipY);

			this->m_Default.ClipZ = (*this->m_Address.ClipZ);

			this->m_Default.ClipXCS = (*this->m_Address.ClipXCS);

			this->m_Default.ClipYCS = (*this->m_Address.ClipYCS);

			this->m_Default.ClipZCS = (*this->m_Address.ClipZCS);
		}

		//pDrawMessage(((this->m_Enable) ? "Camera Control Activated" : "Camera Control Desctivated"), 1);
	}
}

void CCamera::Restore()
{
	if (this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->SetDefaultValue();
		//pDrawMessage("Camera Restored", 1);
	}
}

void CCamera::SetIsMove(BOOL IsMove)
{
	if (this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_IsMove = IsMove;
	}
}

void CCamera::SetCursorX(LONG CursorX)
{
	if (this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_CursorX = CursorX;
	}
}

void CCamera::SetCursorY(LONG CursorY)
{
	if (this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_CursorY = CursorY;
	}
}

void CCamera::Zoom(MOUSEHOOKSTRUCTEX* lpMouse)
{
	if (this->m_Enable == 0 || this->m_IsMove != 0 || *(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	this->m_Zoom.MinLimit = (this->m_Default.Zoom / 100)*this->m_Zoom.MinPercent;

	this->m_Zoom.MaxLimit = (this->m_Default.Zoom / 100)*this->m_Zoom.MaxPercent;

	if (((int)lpMouse->mouseData) > 0)
	{
		if ((*this->m_Address.Zoom) >= this->m_Zoom.MinLimit)
		{
			SetFloat2((DWORD)this->m_Address.Zoom, ((*this->m_Address.Zoom) - this->m_Zoom.Precision));
		}
	}

	if (((int)lpMouse->mouseData) < 0)
	{
		if ((*this->m_Address.Zoom) <= this->m_Zoom.MaxLimit)
		{
			SetFloat2((DWORD)this->m_Address.Zoom, ((*this->m_Address.Zoom) + this->m_Zoom.Precision));
		}
	}

	this->SetCurrentValue();
}

void CCamera::Move(MOUSEHOOKSTRUCTEX* lpMouse)
{
	if (this->m_Enable == 0 || this->m_IsMove == 0 || *(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	if (this->m_CursorX < lpMouse->pt.x)
	{
		if ((*this->m_Address.RotX) > 309.0f)
		{
			SetFloat2((DWORD)this->m_Address.RotX, -45.0f);
		}
		else
		{
			SetFloat2((DWORD)this->m_Address.RotX, ((*this->m_Address.RotX) + 6.0f));
		}
	}

	if (this->m_CursorX > lpMouse->pt.x)
	{
		if ((*this->m_Address.RotX) < -417.0f)
		{
			SetFloat2((DWORD)this->m_Address.RotX, -45.0f);
		}
		else
		{
			SetFloat2((DWORD)this->m_Address.RotX, ((*this->m_Address.RotX) - 6.0f));
		}
	}

	if (this->m_CursorY < lpMouse->pt.y)
	{
		if ((*this->m_Address.RotY) < -22.5f)
		{
			SetFloat2((DWORD)this->m_Address.RotY, ((*this->m_Address.RotY) + 2.420f));
			SetFloat2((DWORD)this->m_Address.PosZ, ((*this->m_Address.PosZ) - 44.0f));
		}
	}

	if (this->m_CursorY > lpMouse->pt.y)
	{
		if ((*this->m_Address.RotY) > -90.0f)
		{
			SetFloat2((DWORD)this->m_Address.RotY, ((*this->m_Address.RotY) - 2.420f));
			SetFloat2((DWORD)this->m_Address.PosZ, ((*this->m_Address.PosZ) + 44.0f));
		}
	}

	this->m_CursorX = lpMouse->pt.x;

	this->m_CursorY = lpMouse->pt.y;

	this->SetCurrentValue();
}

void CCamera::SetCurrentValue()
{
	if (pMapNumber == 30)
	{
		SetFloat2((DWORD)this->m_Address.ClipXCS, (1190 + (abs(*this->m_Address.PosZ - 150) * 3) + 3000));

		SetFloat2((DWORD)this->m_Address.ClipYCS, (2400 + (abs(*this->m_Address.PosZ - 150) * 3) + 3000));

		SetFloat2((DWORD)this->m_Address.ClipZCS, (2400 + (abs(*this->m_Address.PosZ - 150) * 3) + 3000));
	}

	SetFloat2((DWORD)this->m_Address.ClipX, (1190 + (abs(*this->m_Address.PosZ - 150) * 3) + 3100));

	SetFloat2((DWORD)this->m_Address.ClipY, (2400 + (abs(*this->m_Address.PosZ - 150) * 3) + 3100));

	SetFloat2((DWORD)this->m_Address.ClipZ, (2000 + (abs(*this->m_Address.PosZ - 150) * 3) + 3100));
}

void CCamera::SetDefaultValue()
{
	if (this->m_Default.IsLoad != 0)
	{
		SetFloat2((DWORD)this->m_Address.Zoom, this->m_Default.Zoom);

		SetFloat2((DWORD)this->m_Address.RotX, this->m_Default.RotX);

		SetFloat2((DWORD)this->m_Address.RotY, this->m_Default.RotY);

		SetFloat2((DWORD)this->m_Address.PosZ, this->m_Default.PosZ);

		SetFloat2((DWORD)this->m_Address.ClipX, this->m_Default.ClipX);

		SetFloat2((DWORD)this->m_Address.ClipY, this->m_Default.ClipY);

		SetFloat2((DWORD)this->m_Address.ClipZ, this->m_Default.ClipZ);

		if (pMapNumber == 30)
		{
			SetFloat2((DWORD)this->m_Address.ClipXCS, this->m_Default.ClipXCS);

			SetFloat2((DWORD)this->m_Address.ClipYCS, this->m_Default.ClipYCS);

			SetFloat2((DWORD)this->m_Address.ClipZCS, this->m_Default.ClipZCS);
		}
	}
}

void CCamera::RotateDmg(float& X, float& Y, float D)
{
	const float Rad = 0.01745329f;
	float sinTh = sin(Rad * (*gCamera.m_Address.RotX));
	float cosTh = cos(Rad * (*gCamera.m_Address.RotX));

	X += D / 0.7071067f * cosTh / 2;
	Y -= D / 0.7071067f * sinTh / 2;
}

void __declspec(naked) CCamera::RotateFix()
{
	static DWORD jmpBack = 0x006434D1;

	_asm
	{
		Lea Eax, [Ebp - 0x8];
		Lea Ecx, [Ebp - 0xC];
		Push Dword Ptr[Ebp + 0x18];
		Push Eax;
		Push Ecx;
		Call RotateDmg;
		Add Esp, 0xC;
		jmp[jmpBack];
	}
}