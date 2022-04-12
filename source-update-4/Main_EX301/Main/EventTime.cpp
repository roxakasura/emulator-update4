#include "stdafx.h"
#include "EventTime.h"
#include "Interface.h"
#include "PlayerSystem.h"
#include "Protect.h"
#include "Protocol.h"
#include "Reconnect.h"
#include "Util.h"

CCustomEventTime::CCustomEventTime()
{
}

CCustomEventTime gCustomEventTime;

void CCustomEventTime::Load(CUSTOM_EVENT_INFO* info) // OK
{
	for (int n = 0; n < MAX_EVENTTIME; n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomEventTime::SetInfo(CUSTOM_EVENT_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_EVENTTIME)
	{
		return;
	}

	this->m_CustomEventInfo[info.Index] = info;
}

void CCustomEventTime::ClearCustomEventTime() // OK
{
	for (int n = 0; n < MAX_EVENTTIME; n++)
	{
		gCustomEventTime[n].time = -1;
	}
	this->count = 0;
	this->EventTimeEnable = 0;
}

void CCustomEventTime::GCReqEventTime(PMSG_CUSTOM_EVENTTIME_RECV* lpMsg) // OK
{
	this->count = lpMsg->count;

	for (int n = 0; n < lpMsg->count; n++)
	{
		CUSTOM_EVENTTIME_DATA* lpInfo = (CUSTOM_EVENTTIME_DATA*)(((BYTE*)lpMsg) + sizeof(PMSG_CUSTOM_EVENTTIME_RECV) + (sizeof(CUSTOM_EVENTTIME_DATA)*n));

		this->gCustomEventTime[n].index = lpInfo->index;
		this->gCustomEventTime[n].time = lpInfo->time;

		if (this->gCustomEventTime[n].index == 7)
		{
			this->gCustomEventTime[n].time = -1;
		}

		if (this->gCustomEventTime[n].index >= 28 && this->gCustomEventTime[n].time != -1) this->Arena = 1;
	}

	this->EventTimeEnable = 1;
}

int pagina;

void CCustomEventTime::DrawEventTimePanelWindow()
{
	if (JanelaTeste != 0)
	{
		char path[200];
		sprintf_s(path, "Custom\\Menu_Button03.tga");
		pLoadImageTGA(path, 26, 0x2600, 0x2900, 0, 1);

		*(BYTE*)0x78F7CE = 0;
		//pSetCursorFocus = 154;
		*(BYTE*)0x7513354 = 1;
		int result;
		float v1; float v2; float v3; float v4; float v5; float v6;
		signed int i;

		v1 = (double)60;	//Posição Y das Janelas
		v2 = (double)220;	//Largura das Janelase
		v4 = (double)210;	//Posição X das Janelas

		v3 = (double)(12); //Y barra de cima
		RenderBitmap(252, v4, v3 + v1, v2, 5.0, 0, 0, 0.83203125, 0.625, 1, 1, 0.0);

		for (i = 0; i < 7; ++i)
		{
			v5 = (double)12 + (double)(40 * i + 5); //Y do fundo
			RenderBitmap(251, v4, v5 + v1, v2, 40.0, 0, 0, 0.83203125, 0.625, 1, 1, 0.0);
		}

		v6 = (double)(12) + 280.0; //Y barra de baixo
		RenderBitmap(252, v4, v6 + v1, v2, 5.0, 0, 0, 0.83203125, 0.625, 1, 1, 0.0);

		
		//RenderBitmap(26, v4 + 70, v6 + v1 - 22, 19.0, 20.0, 0, 0, 0.59375, 0.625, 1, 1, 0); //Previous
		//RenderBitmap(27, v4 + 130, v6 + v1 - 22, 19.0, 20.0, 0, 0, 0.59375, 0.625, 1, 1, 0); //Next
		
		char Title[256];
		char TitleEvent[256];
		char TitleTime[256];
		// --- Título
		pSetBlend(true);
		pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
		wsprintf(Title, "Time Events");
		pDrawText(pTextThis(), v4 + 90, v1 + 30, Title, 0, 0, (PINT)3, 0);

		if(pCheckMouseOver(342,335,10,10,1) && pClickCursor && this->Page == 0) //Pag 0 for 1
		{
			this->Page = 1;
			RenderBitmap(26, v4 + 216, v6 + v1 + 65, 10, 10, 0.319999963, 0.4549999833, 0.2610003054, 0.1405000836, 0, 0, 0);
		}
		else
		{
			RenderBitmap(26, v4 + 216, v6 + v1 + 65, 10, 10, 0.319999963, 0.00800000038, 0.2610003054, 0.1405000836, 0, 0, 0);
		}

		if(pCheckMouseOver(292,333,10,10,1) && pClickCursor && this->Page == 1) //Pag 1 for 0
		{
			this->Page = 0;
			RenderBitmap(26, v4 + 153, v6 + v1 + 65, 10, 10, 0.02999999747, 0.4549999833, 0.2610003054, 0.1405000836, 0, 0, 0);
		}
		else
		{
			RenderBitmap(26, v4 + 153, v6 + v1 + 65, 10, 10, 0.02999999747, 0.00800000038, 0.2610003054, 0.1405000836, 0, 0, 0);
		}

		if (this->Page == 0)
		{
			if (this->EventTimeEnable == 1)
			{
				// --- Event Name
				pSetBlend(true);
				pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
				wsprintf(TitleEvent, "Event:");
				pDrawText(pTextThis(), v4 + 45, v1 + 41, TitleEvent, 0, 0, (PINT)3, 0);
				// --- Event Time
				pSetBlend(true);
				pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
				wsprintf(TitleTime, "Time:");
				pDrawText(pTextThis(), v4 + 145, v1 + 41, TitleTime, 0, 0, (PINT)3, 0);

				if ((GetTickCount() - this->EventTimeTickCount) > 1000)
				{
					for (int i = 0; i < this->count; i++)
					{
						if (this->gCustomEventTime[i].time > 0)
						{
							this->gCustomEventTime[i].time = this->gCustomEventTime[i].time - 1;
						}
					}
					this->EventTimeTickCount = GetTickCount();
				}

				char text1[20];
				char text2[30];
				int totalseconds;
				int hours;
				int minutes;
				int seconds;
				int days;

				int line = 0;

				for (int i = (14 * Page) + 0; i < (14 * Page) + 14; i++)
				{
					if (this->gCustomEventTime[i].time <= -1)
					{
						continue;
					}
					else if (this->gCustomEventTime[i].time == 0)
					{
						wsprintf(text2, "Online");
					}
					else
					{
						totalseconds = this->gCustomEventTime[i].time;
						hours = totalseconds / 3600;
						minutes = (totalseconds / 60) % 60;
						seconds = totalseconds % 60;
						wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);

						if (hours > 23)
						{
							days = hours / 24;
							wsprintf(text2, "%d day(s)+", days);
						}
						else
						{
							wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
						}
					}

					// --- Event Name Interface (carregado pela config)
					pSetBlend(true);
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 45, v1 + 55 + (line), this->m_CustomEventInfo[i].Name, 0, 0, (PINT)3, 0);

					// --- Event Time Interface (carregado pela config)
					pSetBlend(true);
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 145, v1 + 55 + (line), text2, 0, 0, (PINT)3, 0);
					line += 12;
				}

			}
			else
			{
				if (this->EventTimeLoad == 1)
				{
					// --- Line Interface (carregado pela config)
					pSetBlend(true);
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 20, v1 + 100, "Loading ..", 0, 0, (PINT)3, 0);
					this->EventTimeLoad = 2;
				}
				else if (this->EventTimeLoad == 2)
				{
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 20, v1 + 100, "Loading ..", 0, 0, (PINT)3, 0);
					this->EventTimeLoad = 3;
				}
				else if (this->EventTimeLoad == 3)
				{
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 20, v1 + 100, "Loading ..", 0, 0, (PINT)3, 0);
					this->EventTimeLoad = 4;
				}
				else if (this->EventTimeLoad == 4)
				{
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 20, v1 + 100, "Loading ..", 0, 0, (PINT)3, 0);
					this->EventTimeLoad = 0;
				}
				else
				{
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 20, v1 + 100, "Loading ..", 0, 0, (PINT)3, 0);
					this->EventTimeLoad = 1;
				}
			}
		}

		if (this->Page == 1)
		{
			if (this->EventTimeEnable == 1)
			{
				// --- Event Name
				pSetBlend(true);
				pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
				wsprintf(TitleEvent, "Invasion:");
				pDrawText(pTextThis(), v4 + 45, v1 + 41, TitleEvent, 0, 0, (PINT)3, 0);
				// --- Event Time
				pSetBlend(true);
				pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
				wsprintf(TitleTime, "Time:");
				pDrawText(pTextThis(), v4 + 145, v1 + 41, TitleTime, 0, 0, (PINT)3, 0);

				if ((GetTickCount() - this->EventTimeTickCount) > 1000)
				{
					for (int i = 0; i < this->count; i++)
					{
						if (this->gCustomEventTime[i].time > 0)
						{
							this->gCustomEventTime[i].time = this->gCustomEventTime[i].time - 1;
						}
					}
					this->EventTimeTickCount = GetTickCount();
				}

				char text1[20];
				char text2[30];
				int totalseconds;
				int hours;
				int minutes;
				int seconds;
				int days;

				int line = 0;

				for (int i = (14 * Page) + 0; i < (14 * Page) + 14; i++)
				{
					if (this->gCustomEventTime[i].time <= -1)
					{
						continue;
					}
					else if (this->gCustomEventTime[i].time == 0)
					{
						wsprintf(text2, "Online");
					}
					else
					{
						totalseconds = this->gCustomEventTime[i].time;
						hours = totalseconds / 3600;
						minutes = (totalseconds / 60) % 60;
						seconds = totalseconds % 60;
						wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);

						if (hours > 23)
						{
							days = hours / 24;
							wsprintf(text2, "%d day(s)+", days);
						}
						else
						{
							wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
						}
					}

					// --- Event Name Interface (carregado pela config)
					pSetBlend(true);
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 45, v1 + 55 + (line), this->m_CustomEventInfo[i].Name, 0, 0, (PINT)3, 0);

					// --- Event Time Interface (carregado pela config)
					pSetBlend(true);
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 145, v1 + 55 + (line), text2, 0, 0, (PINT)3, 0);
					line += 12;
				}

			}
			else
			{
				if (this->EventTimeLoad == 1)
				{
					// --- Line Interface (carregado pela config)
					pSetBlend(true);
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 20, v1 + 100, "Loading ..", 0, 0, (PINT)3, 0);
					this->EventTimeLoad = 2;
				}
				else if (this->EventTimeLoad == 2)
				{
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 20, v1 + 100, "Loading ..", 0, 0, (PINT)3, 0);
					this->EventTimeLoad = 3;
				}
				else if (this->EventTimeLoad == 3)
				{
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 20, v1 + 100, "Loading ..", 0, 0, (PINT)3, 0);
					this->EventTimeLoad = 4;
				}
				else if (this->EventTimeLoad == 4)
				{
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 20, v1 + 100, "Loading ..", 0, 0, (PINT)3, 0);
					this->EventTimeLoad = 0;
				}
				else
				{
					pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
					pDrawText(pTextThis(), v4 + 20, v1 + 100, "Loading ..", 0, 0, (PINT)3, 0);
					this->EventTimeLoad = 1;
				}
			}
		}
	}
}
