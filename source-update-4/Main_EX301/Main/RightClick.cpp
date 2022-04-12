#include "stdafx.h"
#include "RightClick.h"
#include "Util.h"
#include "TMemory.h"


bool ItemPosicion(DWORD a1, DWORD a2, int a3, int Columna, int Fila)
{
	if (pCheckWindow(6)) //Trade
	{
		return ((bool(*)(DWORD a1, DWORD a2, int a3, int Fila, int a5))0x5CBD50)(0x113, 0x10F, 0x07670878, Columna, 4);
	}
	else if (pCheckWindow(9) /* ChaosMix */|| pCheckWindow(21) /* SeniorMix */ || pCheckWindow(28) /* Refinery */)
	{
		return ((bool(*)(DWORD a1, DWORD a2, int a3, int Fila, int a5))0x5CBD50)(0x113, 0x6E, 0x07AF47D0, Columna, 4);
	}
	else if (pCheckWindow(7)) //Warehouse
	{
		return ((bool(*)(DWORD a1, DWORD a2, int a3, int Fila, int a5))0x5CBD50)(a1, a2, a3, Columna, Fila);
	}
	return 0;
}


void RightClick()
{
	MemorySet(0x005CA560, 0x90, 2); //Move item Interface -> Inventario OK

	MemorySet(0x005CA4E6, 0x90, 2); //Inventario -> Interface
	SetCompleteHook(0xE8, 0x005CA504, &ItemPosicion);
}