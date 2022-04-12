#pragma once

#define pPetItemConvert			((void(__cdecl*)(int a1))0x00420A60) //1.01t ok

void ItemConvert(int ObjectItem, BYTE Attribute1, BYTE Attribute2, BYTE Attribute3);

class cItem
{
public:
	void ItemLoad();
};
extern cItem gcItem;