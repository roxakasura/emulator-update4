// Notice.cpp: implementation of the CNotice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Notice.h"
#include "MemScript.h"
#include "Util.h"

CNotice gNotice;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNotice::CNotice() // OK
{
	this->m_count = 0;

	this->m_NoticeValue = 0;

	this->m_NoticeTime = GetTickCount();
}

CNotice::~CNotice() // OK
{

}

void CNotice::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_count = 0;

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			NOTICE_INFO info;

			memset(&info,0,sizeof(info));

			strcpy_s(info.Message,lpMemScript->GetString());

			info.Type = lpMemScript->GetAsNumber();

			info.Count = lpMemScript->GetAsNumber();

			info.Opacity = lpMemScript->GetAsNumber();

			info.Delay = lpMemScript->GetAsNumber();
			
			info.ColorR = lpMemScript->GetAsNumber();
			
			info.ColorG = lpMemScript->GetAsNumber();
			
			info.ColorB = lpMemScript->GetAsNumber();

			info.Speed = lpMemScript->GetAsNumber();

			info.RepeatTime = lpMemScript->GetAsNumber()*1000;

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CNotice::SetInfo(NOTICE_INFO info) // OK
{
	if(this->m_count < 0 || this->m_count >= MAX_NOTICE)
	{
		return;
	}

	this->m_NoticeInfo[this->m_count++] = info;
}

void CNotice::MainProc() // OK
{
	if(this->m_count == 0)
	{
		return;
	}

	NOTICE_INFO* lpInfo = &this->m_NoticeInfo[this->m_NoticeValue];

	if((GetTickCount()-this->m_NoticeTime) >= ((DWORD)lpInfo->RepeatTime))
	{
		this->m_NoticeValue = (((this->m_NoticeValue+1)>=this->m_count)?0:(this->m_NoticeValue+1));
		this->m_NoticeTime = GetTickCount();

		if(lpInfo->Type < 2)
		{
			this->GCNoticeSendToAll(lpInfo->Type,lpInfo->Count,lpInfo->Opacity,lpInfo->Delay,RGB(lpInfo->ColorR,lpInfo->ColorG,lpInfo->ColorB),lpInfo->Speed,"%s",lpInfo->Message);
		}
		else
		{
			this->MakeSlideBarAll(lpInfo->Message,lpInfo->ColorR,lpInfo->ColorG,lpInfo->ColorB,lpInfo->Opacity,lpInfo->Speed);
		}
	}
}

void CNotice::GCNoticeSend(int aIndex,BYTE type,BYTE count,BYTE opacity,WORD delay,DWORD color,BYTE speed,char* message,...) // OK
{
	char buff[256] = {0};

	va_list arg;
	va_start(arg,message);
	vsprintf_s(buff,message,arg);
	va_end(arg);

	int size = strlen(buff);

	size = ((size>MAX_MESSAGE_SIZE)?MAX_MESSAGE_SIZE:size);

	PMSG_NOTICE_SEND pMsg;

	pMsg.header.set(0x0D,(sizeof(pMsg)-(sizeof(pMsg.message)-(size+1))));

	pMsg.type = type;

	pMsg.count = count;

	pMsg.opacity = opacity;

	pMsg.delay = delay;

	pMsg.color = color;

	pMsg.speed = speed;

	memcpy(pMsg.message,buff,size);

	pMsg.message[size] = 0;

	DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);
}

void CNotice::GCNoticeSendToAll(BYTE type,BYTE count,BYTE opacity,WORD delay,DWORD color,BYTE speed,char* message,...) // OK
{
	char buff[256] = {0};

	va_list arg;
	va_start(arg,message);
	vsprintf_s(buff,message,arg);
	va_end(arg);

	int size = strlen(buff);

	size = ((size>MAX_MESSAGE_SIZE)?MAX_MESSAGE_SIZE:size);

	PMSG_NOTICE_SEND pMsg;

	pMsg.header.set(0x0D,(sizeof(pMsg)-(sizeof(pMsg.message)-(size+1))));

	pMsg.type = type;

	pMsg.count = count;

	pMsg.opacity = opacity;

	pMsg.delay = delay;

	pMsg.color = color;

	pMsg.speed = speed;

	memcpy(pMsg.message,buff,size);

	pMsg.message[size] = 0;

	for(int n=OBJECT_START_USER;n < MAX_OBJECT;n++)
	{
		if(gObjIsConnectedGP(n) != 0)
		{
			DataSend(n,(BYTE*)&pMsg,pMsg.header.size);
		}
	}
}

void CNotice::MakeSlideBarAll(LPCTSTR szText, BYTE RGB1, BYTE RGB2, BYTE RGB3, BYTE Trans, BYTE Velo)
{
	BYTE buff[0xFF - 0x0e];
	FillMemory(buff, (0xFF - 0x0e), 0x20);
	BYTE Len = (BYTE)strlen(szText);
	buff[0] = 0xC1;
	buff[1] = Len + 0x0E;
	buff[2] = 0x0D;
	buff[3] = 0x0A;
	buff[4] = 0x01;
	buff[5] = 0x01;
	buff[6] = 0x00;
	buff[7] = 0x00;
	buff[8] = RGB1; //R
	buff[9] = RGB2; //G
	buff[10] = RGB3;//B
	buff[11] = Trans;//Transparencia
	buff[12] = 0x14 + Velo;//Velocidade
	strncpy((char*)&buff[0x0d], szText, Len);
	buff[Len + 0x0d] = 0;
	
	for(int n=OBJECT_START_USER;n < MAX_OBJECT;n++)
	{
		if(gObjIsConnectedGP(n) != 0)
		{
			DataSend(n, (unsigned char*)buff, buff[1]);
		}
	}
}