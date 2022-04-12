#pragma once

#define CONFIG_FOG_FILE ".\\Data\\Custom\\FogEffect.txt"

struct RGBAStruct
{
	float r,g,b,a;
};  

RGBAStruct FogMapColor(int Map);

class cFog
{
	public:
		cFog();
		virtual ~cFog();
		BOOL EventMaps();

		static void FogAttach();
		static void FogDettach();

		struct sColor
		{
			int MapId;

			float R;
			float G;
			float B;
			float A;
		};

		sColor eColor[256];
};

extern cFog gFog;