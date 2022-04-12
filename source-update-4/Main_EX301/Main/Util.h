#pragma once

#define CRASH_APPLICATION_MACRO _asm _emit 0xFF _asm _emit 0x25 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00

enum eMacroProtectionNumber
{
	MACRO_PROTECTION_NUMBER_NONE = 0,
	MACRO_PROTECTION_NUMBER_LEVEL1 = 1,
	MACRO_PROTECTION_NUMBER_LEVEL2 = 2,
	MACRO_PROTECTION_NUMBER_LEVEL3 = 3,
	MACRO_PROTECTION_NUMBER_LEVEL4 = 4,
	MACRO_PROTECTION_NUMBER_LEVEL5 = 5,
};

struct PROCESS_CACHE_INFO
{
	DWORD ProcessId;
	DWORD TickCount;
};

void SafeExitProcess();
void SetByte(DWORD offset,BYTE value);
void SetWord(DWORD offset,WORD value);
void SetDword(DWORD offset,DWORD value);
void SetFloat2(DWORD offset,float value);
void SetDouble(DWORD offset,double value);
void SetCompleteHook(BYTE head,DWORD offset,...);
void MemoryCpy(DWORD offset,void* value,DWORD size);
void MemorySet(DWORD offset,DWORD value,DWORD size);
void VirtualizeOffset(DWORD offset,DWORD size);
void PacketArgumentEncrypt(char* out_buff,char* in_buff,int size);
bool FileExists(char * name);
void HookOffset(DWORD my, DWORD tohook, BYTE type);
char* ConvertModuleFileName(char* name);
