#include "stdafx.h"
#include "PcPoint.h"
#include "ItemManager.h"
#include "MemScript.h"
#include "Util.h"

CPcPoint gPcPoint;


void CPcPoint::InitPcPoint() // OK
{
	SetCompleteHook(0xE8,0x005B237F,&PricePcPoint); //1.05d 0x05863DA
}


void CPcPoint::Load(PCPOINT_ITEM_INFO* info) // OK
{
	for(int n=0;n < MAX_ITEM_PCPOINT;n++)
	{
		if(info[n].Index < 0 || info[n].Index >= MAX_ITEM_PCPOINT)
		{
			return;
		}
		this->m_ItemInfo.insert(std::pair<int,PCPOINT_ITEM_INFO>(info[n].Index,info[n]));
	}		
}


int CPcPoint::GetInfo(int item, int level) // OK
{
	for(std::map<int,PCPOINT_ITEM_INFO>::iterator it=this->m_ItemInfo.begin();it != this->m_ItemInfo.end();it++)
	{
		if(it->second.ItemIndex == item && (level >= (it->second.Level*8) && level <=(it->second.Level*8)+7 ))
		{
			return it->second.Value;
		}
	}
	return 100;
}

int PricePcPoint(int a1,int a2)
{
    int ItemId  = *(WORD*)a1;
    int ItemLvl = *(WORD*)(a1+2);

    return gPcPoint.GetInfo(ItemId,ItemLvl);
}


