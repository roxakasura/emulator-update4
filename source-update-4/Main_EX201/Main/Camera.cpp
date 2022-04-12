#include "stdafx.h"
#include "Camera.h"
#include "Offset.h"
#include "Util.h"

CCamera gCamera;

CCamera::CCamera()
{
	this->m_Enable = 0;

	this->m_IsMove = 0;

	this->m_CursorX = 0;

	this->m_CursorY = 0;

	this->m_Zoom.MinPercent = 50.0f;

	this->m_Zoom.MaxPercent = 300.0f;

	this->m_Zoom.Precision = 2.0f;

	this->m_Address.Zoom = (float*)0x0066D8C1;

	this->m_Address.RotX = (float*)0x07DCB0B8;

	this->m_Address.RotY = (float*)0x006EA878;

	this->m_Address.PosZ = (float*)0x006E86E4;

	this->m_Address.ClipX[0] = (float*)0x006EA788;

	this->m_Address.ClipX[1] = (float*)0x006EA7AC;

	this->m_Address.ClipY[0] = (float*)0x006EA790;

	this->m_Address.ClipY[1] = (float*)0x006EA7B4;

	this->m_Address.ClipGL = (float*)0x0066DBDC;

	this->m_Default.IsLoad = 0;

	MemorySet(0x0065853E, 0x90, 6);

	SetCompleteHook(0xE9, 0x006585AA, &this->RotateFix);
}

CCamera::~CCamera()
{

}

void CCamera::Toggle()
{
	if (SceneFlag == 5)
	{
		this->m_Enable ^= 1;

		if (((this->m_Default.IsLoad == 0) ? (this->m_Default.IsLoad++) : this->m_Default.IsLoad) == 0)
		{
			this->m_Default.Zoom = (*this->m_Address.Zoom);

			this->m_Default.RotX = (*this->m_Address.RotX);

			this->m_Default.RotY = (*this->m_Address.RotY);

			this->m_Default.PosZ = (*this->m_Address.PosZ);

			this->m_Default.ClipX[0] = (*this->m_Address.ClipX[0]);

			this->m_Default.ClipX[1] = (*this->m_Address.ClipX[1]);

			this->m_Default.ClipY[0] = (*this->m_Address.ClipY[0]);

			this->m_Default.ClipY[1] = (*this->m_Address.ClipY[1]);

			this->m_Default.ClipGL = (*this->m_Address.ClipGL);
		}

		pDrawMessage(((this->m_Enable) ? "Camera 3D Enabled" : "Camera 3D Disabled"), 1);
	}
}

void CCamera::Restore()
{
	if (this->m_Enable != 0 && SceneFlag == 5)
	{
		this->SetDefaultValue();

		pDrawMessage("Camera 3D Restored", 1);
	}
}

void CCamera::SetIsMove(BOOL IsMove)
{
	if (this->m_Enable != 0 && SceneFlag == 5)
	{
		this->m_IsMove = IsMove;
	}
}

void CCamera::SetCursorX(LONG CursorX)
{
	if (this->m_Enable != 0 && SceneFlag == 5)
	{
		this->m_CursorX = CursorX;
	}
}

void CCamera::SetCursorY(LONG CursorY)
{
	if (this->m_Enable != 0 && SceneFlag == 5)
	{
		this->m_CursorY = CursorY;
	}
}

void CCamera::Zoom(MOUSEHOOKSTRUCTEX* lpMouse)
{
	if (this->m_Enable == 0 || this->m_IsMove != 0 || SceneFlag != 5)
	{
		return;
	}

	this->m_Zoom.MinLimit = (this->m_Default.Zoom / 100) * this->m_Zoom.MinPercent;

	this->m_Zoom.MaxLimit = (this->m_Default.Zoom / 100) * this->m_Zoom.MaxPercent;

	if (((int)lpMouse->mouseData) > 0)
	{
		if ((*this->m_Address.Zoom) >= this->m_Zoom.MinLimit)
		{
			SetFloat((DWORD)this->m_Address.Zoom, ((*this->m_Address.Zoom) - this->m_Zoom.Precision));
		}
	}

	if (((int)lpMouse->mouseData) < 0)
	{
		if ((*this->m_Address.Zoom) <= this->m_Zoom.MaxLimit)
		{
			SetFloat((DWORD)this->m_Address.Zoom, ((*this->m_Address.Zoom) + this->m_Zoom.Precision));
		}
	}

	this->SetCurrentValue();
}

void CCamera::Move(MOUSEHOOKSTRUCTEX* lpMouse)
{
	if (this->m_Enable == 0 || this->m_IsMove == 0 || SceneFlag != 5)
	{
		return;
	}

	if (this->m_CursorX < lpMouse->pt.x)
	{
		if ((*this->m_Address.RotX) > 309.0f)
		{
			SetFloat((DWORD)this->m_Address.RotX, -45.0f);
		}
		else
		{
			SetFloat((DWORD)this->m_Address.RotX, ((*this->m_Address.RotX) + 6.0f));
		}
	}

	if (this->m_CursorX > lpMouse->pt.x)
	{
		if ((*this->m_Address.RotX) < -417.0f)
		{
			SetFloat((DWORD)this->m_Address.RotX, -45.0f);
		}
		else
		{
			SetFloat((DWORD)this->m_Address.RotX, ((*this->m_Address.RotX) - 6.0f));
		}
	}

	if (this->m_CursorY < lpMouse->pt.y)
	{
		if ((*this->m_Address.RotY) > -22.5f)
		{
			SetFloat((DWORD)this->m_Address.RotY, ((*this->m_Address.RotY) + 2.420f));

			SetFloat((DWORD)this->m_Address.PosZ, ((*this->m_Address.PosZ) - 44.0f));
		}
	}

	if (this->m_CursorY > lpMouse->pt.y)
	{
		if ((*this->m_Address.RotY) < -90.0f)
		{
			SetFloat((DWORD)this->m_Address.RotY, ((*this->m_Address.RotY) - 2.420f));

			SetFloat((DWORD)this->m_Address.PosZ, ((*this->m_Address.PosZ) + 44.0f));
		}
	}

	this->m_CursorX = lpMouse->pt.x;

	this->m_CursorY = lpMouse->pt.y;

	this->SetCurrentValue();
}

void CCamera::SetCurrentValue()
{
	SetFloat((DWORD)this->m_Address.ClipX[0], (4290.0f + (abs(((*this->m_Address.PosZ) - 150.0f)) * 3.0f)));

	SetFloat((DWORD)this->m_Address.ClipX[1], (4190.0f + (abs(((*this->m_Address.PosZ) - 150.0f)) * 3.0f)));

	SetFloat((DWORD)this->m_Address.ClipY[0], (5500.0f + (((float)abs(((*this->m_Address.PosZ) - 150.0f))) * 3.0f)));

	SetFloat((DWORD)this->m_Address.ClipY[1], (5500.0f + (((float)abs(((*this->m_Address.PosZ) - 150.0f))) * 3.0f)));

	SetFloat((DWORD)this->m_Address.ClipGL, (5100.0f + (((float)abs(((*this->m_Address.PosZ) - 150.0f))) * 3.0f)));
}

void CCamera::SetDefaultValue()
{
	if (this->m_Default.IsLoad != 0)
	{
		SetFloat((DWORD)this->m_Address.Zoom, this->m_Default.Zoom);

		SetFloat((DWORD)this->m_Address.RotX, this->m_Default.RotX);

		SetFloat((DWORD)this->m_Address.RotY, this->m_Default.RotY);

		SetFloat((DWORD)this->m_Address.PosZ, this->m_Default.PosZ);

		SetFloat((DWORD)this->m_Address.ClipX[0], this->m_Default.ClipX[0]);

		SetFloat((DWORD)this->m_Address.ClipX[1], this->m_Default.ClipX[1]);

		SetFloat((DWORD)this->m_Address.ClipY[0], this->m_Default.ClipY[0]);

		SetFloat((DWORD)this->m_Address.ClipY[1], this->m_Default.ClipY[1]);

		SetFloat((DWORD)this->m_Address.ClipGL, this->m_Default.ClipGL);
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
	static DWORD jmpBack = 0x006585C2;

	_asm
	{
		Add Esp, 0x1C
		Lea Eax, [Ebp - 0x8]
		Lea Ecx, [Ebp - 0xC]
		Push Dword Ptr[Ebp + 0x8]
		Push Eax
		Push Ecx
		Call RotateDmg
		Add Esp, 0x0C
		Inc Esi
		Cmp Esi, Ebx
		Jmp[jmpBack]
	}
}