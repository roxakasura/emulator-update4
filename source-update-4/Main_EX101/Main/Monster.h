#pragma once

void InitMonster();
DWORD MonsterRender(int index,int x,int y,int key);
DWORD MonsterSetup(DWORD ViewportAddress,int index);


#define	pLoadItemModel			((void(*)(int,char*,char*,int))0x005FACA0)	  // 1.1t
#define	pLoadItemTexture		((void(*)(int,char*,int,int,int))0x005FA860)  // 1.1t