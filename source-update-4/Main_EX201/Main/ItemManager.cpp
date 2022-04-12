#include "stdafx.h"
#include "Util.h"
#include "CustomItem.h"
#include "CustomWing.h"
#include "ItemManager.h"

void InitItem() // OK
{
	SetCompleteHook(0xFF,0x0065544E,&ItemModelLoad);	// 1.02r

	SetCompleteHook(0xFF,0x0065545F,&ItemTextureLoad);	// 1.02r

	SetCompleteHook(0xFF,0x0052F199,&GetItemColor);		//s1

	SetCompleteHook(0xFF,0x0063EE31,&GetItemColor);		//s1
}

void ItemModelLoad() // OK
{
	((void(*)())0x00645320)();

	for(int n=0;n < MAX_CUSTOM_WING;n++)
	{
		if(gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemModel((gCustomWing.m_CustomWingInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomWing.m_CustomWingInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		if(gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemModel((gCustomItem.m_CustomItemInfo[n].ItemIndex+ITEM_BASE_MODEL),((gCustomItem.m_CustomItemInfo[n].ItemIndex>=GET_ITEM(7,0)&&gCustomItem.m_CustomItemInfo[n].ItemIndex<GET_ITEM(12,0))?"Player\\":"Item\\"),gCustomItem.m_CustomItemInfo[n].ModelName,-1);
		}
	}
}

void ItemTextureLoad() // OK
{
	for(int n=0;n < MAX_CUSTOM_WING;n++)
	{
		if(gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomWing.m_CustomWingInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomWing.m_CustomWingInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		if(gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomItem.m_CustomItemInfo[n].ItemIndex+ITEM_BASE_MODEL),((gCustomItem.m_CustomItemInfo[n].ItemIndex>=GET_ITEM(7,0)&&gCustomItem.m_CustomItemInfo[n].ItemIndex<GET_ITEM(12,0))?"Player\\":"Item\\"),gCustomItem.m_CustomItemInfo[n].ModelName,-1);
		}
	}

	((void(*)())0x00646DC0)();
}

void LoadItemModel(int index,char* folder,char* name,int value)
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,char*,int))0x00642C00)(index,path,name,value);
}

void LoadItemTexture(int index,char* folder,char* name,int value)
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,int,int,int))0x006427C0)(index,folder,0x2901,0x2600,0x01);
}

void GetItemColor(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e)
{
	if (gCustomItem.GetCustomItemColor((a - ITEM_BASE_MODEL), (float*)d) == 0)
	{
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD))0x0063C030)(a, b, c, d, e);
	}
}