// Protect.cpp: implementation of the CProtect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Protect.h"
#include "..\\..\\Util\\CCRC32.H"
#include "Util.h"

CProtect gProtect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtect::CProtect() // OK
{

}

CProtect::~CProtect() // OK
{

}

bool CProtect::ReadMainFile(char* name) // OK
{
	CCRC32 CRC32;

	if(CRC32.FileCRC(name,&this->m_ClientFileCRC,1024) == 0)
	{
		return 0;
	}

	HANDLE file = CreateFile(name,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	if(GetFileSize(file,0) != sizeof(MAIN_FILE_INFO))
	{
		CloseHandle(file);
		return 0;
	}

	DWORD OutSize = 0;

	if(ReadFile(file,&this->m_MainInfo,sizeof(MAIN_FILE_INFO),&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	for(int n=0;n < sizeof(MAIN_FILE_INFO);n++)
	{
		((BYTE*)&this->m_MainInfo)[n] += (BYTE)(0x95^HIBYTE(n));
		((BYTE*)&this->m_MainInfo)[n] ^= (BYTE)(0xCA^LOBYTE(n));
	}

	CloseHandle(file);
	return 1;
}

void CProtect::CheckClientFile() // OK
{
	if(this->m_MainInfo.ClientCRC32 == 0)
	{
		return;
	}

	char name[MAX_PATH] = {0};

	if(GetModuleFileName(0,name,sizeof(name)) == 0)
	{
		ExitProcess(0);
	}

	if(_stricmp(ConvertModuleFileName(name),this->m_MainInfo.ClientName) != 0)
	{
		ExitProcess(0);
	}

	CCRC32 CRC32;

	DWORD ClientCRC32;

	if(CRC32.FileCRC(this->m_MainInfo.ClientName,&ClientCRC32,1024) == 0)
	{
		MessageBox(0,"Main.exe CRC error!","Error",MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	if(this->m_MainInfo.ClientCRC32 != ClientCRC32)
	{
		MessageBox(0,"Main.exe CRC error!","Error",MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
}

void CProtect::CheckPlugin1File() // OK
{
	if(this->m_MainInfo.Plugin1CRC32 == 0)
	{
		return;
	}

	CCRC32 CRC32;

	DWORD Plugin1CRC32;

	if(CRC32.FileCRC(this->m_MainInfo.PluginName1,&Plugin1CRC32,1024) == 0)
	{
		MessageBox(0,"Plugin 1 CRC error!","Error",MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	if(this->m_MainInfo.Plugin1CRC32 != Plugin1CRC32)
	{
		ExitProcess(0);
	}

	HMODULE module = LoadLibrary(this->m_MainInfo.PluginName1);

	if(module == 0)
	{
		ExitProcess(0);
	}

	void (*EntryProc)() = (void(*)())GetProcAddress(module,"EntryProc");

	if(EntryProc != 0)
	{
		EntryProc();
	}
}

void CProtect::CheckPlugin2File() // OK
{
	if(this->m_MainInfo.Plugin2CRC32 == 0)
	{
		return;
	}

	CCRC32 CRC32;

	DWORD Plugin2CRC32;

	if(CRC32.FileCRC(this->m_MainInfo.PluginName2,&Plugin2CRC32,1024) == 0)
	{
		MessageBox(0,"Plugin 2 CRC error!","Error",MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	if(this->m_MainInfo.Plugin2CRC32 != Plugin2CRC32)
	{
		ExitProcess(0);
	}

	HMODULE module = LoadLibrary(this->m_MainInfo.PluginName2);

	if(module == 0)
	{
		ExitProcess(0);
	}

	void (*EntryProc)() = (void(*)())GetProcAddress(module,"EntryProc");

	if(EntryProc != 0)
	{
		EntryProc();
	}
}