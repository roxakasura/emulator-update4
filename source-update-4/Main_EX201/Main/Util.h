#pragma once

void SetByte(DWORD offset, BYTE value);

void SetWord(DWORD offset, WORD value);

void SetDword(DWORD offset, DWORD value);

void SetFloat(DWORD offset, float value);

void SetDouble(DWORD offset, double value);

void SetCompleteHook(BYTE head, DWORD offset, ...);

void MemoryCpy(DWORD offset, void* value, DWORD size);

void MemorySet(DWORD offset, DWORD value, DWORD size);

void VirtualizeOffset(DWORD offset, DWORD size);

void PacketArgumentEncrypt(char* out_buff, char* in_buff, int size);

char* ConvertModuleFileName(char* name);

bool FileExists(char* name);

int GetTextPosX(char* buff, int PosX);

int GetTextPosY(char* buff, int PosY);

float ImgCenterScreenPosX(float Size);

float ImgCenterScreenPosY(float Size);

DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);

DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd);