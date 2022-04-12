#pragma once

#include "stdafx.h"

struct VIEWPORT_STRUCT
{
	#pragma pack(1)
	char state;
	short index;
	BYTE type;
	#pragma pack()
};
// ---
#pragma pack(push, 1)
struct	ObjectItem
{
	/*+0*/		short 	ItemID;
	/*+2*/		int		Level;
	/*+6*/		BYTE	Unknown6;
	/*+7*/		BYTE	Unknown7;
	/*+8*/		BYTE	Unknown8;
	/*+9*/		short	DamageMin;
	/*+11*/		short	DamageMax;
	/*+13*/		BYTE	Unknown13;
	/*+14*/		short	Unknown14;
	/*+16*/		short	Unknown16;
	/*+18*/		BYTE	Unknown18;
	/*+19*/		BYTE	Unknown19;
	/*+20*/		short	Unknown20;
	/*+22*/		BYTE	Durability;
	/*+23*/		BYTE	ExcellentOption;
	/*+24*/		BYTE	AncientOption;
	/*+25*/		short	ReqStrenght;
	/*+27*/		short	ReqDextirity;
	/*+29*/		short	ReqEnergy;
	/*+31*/		short	ReqVitality;
	/*+33*/		short	ReqCommand;
	/*+35*/		short	ReqLevel;
	/*+37*/		char    SpecialCount;
	/*+38*/		BYTE	SpecialType[8];
	/*+54*/		BYTE	SpecialValue[8];
	/*+62*/		int		UniqueID;
	/*+66*/		char	Unknown66;
	/*+67*/		char 	PosX;
	/*+68*/		char 	PosY;
	/*+69*/		WORD 	HarmonyType;
	/*+71*/		short	HarmonyValue;
	/*+73*/		char 	Is380Item;
};
// ---
#pragma pack(pop)
// ---
struct OBJECTSTRUCT_PLAYER
{
	char Name[11];
	char Class;
	BYTE Unknown12;
	BYTE Unknown13;
	__int16 Level;
	DWORD Experience;
	DWORD NextExperience;
	__int16 Strength;
	__int16 Dexterity;
	__int16 Vitality;
	__int16 Energy;
	__int16 Leadership;
	WORD Life;
	WORD Mana;
	WORD MaxLife;
	WORD MaxMana;
	__int16 AddStrength;
	__int16 AddDexterity;
	__int16 AddVitality;
	__int16 AddEnergy;
	WORD AddLeadership;
	WORD Unknown94;
	WORD Unknown96;
	WORD Stamina;
	WORD MaxStamina;
	BYTE ItemSpecialUseFlag;
	BYTE UnknownGap;
	WORD ItemSpecialUseTime[3];
	WORD AddPoint;
	WORD MaxAddPoint;
	WORD AttackSpeed;
	WORD DamageRate;
	WORD AttackRate;
	WORD DamageMin;
	WORD DamageMax;
	WORD Unknown92;
	WORD MagicSpeed;
	WORD Unknown110;
	WORD LevelPoint;
	BYTE MagicCount;
	WORD DefenseRate;
	WORD Defense;
	WORD pMagicList[150];
	VIEWPORT_STRUCT* VpPlayer;
};
// ---
#pragma pack(pop)
// ---
class CUser
{
public:
	void Load();
	static void GetStruct();
	static void gObjFix();
	// ---
	DWORD dwGetStructJmp;
	// ---
	DWORD gTmpEax;
	DWORD gTmpEcx;
	DWORD gTmpEdx;
	DWORD gTmpEbx;
	DWORD gTmpEsp;
	DWORD gTmpEbp; 
	DWORD gTmpEsi;
	DWORD gTmpEdi;
	// ---
	DWORD dwStructAddr;
	// ---
	OBJECTSTRUCT_PLAYER m_Player;
	ObjectItem m_ItemStat;
};
// ---
extern CUser gUser;
// ---