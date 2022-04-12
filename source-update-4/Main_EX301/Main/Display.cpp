#include "StdAfx.h"
#include "Display.h"


int g_nMaxAnisotropy_ = 1;
int *MAIN_STATE_ADDR_  = (int*)0x0077EBAC;

typedef void (APIENTRY *FUNC_GLENABLE) (GLenum mode);
FUNC_GLENABLE glEnable_o = NULL;

cDisplay gDisplay;

cDisplay::cDisplay()
{
	
}

cDisplay::~cDisplay()
{
	
}

void APIENTRY glEnable_h(GLenum mode)
{

	if(*MAIN_STATE_ADDR_ == 5)
	{
		glGetIntegerv(0x84FF,&g_nMaxAnisotropy_);
		glTexParameteri(GL_TEXTURE_2D,0x84FE,g_nMaxAnisotropy_-0.1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glEnable_o(mode);



}


void cDisplay::Load()
{
	glEnable_o = (FUNC_GLENABLE)DetourAttach((PVOID *)DetourFindFunction("OpenGL32.dll","glBegin"),(PBYTE)glEnable_h);
}
