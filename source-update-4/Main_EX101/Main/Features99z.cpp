#include "stdafx.h"

void WebzenLogo99z(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	// - Função Original
	RenderBitmap(a1, a2-a2, a3-a3, a4+20000, a5+20000, a6, a7, a8, a9, a10, a11, a12); //webzenlogo original redimensionado
	
	// - Função Modificada
	char path[200];
	sprintf_s(path, "Local\\webzenlogo.jpg");
	pLoadTexture(path, 151, 9728, 10496, 0, 1);
	RenderBitmap(151, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12); //webzenlogo recriado
}

void LoadWebzenLogo()
{
	MemorySet(0x0060EFBE,0x90,0x5);
	SetCompleteHook(0xE8,0x0060F066,&WebzenLogo99z);
}