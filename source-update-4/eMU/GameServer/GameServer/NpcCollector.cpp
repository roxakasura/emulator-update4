#include "stdafx.h"
#include "DSProtocol.h"
#include "MemScript.h"
#include "Message.h"
#include "Notice.h"
#include "ItemManager.h"
#include "Path.h"
#include "ServerInfo.h"
#include "User.h"
#include "Util.h"
#include "NpcCollector.h"


CCustomNpcCollector gCustomNpcCollector;

void CCustomNpcCollector::Load(char* path)
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

	for (int n = 0; n < MAX_ITEM_LIST; n++)
	{
		this->m_Data[this->m_count].m_Cat = -1;

		this->m_Data[this->m_count].m_Item = -1;

		this->m_Data[this->m_count].m_Coin1 = 0;

		this->m_Data[this->m_count].m_Coin2 = 0;

		this->m_Data[this->m_count].m_Coin3 = 0;
	}

	this->m_count = 0;

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

					this->m_npcindex = lpMemScript->GetAsNumber();

					this->m_quantity = lpMemScript->GetAsNumber();

				}
				else if (section == 1)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->m_Data[this->m_count].m_Cat = lpMemScript->GetNumber();

					this->m_Data[this->m_count].m_Item = lpMemScript->GetAsNumber();

					this->m_Data[this->m_count].m_Coin1 = lpMemScript->GetAsNumber();

					this->m_Data[this->m_count].m_Coin2 = lpMemScript->GetAsNumber();

					this->m_Data[this->m_count].m_Coin3 = lpMemScript->GetAsNumber();

					this->m_count++;
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


bool CCustomNpcCollector::NpcTalk(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (lpNpc->Class == this->m_npcindex)
	{
		if (this->m_active == 0)
		{
			GCChatTargetSend(lpObj, lpNpc->Index, gMessage.GetMessage(31));
			return false;
		}	
		
		if (lpObj->Interface.use != 0)
		{
			return false;
		}

		for (int i = 0; i < this->m_count; i++)
		{
			if (gItemManager.GetInventoryItemCount(lpObj, GET_ITEM(this->m_Data[i].m_Cat, this->m_Data[i].m_Item), 0) >= this->m_quantity)
			{
				//-- Reward
				GCChatTargetSend(lpObj, lpNpc->Index, gMessage.GetMessage(33));

				GCFireworksSend(lpNpc, lpNpc->X, lpNpc->Y);

				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(34));

				GDSetCoinSend(lpObj->Index, this->m_Data[i].m_Coin1, this->m_Data[i].m_Coin2, this->m_Data[i].m_Coin3, "NpcCollector");

				gItemManager.DeleteInventoryItemCount(lpObj, GET_ITEM(this->m_Data[i].m_Cat, this->m_Data[i].m_Item), 0, this->m_quantity);

				return true;
			}
		}

		char Alert[255];

		sprintf_s(Alert, gMessage.GetMessage(32), this->m_quantity);

		GCChatTargetSend(lpObj, lpNpc->Index, Alert);

		return false;
	}

	return false;

}
