#include "StdAfx.h"
#include "main.h"
#include "User.h"
#include "TMemory.h"
#include "PrintPlayer.h"

CUser gUser;

OBJECTSTRUCT_PLAYER * lpObj;

void CUser::Load()
{
	this->m_CursorX = -1;
	this->m_CursorY = -1;
	//this->m_Player.NextExperience = ViewNextExperience;
	//this->m_Player.Experience = ViewExperience;
	SetRange2((LPVOID)0x0059F802, 16, ASM::NOP);
	SetOp((LPVOID)0x0059F802, (LPVOID)this->GetStruct, ASM::JMP);
}

void CUser::Refresh()
{
	this->m_CursorX = pCursorX;
	this->m_CursorY = pCursorY;
	//this->m_Player.NextExperience = ViewNextExperience;
	//this->m_Player.Experience = ViewExperience;
}

void __declspec(naked) CUser::GetStruct()
{
	_asm
	{
		MOV ECX, DWORD PTR DS:[0x74D2C58];
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
		MOV gUser.dwGetStructJmp, 0x0059F812;
		// ---
		JMP gUser.dwGetStructJmp;
	}
}