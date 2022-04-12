#include "stdafx.h"
#include "Monster.h"
#include "CustomMonster.h"
#include "Util.h"

void InitMonster() // OK
{
	SetByte(0x00513A8B,0xFF); // Monster Kill 004F3EC7+2 1.1t
	
	SetByte(0x00513A8C,0xFF); // Monster Kill 004F3EC7+3 1.1t

	SetCompleteHook(0xE8,0x0052D9A2,&MonsterRender); //0050AD14 - hook 0042B2C0 1.1t
	
	SetCompleteHook(0xE8,0x0052D9C3,&MonsterSetup); //0050AD2D - hook 0050ABB0 1.1t
}

DWORD MonsterRender(int index,int x,int y,int key) // OK
{
	CUSTOM_MONSTER_INFO* lpInfo = gCustomMonster.GetInfoByIndex(index);

	if(lpInfo != 0)
	{
		if(lpInfo->Type != 0)
		{
			index += 408;
		}
		
		DWORD ViewportAddress = 240 * index + *(DWORD*)0x05801AE8;
		//DWORD ViewportAddress = 224 * index + *(DWORD*)0x05756AB8; //1.1t

		if(*(WORD*)(ViewportAddress + 38) <= 0)
		{
			char path[MAX_PATH] = {0};

			wsprintf(path,"Data\\%s",lpInfo->FolderPath);

			pLoadItemModel(index,path,lpInfo->ModelPath,-1);

			if(lpInfo->Type == 0)
			{
				for(int i=0;i < *(WORD*)(ViewportAddress + 38);++i)
				{
					*(float*)(*(DWORD*)(ViewportAddress + 48) + 16 * i + 4) = 0.25f;
				}
			}
			else
			{
				*(float*)(*(DWORD*)(ViewportAddress + 48) + 4) = 0.25f;
				*(float*)(*(DWORD*)(ViewportAddress + 48) + 20) = 0.2f;
				*(float*)(*(DWORD*)(ViewportAddress + 48) + 36) = 0.34f;
				*(float*)(*(DWORD*)(ViewportAddress + 48) + 52) = 0.33000001f;
				*(float*)(*(DWORD*)(ViewportAddress + 48) + 68) = 0.33000001f;
				*(float*)(*(DWORD*)(ViewportAddress + 48) + 84) = 0.5f;
				*(float*)(*(DWORD*)(ViewportAddress + 48) + 100) = 0.55000001f;
				*(BYTE*)(*(DWORD*)(ViewportAddress + 48) + 96) = 1;
			}
		}

		pLoadItemTexture(index,lpInfo->FolderPath,GL_REPEAT,GL_NEAREST,GL_TRUE);
		
		return ((DWORD(__cdecl*)(int,int,int,int,float))0x0052B5BE)(key,index,x,y,0);
		//return ((DWORD(__cdecl*)(int,int,int,int,float))0x00509410)(key,index,x,y,0); 1.1t
	}
	
	return ((DWORD(__cdecl*)(int,int,int,int))0x004DB1D6)(index,x,y,key);
	//return ((DWORD(__cdecl*)(int,int,int,int))0x0042B2C0)(index,x,y,key); //1.1t
}

DWORD MonsterSetup(DWORD address,int index) // OK
{
	CUSTOM_MONSTER_INFO* lpInfo = gCustomMonster.GetInfoByIndex(index);

	if(lpInfo != 0)
	{
		*(float*)(address + 12) = lpInfo->Size;

		*(BYTE*)(address + 188) = (lpInfo->Type == 0) ? 4 : 2;

		memcpy((DWORD*)(address + 529),lpInfo->Name,sizeof(lpInfo->Name));

		*(DWORD*)(address + 942) = (lpInfo->Type == 2) ? 43 : index;

		return address;
	}
	
	return ((DWORD(__cdecl*)(DWORD,int))0x0052D70D)(address,index);
	//return ((DWORD(__cdecl*)(DWORD,int))0x0050ABB0)(address,index); 1.1t
}