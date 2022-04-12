#pragma once

#include "stdafx.h"
#include <vector>

#define MAX_SERVER_CLASS 20

struct SERVERINFO_DATA
{
	int Index;
	int SubServerNum;
	char ServerName[20];
	char ServerText[50];
};

class CServerInfo
{
public:
	CServerInfo();
	~CServerInfo();
	void Load();
	void Init(SERVERINFO_DATA * info);
	static void ServerDrawTextHook(int a1, char *a2, char* ServerName, int SubSala, char* TextConnect, char* TextConnect2);
public:
	std::vector<SERVERINFO_DATA> m_data;
};
extern CServerInfo g_ServerInfo;