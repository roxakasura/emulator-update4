#include "stdafx.h"
#include "Protect.h"
#include "CCRC32.H"
#include "Util.h"

CProtect gProtect;

CProtect::CProtect()
{

}

CProtect::~CProtect()
{

}

bool CProtect::ReadMainFile(char* name)
{
	CCRC32 CRC32;

	if (CRC32.FileCRC(name, &this->m_ClientFileCRC, 1024) == 0)
	{
		return false;
	}

	HANDLE file = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, 0);

	if (file == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	if (GetFileSize(file, 0) != sizeof(MAIN_FILE_INFO))
	{
		CloseHandle(file);

		return false;
	}

	DWORD OutSize = 0;

	if (ReadFile(file, &this->m_MainInfo, sizeof(MAIN_FILE_INFO), &OutSize, 0) == 0)
	{
		CloseHandle(file);

		return false;
	}

	for (int n = 0; n < sizeof(MAIN_FILE_INFO); n++)
	{
		((BYTE*)&this->m_MainInfo)[n] += (BYTE)(0x5D ^ HIBYTE(n));

		((BYTE*)&this->m_MainInfo)[n] ^= (BYTE)(0xA7 ^ LOBYTE(n));
	}

	CloseHandle(file);

	return true;
}

void CProtect::CheckLauncher()
{
	if ((this->m_MainInfo.LauncherType & 1) == 0)
	{
		return;
	}

	HANDLE H = OpenMutex(MUTEX_ALL_ACCESS, 0, this->m_MainInfo.LauncherName);

	if (H == 0)
	{
		MessageBox(0, "Open Game with launcher!", "Error", MB_OK | MB_ICONERROR);

		ExitProcess(0);
	}

	ReleaseMutex(H);

	CloseHandle(H);
}

void CProtect::CheckInstance()
{
	if ((this->m_MainInfo.LauncherType & 2) == 0)
	{
		return;
	}

	char buff[256];

	wsprintf(buff, "XTEAM_MAIN_10405_%s", this->m_MainInfo.IpAddress);

	if (OpenMutex(MUTEX_ALL_ACCESS, 0, buff) == 0)
	{
		CreateMutex(0, 0, buff);
	}
	else
	{
		ExitProcess(0);
	}
}

void CProtect::CheckClientFile()
{
	if (this->m_MainInfo.ClientCRC32 == 0)
	{
		return;
	}

	char name[MAX_PATH] = { 0 };

	if (GetModuleFileName(0, name, sizeof(name)) == 0)
	{
		ExitProcess(0);
	}

	if (_stricmp(ConvertModuleFileName(name), this->m_MainInfo.ClientName) != 0)
	{
		ExitProcess(0);
	}

	CCRC32 CRC32;

	DWORD ClientCRC32;

	if (CRC32.FileCRC(this->m_MainInfo.ClientName, &ClientCRC32, 1024) == 0)
	{
		ExitProcess(0);
	}

	if (this->m_MainInfo.ClientCRC32 != ClientCRC32)
	{
		ExitProcess(0);
	}
}

void CProtect::CheckPluginFile()
{
	if (this->m_MainInfo.PluginCRC32 == 0)
	{
		return;
	}

	CCRC32 CRC32;

	DWORD PluginCRC32;

	if (CRC32.FileCRC(this->m_MainInfo.PluginName, &PluginCRC32, 1024) == 0)
	{
		ExitProcess(0);
	}

	if (this->m_MainInfo.PluginCRC32 != PluginCRC32)
	{
		ExitProcess(0);
	}

	HMODULE module = LoadLibrary(this->m_MainInfo.PluginName);

	if (module == 0)
	{
		ExitProcess(0);
	}

	void(*EntryProc)() = (void(*)())GetProcAddress(module, "EntryProc");

	if (EntryProc != 0)
	{
		EntryProc();
	}
}