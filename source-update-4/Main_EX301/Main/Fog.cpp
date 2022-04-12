#include "StdAfx.h"
#include "Fog.h"
#include <gl/gl.h>
#include <gl/glu.h>

#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"detours.lib")
#include "detours.h"

int IsFogEffect = GetPrivateProfileInt("Customs","UseCustomFogEffect",0,".\\Customs.ini");
int GLTEX_ENABLED = GetPrivateProfileIntA("Customs", "UseCustomFogSmoothing", 0, ".\\Customs.ini");

float *Camera_PosZ_    = (float*) 0x757994;

cFog gFog;

cFog::cFog()
{
	/**/
}

cFog::~cFog()
{
	/**/
}

int g_iMapId;

void APIENTRY glEnable_Hooked(GLenum);
typedef void (APIENTRY *ptr_glEnable)(GLenum);
ptr_glEnable glEnable_Real = (ptr_glEnable)&glEnable;


void APIENTRY glClearColor_Hooked(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void (APIENTRY *ptr_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ptr_glClearColor glClearColor_Real = (ptr_glClearColor)&glClearColor;


RGBAStruct FogMapColor(int Map)
{
	RGBAStruct rgb;

	

	switch (Map)
	{
	case 0x0: // Lorencia
		{
		rgb.r = 0.0f; rgb.g = 0.0f; rgb.b = 0.0f; rgb.a = 1.0f; return rgb;
			return rgb;
		} 
		break;

	case 0x1: // Dungeon
		{
			rgb.r = 0.83f; rgb.g = 0.7581f; rgb.b = 0.6142f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x2: // Devias
		{
			rgb.r = 0.6643f; rgb.g = 0.8158f; rgb.b = 1.91f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x3: // Noria
		{
			rgb.r = 0.3689f; rgb.g = 0.58f; rgb.b = 0.2552f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x4: // Losttower
		{
			rgb.r = 0.0f; rgb.g = 0.0f; rgb.b = 0.0f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x6: // Stadium
		{
			rgb.r = 0.0f; rgb.g = 0.0f; rgb.b = 0.0f; rgb.a = 1.0f; return rgb;
		}

	case 0x7: // Atlans
		{
			rgb.r = 0.451f; rgb.g = 0.6478f; rgb.b = 0.82f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x8: // Tarkan
		{
			rgb.r = 0.83f; rgb.g = 0.667f; rgb.b = 0.3154f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0xA: // Icarus
		{
			rgb.r = 0.077f; rgb.g = 0.1318f; rgb.b = 0.22f; rgb.a = 1.0f; return rgb;
		} 
		break; 

	case 0x19: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break; 

	case 0x1A: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break; 

	case 0x1B: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x1C: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x1D: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x1E: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x1F: // Valley of Loren
		{
			rgb.r = 0.39f; rgb.g = 0.3156f; rgb.b = 0.1872f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x20: // Land of Trial
		{
			rgb.r = 0.0f; rgb.g = 0.0f; rgb.b = 0.0f; rgb.a = 1.0f; return rgb;
		} 
		break; 

	case 0x21: // Aida
		{
			rgb.r = 0.3403f; rgb.g = 0.47f; rgb.b = 0.3008f; rgb.a = 1.0f; return rgb;
		} 
		break; 


	case 0x22: // CryWolf
		{
			rgb.r = 0.39f; rgb.g = 0.3156f; rgb.b = 0.1872f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x25: // Kanturu
		{
			rgb.r = 0.4f; rgb.g = 0.3364f; rgb.b = 0.188f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x26: // Kanturu
		{
			rgb.r = 0.18f; rgb.g = 0.1708f; rgb.b = 0.1494f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x2A: // Balgas Barrack
		{
			rgb.r = 0.47f; rgb.g = 0.1363f; rgb.b = 0.1363f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x33: // Elbeland
		{
			rgb.r = 0.76f; rgb.g = 0.76f; rgb.b = 0.76f; rgb.a = 1.0f; return rgb;
		} 
		break;  

	case 0x39: // Raklion
		{
			rgb.r = 0.6643f; rgb.g = 0.8158f; rgb.b = 0.91f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x3E: // Santa town
		{
			rgb.r = 0.6643f; rgb.g = 0.8158f; rgb.b = 0.91f; rgb.a = 1.0f; return rgb;
		}

	default:
		{
			rgb.r = 0.0f; rgb.g = 0.0f; rgb.b = 0.0f; rgb.a = 1.0f; return rgb;
		} 
		break;
	}
}

BOOL cFog::EventMaps()
{
	if(pMapNumber == 10 || pMapNumber == 24 || pMapNumber == 25 || pMapNumber == 26 || pMapNumber == 27 || pMapNumber == 28 || pMapNumber == 29 || pMapNumber == 36)
	{
		return FALSE;
	}
	// ----
	return TRUE;
}



void APIENTRY glEnable_Hooked(GLenum cap)
{		

	RGBAStruct rgb = FogMapColor(pMapNumber); 

	GLfloat rgba[4] = { rgb.r, rgb.g, rgb.b, rgb.a };
	
	if(pPlayerState == SelectServer)
	{
		glDisable(GL_FOG);
	}

	if(pPlayerState == SwitchCharacter)
	{
		glDisable(GL_FOG);
	}
	
	if(pPlayerState == GameProcess && gFog.EventMaps() == TRUE)
	{
		if((cap == GL_BLEND) || (cap == GL_TEXTURE_2D) || (cap == GL_DEPTH_TEST))  
		{
			glDisable(GL_FOG);  
		}

			if (GLTEX_ENABLED == 1)
			{
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}

		glEnable_Real(GL_FOG);


		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_DENSITY,0.025f);
		glFogfv(GL_FOG_COLOR,rgba); // 
		glFogf(GL_FOG_START, 1800.0f); //1800
		glFogf(GL_FOG_END, 2200.0f); //2200
		glHint(GL_FOG_HINT,GL_NICEST);

		if((cap == GL_BLEND) || (cap == GL_TEXTURE_2D) || (cap == GL_DEPTH_TEST))   
		{
			glDisable(GL_FOG);  
		}
	}
	
	glEnable_Real(cap);
	
} 

void APIENTRY glClearColor_Hooked(GLclampf red,GLclampf green,GLclampf blue,GLclampf alpha)
{
	RGBAStruct Color = FogMapColor(pMapNumber); 

	if(pPlayerState == SelectServer)
	{
		glClearColor_Real(0.0f,0.0f,0.0f,0.0f);   
	}

	if(pPlayerState == SwitchCharacter)
	{
		glClearColor_Real(0.0f,0.0f,0.0f,0.0f);  
	}
	
	if(pPlayerState == GameProcess && gFog.EventMaps() == FALSE)
	{ 
		glClearColor_Real(0.0f,0.0f,0.0f,0.0f); 
	}

	if(pPlayerState == GameProcess && gFog.EventMaps() == TRUE)
	{ 
		glClearColor_Real(Color.r,Color.g,Color.b,Color.a);
	}

	
}

void cFog::FogAttach()
{
	FILE *File;
	File = fopen(CONFIG_FOG_FILE,"r");

	if(File != NULL)
	{
		int Flag = 0;
		char zBuffer[1024];

		g_iMapId = 0;
		memset(gFog.eColor,0,sizeof(gFog.eColor));

		while(!feof(File))
		{
			fgets(zBuffer,sizeof(zBuffer),File);

			if(Flag == 0)
			{
				sscanf_s(zBuffer,"%d %f %f %f %f",&gFog.eColor[g_iMapId].MapId,&gFog.eColor[g_iMapId].R,&gFog.eColor[g_iMapId].G,&gFog.eColor[g_iMapId].B,&gFog.eColor[g_iMapId].A);

				g_iMapId++;
			}
		}

		fclose(File);

		if(IsFogEffect == 1 )
			{

				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());
				DetourAttach(&(PVOID&)glEnable_Real,glEnable_Hooked);

				DetourTransactionCommit();
			}


	}
	else
	{

	}
}

void cFog::FogDettach()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)glEnable_Real, glEnable_Hooked); 

	DetourTransactionCommit();
}