#ifndef _EFFECT_MANAGER_H
#define _EFFECT_MANAGER_H

#include "MathLib.h"

typedef struct
{
	BYTE Shift00[16];
	/*+16*/	vec3_t Position;
	/*+28*/	vec3_t Angle;
}OBJECT,*LPOBJECT;

#define CONFIG_EFFECT_FILE	"Data\\Custom\\ItemEffect.txt"

#define pAllowStaticEffect		((int(__thiscall*)(float *This, int a2, int a3, int a4, char a5)) 0x005020D9) // 1.04j ok
#define pPlayDynamicEffect		((int(__cdecl*)(DWORD ModelID, DWORD * Arg1, int Arg2, float * Color, int Arg4, float Arg5, int Arg6)) 0x006DA9C1) //1.04j ok
#define pPlayStaticEffect		((int(__cdecl*)(DWORD ModelID, __int16 a2, int a3, int a4, float *a5, int a6)) 0x0051CB66) //1.04j ok


#define pDrawItemEffect			((void(__cdecl*)(LPOBJECT o,int Type,vec3_t Light,float Alpha,int ItemLevel,int NewOption,int SetOption,int Select,int RenderType))0x0062392F) //1.04j ok
#define pCreateSprite			((int(__cdecl*)(int Type,vec3_t Position,float Scale,vec3_t Light,LPOBJECT Owner,float Rotation,int SubType))0x006EE878)
#define pTransformPosition		((int(__thiscall*)(LPVOID This,int Matrix,vec3_t Position,vec3_t WorldPosition,bool Translate))0x005020D9)
#define pTransformPosition2		((int(__thiscall*)(void *This,vec34_t Matrix,vec3_t Position,vec3_t WorldPosition,bool Translate))0x005020D9)

#define pCreateParticle					((int(__cdecl*)(int Type,vec3_t Position,vec3_t Angle,vec3_t Light,int SubType,float Scale,LPOBJECT Owner))0x006DA9C1)

#define oBoneTransformPointer						0x0694982C
#define JointId(x)									((0x30*x)+oBoneTransformPointer)

#define MAX_CUSTOM_EFFECT 3000

struct EFFECT_INFO	
{
	int ItemIndex;
	int EffectStaticIndex;
	int EffectDynamicIndex;
	int EffectBone;

	float Color[3];

	float EffectStaticSize;
	float EffectDynamicSize;
};

class CEffectManager
{
public:
	void Load();
	// ---
	static void EffectItem();
	// ---
	static void DrawItemEffect(LPOBJECT o,int Type,vec3_t Light,float Alpha,int ItemLevel,int NewOption,int SetOption,int Select,int RenderType);
	static int CreateSpriteEx(int Type,vec3_t Position,float Scale,vec3_t Light,LPOBJECT Owner,float Rotation,int SubType);
	static int CreateParticleEx(int Type,vec3_t Position,vec3_t Angle,vec3_t Light,int SubType,float Scale,LPOBJECT Owner);
	static int AllowStaticEffect(float *This, int a2, int a3, int a4, char a5);
private:
	int Count;
	// ---
	EFFECT_INFO m_EffectInfo[MAX_CUSTOM_EFFECT];
};

extern CEffectManager gEffectManager;

void ReadyEfect();

#endif