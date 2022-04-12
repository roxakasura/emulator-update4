#pragma once

#define MAX_CUSTOM_POSITION 1000
#define ItemPosition	 ((int(*)(float PosResuX, float PosResuY, float Izquierda, float Arriba, int IDItems, int Level, int a7, int a8, int Tamanho))0x005E8790)

struct CUSTOM_POSITION_INFO
{
	int Index;
	int ItemIndex;
	float X;
	float Y;
	int Size;
};

class CCustomItemPosition
{
public:
	CCustomItemPosition();
	virtual ~CCustomItemPosition();
	void Load(CUSTOM_POSITION_INFO* info);
	void SetInfo(CUSTOM_POSITION_INFO info);
	CUSTOM_POSITION_INFO* GetInfo(int index);
	CUSTOM_POSITION_INFO* GetInfoByItem(int ItemIndex);
	short CheckItemPositionByItem(int ItemIndex);
	void PositionItemLoad();
public:
	CUSTOM_POSITION_INFO m_Info[MAX_CUSTOM_POSITION];
};
extern CCustomItemPosition gCustomItemPosition;