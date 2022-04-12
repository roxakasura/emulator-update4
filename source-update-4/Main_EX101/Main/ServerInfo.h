#pragma once

#include "stdafx.h"
#include <vector>

struct SERVERINFO_DATA
{
	char ServerName[20];
	int SubServerNum;
	char ServerText[50];
};

#define pDrawInfo				((int(__cdecl*)(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)) 0x00548620)
class CServerInfo

{
public:
		 CServerInfo();
		 ~CServerInfo();

	void Load();
	void Read(char* filename);

	static void ServerDrawTextHook(int a1, int a2, LPCSTR a3, int a4, char a5, int a6);

	std::vector<SERVERINFO_DATA> m_data;
};
extern CServerInfo g_ServerInfo;