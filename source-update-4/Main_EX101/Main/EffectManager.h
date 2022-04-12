#pragma once

#include "MathLib.h"
#include "BMD.h"


// -> 1.01.46
typedef struct
{
	BYTE		gap00[2];
	/*+2*/		WORD		ObjModelID;
	BYTE		gap01[1];
	/*+4*/		BYTE		IsRender;
	BYTE		gap02[4];
	/*+8*/		BYTE		AnimationID;
	BYTE		gap03[4];
	/*+16*/		vec3_t		Position;		// -> +16 | +20 | +24
	/*+28*/		vec3_t		Angle;			// -> +28 | +32 | +36
}OBJMODEL,*LPOBJMODEL;

/*
MODEL INFORMATION:
char	= 1;
BYTE	= -1~1;
short	= 2
WORD	= -2~2
long	= 4;
DWORD	= -4~4;
float	= 4;
double	= 8;
vec3_t	= 4+4+4; 4*3; 12;
*/

// -> 1.01.46
typedef struct
{
	BYTE		gap01[2];
	/*+2*/		WORD		ObjectID;
	/*+4*/		BYTE		IsRender;
	BYTE		gap02[3];
	/*+8*/		BYTE		AnimationID;
	BYTE		gap03[4];
	/*+16*/		vec3_t		Position;
	/*+28*/		vec3_t		Angle;
	BYTE		gap04[220];
	/*+260*/	LPOBJMODEL	ObjModelLink;
	BYTE		gap05[718];
	/*+978*/	BYTE		IsSafeZone;
}OBJPREVIEW,*LPOBJPREVIEW;

#define pDrawItemEffect			((void(__cdecl*)(LPOBJECT o,int Type,vec3_t Light,float Alpha,int ItemLevel,int NewOption,int SetOption,int Select,int RenderType))0x005F8640) //1.01t ok
#define pCreateSprite			((int(__cdecl*)(int Type,vec3_t Position,float Scale,vec3_t Light,LPOBJPREVIEW Owner,float Rotation,int SubType))0x0053DE20)

#define pTransformPosition		((int(__thiscall*)(LPVOID This,int Matrix,vec3_t Position,vec3_t WorldPosition,bool Translate))0x004E4610) //1.01t ok
#define pTransformPosition2		((int(__thiscall*)(void *This,vec34_t Matrix,vec3_t Position,vec3_t WorldPosition,bool Translate))0x004E4610) //1.01t ok

#define pCreateParticle			((int(__cdecl*)(int Type,vec3_t Position,vec3_t Angle,vec3_t Light,int SubType,float Scale,LPOBJPREVIEW Owner))0x005353B0)
#define pRenderPartObjectEffect	((void(__cdecl*)(LPOBJPREVIEW Owner,int ObjectId,vec3_t Light,float Alpha,int ItemLevel,int NewOption,int SetOption,int Select,int RenderType))0x005F8640)

#define oBoneTransformPointer						0x0689E7FC //1.1t
#define JointId(x)									((0x30*x)+oBoneTransformPointer)

class CEffectManager
{
public:
	CEffectManager();
	virtual ~CEffectManager();
	// ----
	void Load();
	void Init();
	// ---
	static void DrawItemEffect(LPOBJPREVIEW Owner,int ObjectId,vec3_t Light,float Alpha,int ItemLevel,int NewOption,int SetOption,int Select,int RenderType);
};

extern CEffectManager gEffectManager;
