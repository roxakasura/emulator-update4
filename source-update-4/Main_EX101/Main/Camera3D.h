#pragma once

static float *Camera_Zoom    = (float*) 0x00626681;
static float *Camera_RotY    = (float*) 0x006A9798;
static float *Camera_RotZ    = (float*) 0x07D171A0;
static float *Camera_PosZ    = (float*) 0x006A7770;
static float *Camera_ClipX   = (float*) 0x006A967C;
static float *Camera_ClipY   = (float*) 0x005E9D4E;
static float *Camera_GlClip  = (float*) 0x004E8486;
static float *Camera_ClipAUX1 = (float*) 0x006A9684;
static float *Camera_ClipAUX2 = (float*) 0x006A9680;
static float *Camera_ClipAUX3 = (float*) 0x006A8FBC;

class CCamera
{
public:
	CCamera();
	virtual ~CCamera();
	// ---
	void ViewType(int Type);
	void Reset();
	void Run(MOUSEHOOKSTRUCTEX * Mouse, WPARAM wParam);
	// ---
	BOOL Enabled;
	BOOL bSelect;
	// ---
	bool InitCamera; 
	bool MoveCamera;
	// ---
	float Zoom;
	float RotY;
	float RotZ;
	float PosZ;
	float ClipX;
	float ClipY;
	float GlClip;
	// ---
	int MouseX,MouseY;
};
// ---
extern CCamera gCamera;