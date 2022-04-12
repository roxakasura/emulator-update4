#include "stdafx.h"
#include "PlayerSystem.h"
#include "Protect.h"
#include "Util.h"

int valor = 0;

void PlayerLoad()
{
	if (gProtect.m_MainInfo.PlayerInfoGuildLogo == 1)
	{
		SetCompleteHook(0xE8, 0x0059F307, &PlayerGuildLogo); //Season 2.5 (jpn 1.02s - 0x006037C1)
	}
}

void PlayerGuildLogo(int a1, int a2, char* a3)
{
    int guild = 1;
    int result = *(DWORD*)(a3 + 628); //

    if (*(BYTE*)(result + 928) == 255)
    {
        guild = 0;
    }

    //-- Revisão se tem guild ou não
    if (guild == 0)
    {
        valor = 0;
    }
    else
    {
        CreateGuildMark(*(WORD*)(result + 554), 1);
        RenderBitmap(0x22, a1 - 18, a2 + 2, 16.0, 16.0, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
    }

    RenderBoolean(a1, a2, a3);
}