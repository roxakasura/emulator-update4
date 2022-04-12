// GoldenArcher.cpp: implementation of the CGoldenArcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GoldenArcher.h"
#include "DSProtocol.h"
#include "JSProtocol.h"
#include "GameMain.h"
#include "ItemManager.h"
#include "MemScript.h"
#include "Notice.h"
#include "Util.h"
#include "ItemBagManager.h"

CGoldenArcher gGoldenArcher;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void CGoldenArcher::Load(char* path)
{

	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if (lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while (true)
			{
				if (section == 0)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->m_active = lpMemScript->GetNumber();

					this->m_type = lpMemScript->GetAsNumber();

					this->m_quantity = lpMemScript->GetAsNumber();
				}
				else if (section == 1)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->m_resets = lpMemScript->GetNumber();

					this->m_leveluppoint = lpMemScript->GetAsNumber();

					this->m_money = lpMemScript->GetAsNumber();
				}
				else if (section == 2)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->m_coin1 = lpMemScript->GetNumber();

					this->m_coin2 = lpMemScript->GetAsNumber();

					this->m_coin3 = lpMemScript->GetAsNumber();
				}
				else if (section == 3)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->m_viptype = lpMemScript->GetNumber();

					this->m_days = lpMemScript->GetAsNumber();
				}
			}
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CGoldenArcher::CGGoldenArcherCountRecv(int aIndex) // OK
{
	#if(GAMESERVER_UPDATE<=603)

	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	if(((lpObj->GoldenArcherTransaction == 0) ? (lpObj->GoldenArcherTransaction++) : lpObj->GoldenArcherTransaction) != 0)
	{
		return;
	}

	this->m_count = 1;

	SDHP_GOLDEN_ARCHER_COUNT_SEND pMsg;

	pMsg.header.set(0x94,0x00,sizeof(pMsg));

	pMsg.index = lpObj->Index;

	memcpy(pMsg.account,lpObj->Account,sizeof(pMsg.account));

	gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

	#endif
}

void CGoldenArcher::CGGoldenArcherRegisterRecv(PMSG_GOLDEN_ARCHER_COUNT_RECV* lpMsg,int aIndex) // OK
{
	#if(GAMESERVER_UPDATE<=603)

	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	int count = gItemManager.GetInventoryItemCount(lpObj,GET_ITEM(14,21),0);

	gItemManager.DeleteInventoryItemCount(lpObj,GET_ITEM(14,21),0,count);

	this->GDGoldenArcherAddCountSaveSend(aIndex,count);

	this->CGGoldenArcherCountRecv(aIndex);
	
	#endif
}

void CGoldenArcher::CGGoldenArcherCloseRecv(int aIndex) // OK
{
	#if(GAMESERVER_UPDATE<=603)

	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	if(lpObj->Interface.use == 0 || lpObj->Interface.type == INTERFACE_NONE || lpObj->Interface.type != INTERFACE_GOLDEN_ARCHER)
	{
		return;
	}

	lpObj->Interface.use = 0;
	lpObj->Interface.type = INTERFACE_NONE;
	lpObj->Interface.state = 0;

	#endif
}

void CGoldenArcher::DGGoldenArcherCountRecv(SDHP_GOLDEN_ARCHER_COUNT_RECV* lpMsg) // OK
{
	#if(GAMESERVER_UPDATE<=603)

	if(gObjIsAccountValid(lpMsg->index,lpMsg->account) == 0)
	{
		LogAdd(LOG_RED,"[DGGoldenArcherCountRecv] Invalid Account [%d](%s)",lpMsg->index,lpMsg->account);
		CloseClient(lpMsg->index);
		return;
	}

	LPOBJ lpObj = &gObj[lpMsg->index];

	lpObj->GoldenArcherTransaction = 0;

	PMSG_GOLDEN_ARCHER_COUNT_SEND pMsg;

	pMsg.header.set(0x94,sizeof(pMsg));

	pMsg.type = 0;

	pMsg.count = lpMsg->count;

	if(this->m_type > 0)
	{
		this->GoldenArcherReward(lpObj->Index,lpMsg->count); //reward
	}

	memset(pMsg.code,0,sizeof(pMsg.code));

	DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);

	#endif
}

void CGoldenArcher::GDGoldenArcherAddCountSaveSend(int aIndex, DWORD count) // OK
{
	#if(GAMESERVER_UPDATE<=603)

	SDHP_GOLDEN_ARCHER_ADD_COUNT_SAVE_SEND pMsg;

	pMsg.header.set(0x94,0x30,sizeof(pMsg));

	pMsg.index = aIndex;

	memcpy(pMsg.account,gObj[aIndex].Account,sizeof(pMsg.account));

	pMsg.count = count;

	gDataServerConnection.DataSend((BYTE*)&pMsg,sizeof(pMsg));

	#endif
}

void CGoldenArcher::GoldenArcherReward(int aIndex, DWORD count)
{
	LPOBJ lpObj = &gObj[aIndex];

	this->m_count = 1;

	if(this->m_active == 1)
	{
		if(count >= this->m_quantity)
		{
			//Types
			//0 - Normal
			//1 - Atributos
			//2 - Itens
			//3 - Gold
			//4 - Vip
		
			if(this->m_type == 1)
			{
				lpObj->Reset += this->m_resets;
				lpObj->LevelUpPoint += this->m_leveluppoint;
				GCMoneySend(lpObj->Index,lpObj->Money += this->m_money);
				GDResetInfoSaveSend(lpObj->Index,0,0,0);
				GCLevelUpSend(lpObj);
				GDCharacterInfoSaveSend(lpObj->Index);	
				gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,"Você ganhou %d resets, %d pontos, %d de zen",this->m_resets,this->m_leveluppoint,this->m_money);
			}

			if(this->m_type == 2)
			{
				gItemBagManager.DropItemBySpecialValue(ITEM_BAG_GOLDEN_ARCHER,lpObj,lpObj->Map,lpObj->X,lpObj->Y);				
				gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,"Você ganhou um prêmio, parabéns!");
			
			}

			if(this->m_type == 3)
			{
				GDSetCoinSend(lpObj->Index, this->m_coin1, this->m_coin2, this->m_coin3, "Golden Archer");	
				gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,"Você ganhou %d Coin1, %d Coin2, %d Coin3",this->m_coin1,this->m_coin2,this->m_coin3);
			}

			if(this->m_type == 4)
			{
				GJAccountLevelSaveSend(lpObj->Index,this->m_viptype,this->m_days*86400);
				GJAccountLevelSend(lpObj->Index);				
				gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,"Parabéns você assinou o vip!");
			}

			GCFireworksSend(lpObj, lpObj->X, lpObj->Y);
		
			this->GDGoldenArcherAddCountSaveSend(aIndex,-(this->m_quantity));

			this->CGGoldenArcherCountRecv(aIndex);
		}
	}
}