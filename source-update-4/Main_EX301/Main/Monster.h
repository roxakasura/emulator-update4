#pragma once

void InitMonster();
DWORD MonsterRender(int index,int x,int y,int key);
DWORD MonsterSetup(DWORD ViewportAddress,int index);


#define	pLoadItemModel			((void(*)(int,char*,char*,int))0x0062B803)
#define	pLoadItemTexture		((void(*)(int,char*,int,int,int))0x0062B387)