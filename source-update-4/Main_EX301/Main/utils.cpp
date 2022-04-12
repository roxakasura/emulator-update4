#include "stdafx.h"
#include "utils.h"

UtilsEx::UtilsEx() {};

UtilsEx::~UtilsEx() {};

UtilsEx Utils;

void UtilsEx::Protect(DWORD dwSrcOffset, int Size, DWORD dwNewProtect)
{
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)dwSrcOffset, Size, dwNewProtect, &OldProtect);
};

DWORD UtilsEx::UnProtect(DWORD dwSrcOffset, int Size)
{
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)dwSrcOffset, Size, PAGE_EXECUTE_READWRITE, &OldProtect);
	return OldProtect;
};

void UtilsEx::SetNop(DWORD dwSrcOffset, int Size)
{
	for (int i = 0; i < Size; i++) 
		*(BYTE*)(dwSrcOffset + i) = 0x90;
};

void UtilsEx::SetByte(DWORD dwSrcOffset, BYTE bOpCode)
{
	__try 
	{
		DWORD dwProtect = this->UnProtect(dwSrcOffset, 1);
		*(BYTE*)(dwSrcOffset) = bOpCode;
		this->Protect(dwSrcOffset, 1, dwProtect);
	}
	__finally {}
}

void UtilsEx::WriteJmp(DWORD dwSrcOffset, DWORD dwDstOffset)
{
	if (dwSrcOffset)
	{
		__try
		{
			DWORD dwOffset = UnProtect(dwSrcOffset, 10);
			SetByte(dwSrcOffset, 0xE9);
			HookThis(dwDstOffset, dwSrcOffset);
			Protect(dwSrcOffset, 10, dwOffset);
		}
		__finally {}
	}
};

void UtilsEx::HookThis(DWORD dwDstOffset, DWORD dwSrcOffset) 
{
	*(DWORD*)(dwSrcOffset + 1) = dwDstOffset - (dwSrcOffset + 5);
};

void UtilsEx::HookExactOffset(DWORD my, DWORD tohook, BYTE type)
{
	*(BYTE*)tohook = type;
	*(DWORD*)(tohook+1) = my;
};

void UtilsEx::HookOffset(DWORD my, DWORD tohook, BYTE type)
{
	*(BYTE*)tohook = type;
	*(DWORD*)(tohook+1) = my - (tohook+5);
};

void UtilsEx::SetCompleteHook(BYTE head,DWORD offset,...) // OK
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

void UtilsEx::SetDword(DWORD offset,DWORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(DWORD*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}