#include "StdAfx.h"


void RightClickLoad()
{
	SetCompleteHook(0xE8,0x005B79B4,&ItemPosicion);
	MemorySet(0x005B7A0F, 0x90, 2); //Move item Interface -> Inventario OK
	MemorySet(0x005B7996, 0x90, 2); //Move item Interface -> Inventario OK
}

void ItemPosicion(DWORD a1, DWORD a2, int a3, int Columna, int Fila)
{
	if (CheckWindows(0x20))
	{
		a1 = 0x113;
		a2 = 0x10F;
		a3 = 0x7889FD8;
		Fila = 4;
		Columna = 8;
	}

	if (CheckWindows(0x100))
	{
		a1 = 0x113;
		a2 = 0x6E;
		a3 = 0x7D0E088;
		Fila = 4;
		Columna = 8;
	}

	((void(*)(DWORD a1, DWORD a2, int a3, int Fila, int a5))0x005B8890)(a1, a2, a3, Columna, Fila);//6321A0 1.2s
}
