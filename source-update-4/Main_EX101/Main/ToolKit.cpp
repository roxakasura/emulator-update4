#include "StdAfx.h"

CToolKit gToolKit;

void CToolKit::HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset)
{
	*(BYTE*)(dwJmpOffset) = 0xE9;
	// ---
	*(DWORD*)(dwJmpOffset + 1) = dwMyFuncOffset - (dwJmpOffset + 5);
}

DWORD CToolKit::WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
    DWORD dwErrorCode = 0;
    DWORD dwOldProtect = 0;
	// ---
    int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, & dwOldProtect);
	// ---
    if(iRes == 0)
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }
	// ---
    memcpy(lpAddress, lpBuf, uSize);
	// ---
    DWORD dwBytes = 0;
	// ---
    iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, & dwBytes);
	// ---
    if(iRes == 0)
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }
	// ---
    return 0x00;
}

DWORD CToolKit::SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[5];
	// ---
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ---
	btBuf[0] = 0xE9;
	// ---
	memcpy((LPVOID)&btBuf[1], (LPVOID) &dwShift, sizeof(ULONG_PTR));
	// ---
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}

DWORD CToolKit::SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[6];
	// ---
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;
	// ---
	btBuf[0] = 0x0F;
	btBuf[1] = 0x8F;
	// ---
	memcpy((LPVOID)&btBuf[2], (LPVOID)&dwShift, sizeof(ULONG_PTR));
	// ---
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}

DWORD CToolKit::SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[6];
	// ---
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;
	// ---
	btBuf[0] = 0x0F;
	btBuf[1] = 0x87;
	// ---
	memcpy((LPVOID)&btBuf[2], (LPVOID)&dwShift, sizeof(ULONG_PTR));
	// ---
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}

DWORD CToolKit::SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
	BYTE btBuf[5];
	// ---
	DWORD dwShift = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ---
	btBuf[0] = cmd;
	// ---
	memcpy((LPVOID)&btBuf[1], (LPVOID)&dwShift, sizeof(ULONG_PTR));
	// ---
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}

DWORD CToolKit::SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue)
{
	BYTE * lpBuf = new BYTE[wCount];
	// ---
	memset(lpBuf, btValue, wCount);
	// ---
	return WriteMemory(dwAddress, (LPVOID)lpBuf, wCount);
}

DWORD CToolKit::SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd)
{
	BYTE btBuf[5];
	// ---
	DWORD dwShift = (ULONG_PTR)dwMyFuncOffset - ((ULONG_PTR)dwJmpOffset + 5);
	// ---
	btBuf[0] = cmd;
	// ---
	memcpy((LPVOID)&btBuf[1], (LPVOID)&dwShift, sizeof(ULONG_PTR));
	// ---
	return WriteMemory(dwJmpOffset, (LPVOID)btBuf, sizeof(btBuf));
}

DWORD CToolKit::SetByte(const LPVOID dwOffset, const BYTE btValue)
{
	return WriteMemory(dwOffset, (LPVOID)&btValue, sizeof(BYTE));
}

DWORD CToolKit::SetFloat(const LPVOID dwOffset, float fValue)
{
	return WriteMemory(dwOffset, &fValue, sizeof(float));
}

DWORD CToolKit::SetDouble(const LPVOID dwOffset, double dValue)
{
	return WriteMemory(dwOffset, &dValue, sizeof(double));
}

DWORD CToolKit::SetDword(const LPVOID dwOffset, const DWORD dwValue)
{
	return WriteMemory(dwOffset, (LPVOID) & dwValue, sizeof(DWORD));
}

void CToolKit::SetCompleteHook(BYTE head,DWORD offset,...) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,5,PAGE_EXECUTE_READWRITE,&OldProtect);

	if(head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset+1;

	*(DWORD*)(offset+1) = (*function)-(offset+5);

	VirtualProtect((void*)offset,5,OldProtect,&OldProtect);
}

int CToolKit::Registry(const char* Section)
{
	HKEY Key;
	// ---
	int Value = 0;
	// ---
	DWORD Size = sizeof(int);
	// ---
	if (RegOpenKey(HKEY_CURRENT_USER, "Software\\Webzen\\MU\\Config", &Key) == 0)
	{
		if (RegQueryValueEx(Key, Section, nullptr, nullptr, (LPBYTE)(&Value), &Size) == 0)
		{	
			return Value;
		}
		// ---
		RegCloseKey(Key);
	}
	// ---
	return 0;
}

//----------------------------------
// - ID = 0 Amarelo
// - ID = 1 Verde


void CToolKit::SendMsg(int ColorId, char * szMsg)
{
	_asm
	{    
        MOV EDI, 00548AB0H
		// ---
        PUSH ColorId
        PUSH szMsg
		// ---
        CALL EDI
		// ---
		ADD ESP, 0x8
	}
}

void Protect(DWORD dwSrcOffset, int Size, DWORD dwNewProtect)
{
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)dwSrcOffset, Size, dwNewProtect, &OldProtect);
};

DWORD UnProtect(DWORD dwSrcOffset, int Size)
{
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)dwSrcOffset, Size, PAGE_EXECUTE_READWRITE, &OldProtect);
	return OldProtect;
};

void CToolKit::SetByteP(DWORD dwSrcOffset, BYTE bOpCode)
{
	__try
	{
		DWORD dwProtect = UnProtect(dwSrcOffset, 1);
		*(BYTE*)(dwSrcOffset) = bOpCode;
		Protect(dwSrcOffset, 1, dwProtect);
	}
	__finally {}
}

void CToolKit::WriteJmp(DWORD dwSrcOffset, DWORD dwDstOffset)
{
if (dwSrcOffset)
{
	__try
	{
		DWORD dwOffset = UnProtect(dwSrcOffset, 10);
		SetByteP(dwSrcOffset, 0xE9);
		HookThis(dwDstOffset, dwSrcOffset);
		Protect(dwSrcOffset, 10, dwOffset);
	}
	__finally {}
}
};