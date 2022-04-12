#include "stdafx.h"
#include "ServerInfo.h"
#include "Util.h"
#include "TMemory.h"
#include "ReadScript.h"

CServerInfo g_ServerInfo;

CServerInfo::CServerInfo()
{
	this->m_data.clear();
}

CServerInfo::~CServerInfo()
{
}

void CServerInfo::Init(SERVERINFO_DATA * info)
{
	for( int n = 0; n < MAX_SERVER_CLASS; n++)
	{
		if(info[n].Index < 0 || info[n].Index >= MAX_SERVER_CLASS)
		{
			return;
		}
		this->m_data.push_back(info[n]);
	}
}

void CServerInfo::Load()
{
	//100%
	MemorySet(0x00413031, 0x90, 0x0E); // Fix servercode
	SetOp((LPVOID)0x004132DC, this->ServerDrawTextHook, ASM::CALL); //1.04j
    SetOp((LPVOID)0x00413182, this->ServerDrawTextHook, ASM::CALL); //1.04j
	//100% - login box
	SetOp((LPVOID)0x0040A59C, this->ServerDrawTextHook, ASM::CALL); //1.04j
	SetOp((LPVOID)0x0040A5D3, this->ServerDrawTextHook, ASM::CALL); //1.04j
	//100% - information chars (Key C)
	SetOp((LPVOID)0x005F6480, this->ServerDrawTextHook, ASM::CALL); //1.04j
	//remove name das salas ao lado
	SetDword(0x0041314B+3,-1);
	SetDword(0x00413142+3,-1);
	SetDword(0x0041311F+3,-1);
	SetDword(0x0041328A+3,-1);
	SetDword(0x004132A3+3,-1);
	SetDword(0x004132AC+3,-1);
}

void CServerInfo::ServerDrawTextHook(int a1, char *a2, char* ServerName, int SubServerNum, char* TextConnect,  char* TextConnect2)
{
	for(std::vector<SERVERINFO_DATA>::iterator it = g_ServerInfo.m_data.begin();it != g_ServerInfo.m_data.end();it++)	
	{
		if(!strcmp(ServerName, it->ServerName))
		{
			if(SubServerNum == it->SubServerNum)
			{
				pSetItemTextLine(a1, it->ServerText);
				return;
			}
		}
	}
	
	pSetItemTextLine(a1, a2, ServerName, SubServerNum, TextConnect, TextConnect2);
}

