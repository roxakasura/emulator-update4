#include "StdAfx.h"

CUser gUser;

OBJECTSTRUCT_PLAYER * lpObj;

void CUser::Load()
{
	gToolKit.SetRange((LPVOID)0x005990AF, 16, ASM::NOP);
	gToolKit.SetOp((LPVOID)0x005990AF, (LPVOID)this->GetStruct, ASM::JMP);

	gToolKit.SetRange((LPVOID)0x005DEE8E, 6, ASM::NOP);
	gToolKit.SetJmp((LPVOID)0x005DEE89, this->gObjFix);
}

void __declspec(naked) CUser::GetStruct()
{
	_asm
	{
		MOV ECX, DWORD PTR DS:[0x7666A78];
		// ---
		MOV gUser.dwStructAddr, ECX;
		// ---
		XOR EAX, EAX;
		MOV DX, WORD PTR DS:[ECX+0x26];
		MOV AX, WORD PTR DS:[ECX+0x22];
	}
	// ---
	_asm
	{
		MOV gUser.gTmpEax, EAX
		MOV gUser.gTmpEsi, ESI
		MOV gUser.gTmpEdi, EDI
		MOV gUser.gTmpEcx, ECX
		MOV gUser.gTmpEdx, EDX
		MOV gUser.gTmpEbx, EBX
		MOV gUser.gTmpEsp, ESP
		MOV gUser.gTmpEbp, EBP
	}
	// ---
	lpObj = (OBJECTSTRUCT_PLAYER*) gUser.dwStructAddr;
	// ---
	memcpy(&gUser.m_Player, lpObj, sizeof(OBJECTSTRUCT_PLAYER));
	// ---
	_asm
	{
		MOV EAX, gUser.gTmpEax
		MOV ESI, gUser.gTmpEsi
		MOV EDI, gUser.gTmpEdi
		MOV ECX, gUser.gTmpEcx
		MOV EDX, gUser.gTmpEdx
		MOV EBX, gUser.gTmpEbx
		MOV ESP, gUser.gTmpEsp
		MOV EBP, gUser.gTmpEbp
		// ---
		MOV gUser.dwGetStructJmp, 0x005990BF;
		// ---
		JMP gUser.dwGetStructJmp;
	}
}

void __declspec(naked) CUser::gObjFix()
{
	_asm
	{
		MOV EAX, ViewPoint
		PUSH EAX
		PUSH 0x76B1BF0
		PUSH EDX
		MOV EDI, 0x005DEE94
		JMP EDI
	}
}