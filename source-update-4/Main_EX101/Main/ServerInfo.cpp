#include "stdafx.h"
#include "ReadScript.h"


CServerInfo g_ServerInfo;

CServerInfo::CServerInfo()
{
	this->m_data.clear();
}

CServerInfo::~CServerInfo()
{
}

void CServerInfo::Load()
{
	//00953CFC - hook
	this->m_data.clear();

	this->Read("Data/Custom/ServerSide.txt");

	//SetDword(0x0061FC6C+1,(DWORD)"Testando1");
	//SetDword(0x0061FC8B+1,(DWORD)"Testando2");
	//SetDword(0x0061FCA4+1,(DWORD)"Testando3"); //ALTERAÇÃO É AQUI - UMA UNICA SALA

	//SetDword(0x0061FCFF+1,(DWORD)"Testando2");
	//SetDword(0x0061FD13+1,(DWORD)"Testando4");
	//SetDword(0x0061FD21+1,(DWORD)"Testando5"); //ALTERAÇÃO É AQUI - COM NOME NOPVP E DUAS SALAS NO MESMO SERVER

	//SetDword(0x0061FD3E+1,(DWORD)"Testando2");
	//SetDword(0x0061FD52+1,(DWORD)"Testando4");
	//SetDword(0x0061FD60+1,(DWORD)"Testando7"); //ALTERAÇÃO É AQUI - SEM NOME NOPVP E DUAS SALAS NO MESMO SERVER
	//SetByte(0x0061FC56+1,0);
	//MemorySet(0x0061FCDD, 0x90, 0x5); //Remove Leitura de NON-PVP
	////MemorySet(0x006201DC,0x90,0x5);
	//SetOp((LPVOID)0x0062026D, this->ServerDrawTextHook, ASM::CALL); //1.04j

}

void CServerInfo::Read(char* filename)
{
	SMDToken Token;

	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		return;
	}

	while(true)
	{
		Token = GetToken();

		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}

		SERVERINFO_DATA list;

		memcpy(list.ServerName, TokenString, sizeof(list.ServerName));

		Token = GetToken();
		list.SubServerNum = TokenNumber;

		Token = GetToken();
		memcpy(list.ServerText, TokenString, sizeof(list.ServerText));

		this->m_data.push_back(list);
	}

	fclose(SMDFile);
}

void CServerInfo::ServerDrawTextHook(int a1, int a2, LPCSTR ServerName, int a4, char a5, int a6)
{
	int v29 = 0;

	int v10 = 100 * (v29 + 20 * (*(DWORD*)0x6C42B0));



	if (a2 == 212)
	{
		pDrawInfo(a1, a2, "Server 1", a4, a5, a6);
	}
	else
	{
		pDrawInfo(a1, a2, "Server 2", a4, a5, a6);
	}

	char Texto[234];

	sprintf(Texto, "%d,%d,%d,%d,%s", v10, a2, a4, a6, ServerName);

	Console.Write(Texto,0,1);

	//414, 212, 0, 0, RoxMU - 1 Connect
	//414, 232, 0, 0, RoxMU - 2 Connect
}

