#pragma once

#include "stdafx.h"

class UtilsEx
{
public:
	UtilsEx();
	virtual ~UtilsEx();

	void SetNop(DWORD dwSrcOffset, int Size);
	void SetByte(DWORD dwSrcOffset, BYTE bOpCode);
	void WriteJmp(DWORD dwSrcOffset, DWORD dwDstOffset);
	void HookThis(DWORD dwDstOffset, DWORD dwSrcOffset);
	void Protect(DWORD dwSrcOffset, int Size, DWORD dwNewProtect);
	DWORD UnProtect(DWORD dwSrcOffset, int Size);
	void HookOffset(DWORD my, DWORD tohook, BYTE type);
	void HookExactOffset(DWORD my, DWORD tohook, BYTE type);
	void SetCompleteHook(BYTE head,DWORD offset,...);
	void SetDword(DWORD offset,DWORD value);

private:

protected:
};
extern UtilsEx Utils;