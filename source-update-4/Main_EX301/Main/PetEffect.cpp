#include "main.h"
//#include "utils.h"
#include "stdafx.h"

char CreatePetEffect(int Arg1, char Arg2)
{
	float v2; // ST14_4@3
	float v3; // ST10_4@3
	char v5; // [sp+17h] [bp-15h]@3
	int v6; // [sp+18h] [bp-14h]@18
	float v7; // [sp+1Ch] [bp-10h]@21
	float v8; // [sp+20h] [bp-Ch]@21
	float v9; // [sp+24h] [bp-8h]@21
	float v10; // [sp+28h] [bp-4h]@20

	vec3_t Color;
	Vector(0.f, 0.f, 0.f, Color);

	vec3_t Color2;
	Vector(0.f, 0.f, 0.f, Color2);

	vec3_t Color3;
	Vector(0.f, 0.f, 0.f, Color3);

	vec3_t Color4;
	Vector(0.f, 0.f, 0.f, Color4);

	vec3_t Color5;
	Vector(0.f, 0.f, 0.f, Color5);

	if (*(BYTE*)(Arg1)) //ok
	{
		if (Arg2)//ok
		{
			v5 = 1;//ok
		}
		else
		{
			v2 = *(float *)(Arg1 + 20) * 0.0099999998;//ok
			v3 = *(float *)(Arg1 + 16) * 0.0099999998;//ok
			v5 = pObjectGetAngle(v3, v2, -20);
		}
		*(BYTE*)(Arg1 + 416) = v5;
		if (*(BYTE*)(Arg1 + 416)) //ok
		{
			if (*(WORD *)(*(DWORD*)(Arg1 + 316) + 2) != 641 && *(WORD *)(Arg1 + 2) != 7305)
				return 1;
			if (Arg2)
			{
				*(DWORD*)(Arg1 + 12) = *(DWORD*)(Arg1 + 12);
			}
		
			else if (pMainState == 2)
			{
				*(DWORD*)(Arg1 + 12) = 1065353216;
			}
			else if (pMainState == 4)
			{
				*(DWORD*)(Arg1 + 12) = 1065353216;
			}
			else if (*(WORD *)(Arg1 + 2) != 364
				&& *(WORD *)(Arg1 + 2) != 366
				&& *(WORD *)(Arg1 + 2) != 365
				&& *(WORD *)(Arg1 + 2) != 367)
			{
				*(DWORD *)(Arg1 + 12) = 1065353216;
			}

			v6 = 0;
			if ((*(DWORD *)(*(DWORD *)(Arg1 + 316) + 168) & 0x4000) == 0x4000)
			v6 = 10;
			pObjectMaxBug(Arg1, 0, 0, v6);
			v10 = (double)(sub_007396FD() % 30 + 70) * 0.0099999998;
			// ----
			/*if (*(DWORD*)(Arg1 + 2) == ObjectId(13, 0))
			{
				v7 = v10 * 0.5;
				v8 = v10 * 0.80000001;
				v9 = v10 * 0.60000002;
				Vector(0.94, 0.812f, 0.5358f, Color);
				pCreateSpriteEx(1707, Arg1 + 16, 1065353216, (int)&Color, Arg1, 0, 0);
			}*/
			if (*(DWORD*)(Arg1 + 2) == ObjectId(13, 0))
			{
				Vector(0.5358f, 0.812f, 0.94f, Color);
				//Vector(0.94f, 0.834f, 0.553f, Color);
				pCreateParticleEx(1733, Arg1 + 16, Arg1 + 24, (int)Color, 11, 0.5f, Arg1);
				Vector(0.94f, 0.834f, 0.553f, Color2);
				pCreateParticleEx(1733, Arg1 + 16, Arg1 + 24, (int)Color2, 11, 0.4f, Arg1);
				Vector(0.553f, 0.94f, 0.84f, Color3);
				pCreateParticleEx(1733, Arg1 + 16, Arg1 + 24, (int)Color3, 11, 0.3f, Arg1);
				Vector(0.235f, 0.125f, 0.85f, Color4);
				pCreateParticleEx(1733, Arg1 + 16, Arg1 + 24, (int)Color4, 11, 0.2f, Arg1);
				Vector(0.85689f, 0.23541f, 0.9635f, Color5);
				pCreateParticleEx(1733, Arg1 + 16, Arg1 + 24, (int)Color5, 11, 0.1f, Arg1);
			}
			// -----------
		}
	}
	return 1;
}

//SetHook((LPVOID)CreatePetEffect, (LPVOID)0x004714C2, ASM::CALL); //ok
//SetHook((LPVOID)CreatePetEffect, (LPVOID)0x004E7786, ASM::CALL); //ok