#include "stdafx.h"

void InitMap()  // OK
{
	//Bypass in terrains files
	SetByte(0x00607090,0xEB); //00607090 
	SetByte(0x00607095,0xEB); //00607095
	SetByte(0x00607141,0xEB); //00607141
	SetByte(0x00607146,0xEB); //00607146
	SetByte(0x006071B3,0xEB); //006071B3
	SetByte(0x006071B8,0xEB); //006071B8

	SetCompleteHook(0xE8,0x004BEB03,&LoadMapName); //004BEB03

	SetCompleteHook(0xE8,0x004C1900,&LoadMapName); //004C1900

	SetCompleteHook(0xE8,0x005DF615,&LoadMapName); //005DF615

	SetCompleteHook(0xE8,0x0064D303,&LoadMapTitle); //0064D303
}

char* LoadMapName(int index) //OK
{
	CUSTOM_MAP_INFO* lpInfo = gCustomMap.GetInfoByNumber(index);

	if(lpInfo != 0)
	{
		return lpInfo->MapName;
	}
	
	return ((char*(*)(int))0x005DF2A0)(index);
}

int LoadMapTitle(char* path,int index,int c,int d,int e,int f) // OK
{
	CUSTOM_MAP_INFO* lpInfo = gCustomMap.GetInfoByNumber(*(DWORD*)MAIN_CURRENT_MAP);

	if(lpInfo != 0)
	{
		path = lpInfo->TitlePath;
	}
	
	return ((int(__cdecl*)(char*,int,int,int,int,int))0x0062C670)(path,index,c,d,e,f);
}