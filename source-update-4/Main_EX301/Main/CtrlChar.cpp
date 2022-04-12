#include "stdafx.h"
#include "CtrlChar.h"
#include "Util.h"

void CtrlChar()
{
	SetCompleteHook(0xE9, 0x5423E0, &sub_5423E0);
}

bool sub_5423E0()
{
	int v0; // edi@3
	char v2; // al@7
	char v3; // al@12
	char v4; // cl@18
	char v5; // al@22
	int v6; // eax@28
	bool v7; // zf@32
	int v8; // eax@35
	char v9; // al@40
	__int16 v10; // ax@44
	bool v11; // zf@48
	int v12; // ST00_4@58

	if (*(DWORD*)0x764183F > 0 || *(DWORD*)0x76EFA4 == -1)
	{
		return 0;
	}
	v0 = *(DWORD*)0x74D2B28 + 1148 * *(DWORD*)0x76EFA4;

	if (*(DWORD*)0x77038C >= 18 && *(DWORD*)0x77038C <= 23 && v0 != *(DWORD*)0x74D2B2C)
	{
		return 1;
	}
	v2 = *(BYTE *)(v0 + 188);
	if (v2 == 2)
	{
		if (*(BYTE*)0x7B06C1C)
		{
			return *(BYTE*)0x7B06C1D != 0;
		}
		return 1;
	}
	if (v2 != 1)
	{
		return 0;
	}
	if (sub_4C8CB6())
	{
		v3 = *(BYTE *)(*(DWORD*)0x74D2B2C + 920);
		if (v3 == 9 || v3 == 6 || v3 == 10 || v3 == 11 || v3 == 7 || v3 == 8)
		{
			v4 = *(BYTE *)(v0 + 920);
			if (v4 == 13 || v4 == 12)
				return (*(DWORD *)(v0 + 168) & 0x4000) != 0x4000;
		}
		if (v3 == 13 || v3 == 12)
		{
			v5 = *(BYTE *)(v0 + 920);
			if (v5 == 9 || v5 == 6 || v5 == 10 || v5 == 11 || v5 == 7 || v5 == 8)
				return (*(DWORD *)(v0 + 168) & 0x4000) != 0x4000;
		}
		v6 = *(DWORD *)(*(DWORD*)0x74D2B2C + 168);
		if ((*(DWORD *)(*(DWORD*)0x74D2B2C + 168) & 0x80000) == 0x80000
			|| (v6 & 0x400000) == 0x400000
			|| ((unsigned int)0x800000 & v6) == 0x800000)
		{
			v8 = *(DWORD *)(v0 + 168);
			if ((*(DWORD *)(v0 + 168) & 0x80000) == 0x80000 || (v8 & 0x400000) == 0x400000)
				goto LABEL_40;
			v7 = ((unsigned int)0x800000 & v8) == 0x800000;
		}
		else
		{
			if ((v6 & 0x40000) != 0x40000)
				goto LABEL_40;
			v7 = (*(DWORD *)(v0 + 168) & 0x40000) == 0x40000;
		}
		if (!v7)
			return (*(DWORD *)(v0 + 168) & 0x4000) != 0x4000;
	}
LABEL_40:
	v9 = *(BYTE *)(v0 + 936);
	if (v9 == 2 || v9 == 8)
		return 1;
	if (*(BYTE*)0x7B06C1C)
	{
		if (*(BYTE *)(v0 + 941) >= 6u)
		{
			v10 = *(WORD *)(v0 + 554);
			if (v10 != -1
				&& !strcmp(
				(const char *)(88 * *(WORD *)(*(DWORD*)0x74D2B2C + 554) + 124003013),
					(const char *)(88 * v10 + 124003013)))
			{
				return 0;
			}
		}
	}
	if (*(BYTE*)0x7672EE0)
	{
		if (*(WORD *)(v0 + 556) != *(DWORD*)0x7672EE4)
			return 0;
		v11 = strcmp((const char *)(v0 + 529), (const char *)&*(DWORD*)0x7672EE8) == 0;
		goto LABEL_59;
	}
	if (*(BYTE*)0x7B06C1C)
	{
		if (*(BYTE *)(v0 + 940) == 2 && v0 != *(DWORD*)0x74D2B2C)
			return 1;
		return 0;
	}
		return 1;
	sub_66BFEC();
	if (*(DWORD*)0x77038C >= 45 && *(DWORD*)0x77038C <= 50)
	{
		v12 = *(DWORD*)0x76EFA4;
		sub_66BFEC();
		v11 = sub_66C27F(v12) == 0;
	LABEL_59:
		if (v11)
			return 1;
	}
	return 0;
}