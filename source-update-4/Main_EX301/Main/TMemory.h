#include "stdafx.h"
#pragma once
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------

namespace ASM
{
	enum T
	{
		JMP			= 0xE9,
		JE			= 0x74,
		JNE			= 0x75,
		JGE			= 0x7D,
		NOP			= 0x90,
		CALL		= 0xE8,
		CALLD		= 0xFF,
		PUSH		= 0x68,
	};
};


 #define MEMORY4(value) *(unsigned int*)(value)
 #define MEMORY2(value) *(unsigned short*)(value)
 #define MEMORY1(value) *(unsigned char*)(value)
//Opcode const
#define _asm_call       0xE8
#define _asm_push       0x68
#define _asm_jmp        0xE9
#define _asm_jmps       0xEB//jmp short
#define _asm_jes        0x74
#define _asm_jnzs       0x75
#define _asm_jnz2       0x0F85//jmp short
#define _asm_nop        0x90
#define _asm_retn       0xC3
#define _asm_push_eax 0x50
bool ProcessReduceMemory();
DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
DWORD ReadMemory(const LPVOID lpAddress, LPVOID lpBuf, const UINT uSize);
DWORD SetByte(const LPVOID dwOffset, const BYTE btValue);
DWORD GetByte(const LPVOID dwOffset, BYTE & btValue);
DWORD SetWord(const LPVOID dwOffset, const WORD wValue);
DWORD GetWord(const LPVOID dwOffset, WORD & wValue);
DWORD SetDword(const LPVOID dwOffset, const DWORD dwValue);
DWORD GetDword(const LPVOID dwOffset, DWORD & dwValue);
DWORD SetFloat(const LPVOID dwOffset, float fValue);
DWORD GetFloat(const LPVOID dwOffset, float & fValue);
DWORD SetDouble(const LPVOID dwOffset, double dValue);
DWORD SetJmp2(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
DWORD SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
DWORD SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, BYTE cmd);
DWORD SetPush(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd);
DWORD SetRange2(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue);
DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd);
void SetNop(DWORD dwOffset,int Size);
void HookThis(DWORD dwMyFuncOffset,DWORD dwJmpOffset);
void Access(DWORD dwOffset, int t_size);
void HookAddress(DWORD dwAddrOffst, DWORD dwNewOffst, BYTE new_Cmd);
void SetCompleteHook2(BYTE head, DWORD offset, ...); // OK;
DWORD SetOp_(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, BYTE cmd);
//---------------------------------------------------------------------------


