#include "stdafx.h"

CCamera gCamera;

CCamera::CCamera()
{
	this->Enabled = FALSE;
}

CCamera::~CCamera(){}

void CCamera::ViewType(int Type)
{
	switch(Type)
	{
	case 1:
		{
			this->bSelect = !this->bSelect;
			// ---
			this->Enabled = true;
			// ---
			//gToolKit.SendMsg(0, "* Camera Ligada *");
		}
		break;
	case 2:
		{
			this->bSelect = !this->bSelect;
			// ---
			this->Enabled = false;
			// ---
			//gToolKit.SendMsg(0, "* Camera Desligada *");
		}
		break;
	};
}

void CCamera::Reset()
{
	*Camera_RotY		= 48.5;
	*Camera_RotZ		= -45;
	*Camera_PosZ		= 150;
	*Camera_ClipX		= 1190;
	*Camera_ClipY		= 2400;
	*Camera_GlClip		= 2000;
	*Camera_Zoom		= 35;
	*Camera_ClipAUX1	= 456;
	*Camera_ClipAUX2	= 1128;
	*Camera_ClipAUX3	= 540;
	// ---
	//gToolKit.SendMsg(0, "* Camera Resetada *");
}

void CCamera::Run(MOUSEHOOKSTRUCTEX * Mouse, WPARAM wParam)
{
	switch(wParam)
	{
		case WM_MBUTTONDOWN:
		{
			if(!gCamera.Enabled) break;

			gCamera.MoveCamera = true;

			break;
		}
		case WM_MBUTTONUP:
		{
			if(!gCamera.Enabled) break;

			gCamera.MoveCamera = false;

			break;
		}
		case WM_MOUSEWHEEL:
		{
			if(!gCamera.Enabled) break;
			// ---
			int direction = Mouse->mouseData;
			// ---
			if(direction < 0)
			{
				if(*Camera_Zoom > 12)
				{
					*Camera_Zoom -= 1;
				}
				// ---
				if(*Camera_Zoom < 12)
				{
					*Camera_Zoom = 12;
				}

			}
			else if(direction > 0)
			{
				if(*Camera_Zoom < 60)
				{
					*Camera_Zoom += 1;
				}
				// ---
				if(*Camera_Zoom > 60)
				{
					*Camera_Zoom = 60;
				}
			}
			// ---
			*Camera_ClipX		= 6144 + (abs(*Camera_PosZ - 150) * 3) + 6000;
            *Camera_ClipY		= 6144 + (abs(*Camera_PosZ - 150) * 3) + 4000;
            *Camera_GlClip		= 3600 + (abs(*Camera_PosZ - 150) * 3) + 3000;
			*Camera_ClipAUX1	= -2000 + (abs(*Camera_PosZ - 150) * 3) - 3000;
			*Camera_ClipAUX2	= 2000 + (abs(*Camera_PosZ - 150) * 3) + 3000;
			*Camera_ClipAUX3	= 2000 + (abs(*Camera_PosZ - 150) * 3) + 3000;
			// ---
			break;
		}
		case WM_MOUSEMOVE:
		{
			if(!gCamera.Enabled) break;
			// ---
			if(gCamera.MoveCamera)
			{
				if(gCamera.MouseX < Mouse->pt.x)
				{
					*Camera_RotZ += 8;
					// ---
					if(*Camera_RotZ > 315)
					{
						*Camera_RotZ = -45;
					}
				}
				else if(gCamera.MouseX > Mouse->pt.x)
				{
					*Camera_RotZ -= 8;
					// ---
					if(*Camera_RotZ < -405)
					{
						*Camera_RotZ = -45;
					}
				}
				if(gCamera.MouseY < Mouse->pt.y)
				{
					if (*Camera_RotY > -90)
					{
						*Camera_PosZ += 20;
						*Camera_RotY += abs((*Camera_PosZ + 330) / 640);	
					}	
				}
				else if(gCamera.MouseY > Mouse->pt.y)
				{
					if (*Camera_RotY > 25)
					{
						*Camera_PosZ -= 20;
						*Camera_RotY -= abs((*Camera_PosZ + 330) / 600);
					}
				}
				// ---
				gCamera.MouseX = Mouse->pt.x;
				gCamera.MouseY = Mouse->pt.y;
				// ---
				*Camera_ClipX		= 6144 + (abs(*Camera_PosZ - 150) * 3) + 6000;
				*Camera_ClipY		= 6144 + (abs(*Camera_PosZ - 150) * 3) + 4000;
				*Camera_GlClip		= 3600 + (abs(*Camera_PosZ - 150) * 3) + 3000;
				*Camera_ClipAUX1	= -2000 + (abs(*Camera_PosZ - 150) * 3) - 3000;
				*Camera_ClipAUX2	= 2000 + (abs(*Camera_PosZ - 150) * 3) + 3000;
				*Camera_ClipAUX3	= 2000 + (abs(*Camera_PosZ - 150) * 3) + 3000;
			}
			// ---
			break;
		}
	}
}