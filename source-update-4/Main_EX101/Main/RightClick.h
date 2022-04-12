#pragma once
#define CheckWindows			((bool(__stdcall*)(int Code)) 0x648BB0) 

void ItemPosicion(DWORD a1, DWORD a2, int a3, int Columna, int Fila);
void RightClickLoad();
bool __stdcall CheckClick(int a1);