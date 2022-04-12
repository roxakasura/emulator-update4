#pragma once

struct sSmoke
{
	WORD			    _Index;
	float			    _ColorR;
	float			    _ColorG;
	float			    _ColorB;
};

class cSmoke
{
public:
	bool Load();
	int Get(DWORD Type);
	static void Effect();

private:
	WORD			    _Index;
	int                 _Item;
	int			        _Count;
	float               _ColorR;
	float               _ColorG;
	float               _ColorB;

private:
	sSmoke			    SmokeStruct[255];
};

extern cSmoke Smoke;