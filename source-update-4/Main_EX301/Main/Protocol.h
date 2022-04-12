#pragma once
struct PWMSG_HEAD2
{
	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
};
struct PMSG_HEALTHBAR
{
	PWMSG_HEAD2 h;
	BYTE Code;
	BYTE Count;
};
struct PMSG_HEALTHBAR_INFO
{
	short Index;
	BYTE Rate;
};

#pragma once
//079B9D40
#define STRUCT_DECRYPT			((void(__thiscall*)(void*,void*))0x0040B3C0)((void*)0x07AFEA08,*(void**)0X074D2C5C);
#define STRUCT_ENCRYPT			((void(__thiscall*)(void*,void*))0x0040B460)((void*)0x07AFEA08,*(void**)0X074D2C5C);

#define pMainSpeedFrameOne				(float*)(0x00758284) //0x00758284
#define pMainSpeedFrameTwo				(float*)(0x00758124) //0x00758124
#define	MAIN_WINDOW				0x07AFEE84
#define	MAIN_CONNECTION_STATUS	0x07B06BD0
#define	MAIN_SCREEN_STATE		0x0077EBAC
#define	MAIN_CHARACTER_STRUCT	0x074D2C58
#define	MAIN_VIEWPORT_STRUCT	0x074D2B2C
#define	MAIN_PACKET_SERIAL		0x07B06BCB
#define	MAIN_FONT_SIZE			0x07513340
#define	MAIN_RESOLUTION			0x07AFEC78
#define	MAIN_RESOLUTION_X		0x0077E350
#define	MAIN_RESOLUTION_Y		0x0077E354
#define	MAIN_PARTY_MEMBER_COUNT	0x07672E50
#define	MAIN_CURRENT_MAP		0x0077038C
#define	MAIN_HOOK_RECV			0x007565D4
#define	MAIN_HOOK_SEND			0x007565E4
#define MAIN_ACTIVE_SOCKET		0x07B02978

#define ProtocolCore ((BOOL(*)(DWORD,BYTE*,DWORD,DWORD))0x0069C3C0) // 1.04j 0069C3C0  ok
#define DrawInterface ((void(*)(DWORD,float,float,float,float))0x6438B4) // 1.04j  006A7FB0
#define DrawInterfaceText ((void(*)(char*,int,int,int,int,int,int))0x666347) //1.04j

//new line
#define pGetTextLine			((char*(__thiscall*)(LPVOID This, int LineNumber)) 0x402260) //1.04j
#define pMapName				((char*(__cdecl*)(signed int mapNumber)) 0x5F8F60) //1.04j
#define pTextLineThis			((LPVOID(*)()) 0x750DF88) //1.04j
#define pSetItemTextLine		((void(__cdecl*)(int Line, LPSTR Text, ...)) 0x739528) //1.04j
#define oItemText_Color			0x7641DD4 //1.04j
#define oItemText_Weight		0x7670800 //1.04j
#define oItemText_Line			0x7672F38 //1.04j
#define oItemText_Index			0x7640C48 //1.04j


#define SET_NUMBERHB(x) ((BYTE)((DWORD)(x)>>(DWORD)8))
#define SET_NUMBERLB(x) ((BYTE)((DWORD)(x)&0xFF))
#define SET_NUMBERHW(x) ((WORD)((DWORD)(x)>>(DWORD)16))
#define SET_NUMBERLW(x) ((WORD)((DWORD)(x)&0xFFFF))
#define SET_NUMBERHDW(x) ((DWORD)((QWORD)(x)>>(QWORD)32))
#define SET_NUMBERLDW(x) ((DWORD)((QWORD)(x)&0xFFFFFFFF))

#define MAKE_NUMBERW(x,y) ((WORD)(((BYTE)((y)&0xFF))|((BYTE)((x)&0xFF)<<8)))
#define MAKE_NUMBERDW(x,y) ((DWORD)(((WORD)((y)&0xFFFF))|((WORD)((x)&0xFFFF)<<16)))
#define MAKE_NUMBERQW(x,y) ((QWORD)(((DWORD)((y)&0xFFFFFFFF))|((DWORD)((x)&0xFFFFFFFF)<<32)))

//**********************************************//
//************ Packet Base *********************//
//**********************************************//

struct PBMSG_HEAD
{
	void set(BYTE head,BYTE size) // OK
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
	}

	void setE(BYTE head,BYTE size) // OK
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
	}

	BYTE type;
	BYTE size;
	BYTE head;
};

struct PSBMSG_HEAD
{
	void set(BYTE head,BYTE subh,BYTE size) // OK
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head,BYTE subh,BYTE size) // OK
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size;
	BYTE head;
	BYTE subh;
};

struct PWMSG_HEAD
{
	void set(BYTE head,WORD size) // OK
	{
		this->type = 0xC2;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
	}

	void setE(BYTE head,WORD size) // OK
	{
		this->type = 0xC4;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
	}

	BYTE type;
	BYTE size[2];
	BYTE head;
};

struct PSWMSG_HEAD
{
	void set(BYTE head,BYTE subh,WORD size) // OK
	{
		this->type = 0xC2;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head,BYTE subh,WORD size) // OK
	{
		this->type = 0xC4;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size[2];
	BYTE head;
	BYTE subh;
};

//**********************************************//
//************ GameServer -> Client ************//
//**********************************************//

struct PMSG_DAMAGE_RECV
{
	PBMSG_HEAD header;
	BYTE index[2];
	BYTE damage[2];
	BYTE type;
	BYTE ShieldDamage[2];
//Extra
	DWORD ViewCurHP;
	DWORD ViewCurSD;
	DWORD ViewDamageHP;
	DWORD ViewDamageSD;
};

struct PMSG_VIEWPORT_DESTROY_RECV
{
	PBMSG_HEAD header; // C1:14
	BYTE count;
};

struct PMSG_VIEWPORT_DESTROY
{
	BYTE index[2];
};

struct PMSG_MONSTER_DIE_RECV
{
	PBMSG_HEAD header; // C1:16
	BYTE index[2];
	BYTE experience[2];
	BYTE damage[2];
	//EXTRA
	DWORD ViewDamageHP;
};

struct PMSG_USER_DIE_RECV
{
	PBMSG_HEAD header; // C1:17
	BYTE index[2];
	BYTE skill[2];
	BYTE killer[2];
};

struct PMSG_LIFE_RECV
{
	PBMSG_HEAD header; // C1:26
	BYTE type;
	BYTE life[2];
	BYTE flag;
	BYTE shield[2];
	//EXTRA
	DWORD ViewHP;
	DWORD ViewSD;
};

struct PMSG_MANA_RECV
{
	PBMSG_HEAD header; // C1:27
	BYTE type;
	BYTE mana[2];
	BYTE bp[2];
	//EXTRA
	DWORD ViewMP;
	DWORD ViewBP;
};

struct PMSG_FRUIT_RESULT_RECV
{
	PBMSG_HEAD header; // C1:2C
	BYTE result;
	WORD value;
	BYTE type;
	//EXTRA
	DWORD ViewValue;
	DWORD ViewPoint;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};

struct PMSG_REWARD_EXPERIENCE_RECV
{
	PBMSG_HEAD header; // C1:9C
	BYTE index[2];
	WORD experience[2];
	BYTE damage[2];
	//EXTRA
	DWORD ViewDamageHP;
};

struct PMSG_QUEST_REWARD_RECV
{
	PBMSG_HEAD header; // C1:A3
	BYTE index[2];
	BYTE QuestReward;
	BYTE QuestAmount;
	//EXTRA
	DWORD ViewPoint;
};

struct PMSG_MAP_SERVER_MOVE_RECV
{
	PSBMSG_HEAD header; // C1:B1:00
	char IpAddress[16];
	WORD ServerPort;
	WORD ServerCode;
	DWORD AuthCode1;
	DWORD AuthCode2;
	DWORD AuthCode3;
	DWORD AuthCode4;
};

struct PMSG_MAP_SERVER_MOVE_AUTH_RECV
{
	PSBMSG_HEAD header; // C1:B1:01
	BYTE result;
};

struct PMSG_CONNECT_CLIENT_RECV
{
	PSBMSG_HEAD header; // C1:F1:00
	BYTE result;
	BYTE index[2];
	BYTE ClientVersion[5];
};

struct PMSG_CONNECT_ACCOUNT_RECV
{
	PSBMSG_HEAD header; // C1:F1:01
	BYTE result;
};

struct PMSG_CLOSE_CLIENT_RECV
{
	PSBMSG_HEAD header; // C1:F1:02
	BYTE result;
};

struct PMSG_CHARACTER_LIST_RECV
{
	PSBMSG_HEAD header; // C1:F3:00
	BYTE ClassCode;
	BYTE MoveCnt;
	BYTE count;
};

struct PMSG_CHARACTER_INFO_RECV
{
	PSBMSG_HEAD header; // C3:F3:03
	BYTE X;
	BYTE Y;
	BYTE Map;
	BYTE Dir;
	DWORD Experience;
	DWORD NextExperience;
	WORD LevelUpPoint;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	WORD Shield;
	WORD MaxShield;
	WORD BP;
	WORD MaxBP;
	DWORD Money;
	BYTE PKLevel;
	BYTE CtlCode;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD Leadership;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
#if(GAMESERVER_EXTRA==0)
	DWORD ViewReset;
	DWORD ViewMasterReset;
	DWORD ViewPoint;
	DWORD ViewCurHP;
	DWORD ViewMaxHP;
	DWORD ViewCurMP;
	DWORD ViewMaxMP;
	DWORD ViewCurBP;
	DWORD ViewMaxBP;
	DWORD ViewCurSD;
	DWORD ViewMaxSD;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
	DWORD ViewExperience;
	DWORD ViewNextExperience;
#endif
};

struct PMSG_CHARACTER_REGEN_RECV
{
	PSBMSG_HEAD header; // C3:F3:04
	BYTE X;
	BYTE Y;
	BYTE Map;
	BYTE Dir;
	WORD Life;
	WORD Mana;
	WORD Shield;
	WORD BP;
	DWORD Experience;
	DWORD Money;
	DWORD ViewCurHP;
	DWORD ViewCurMP;
	DWORD ViewCurBP;
	DWORD ViewCurSD;
};

struct PMSG_LEVEL_UP_RECV
{
	PSBMSG_HEAD header; // C1:F3:05
	WORD Level;
	WORD LevelUpPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
	WORD MaxBP;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	//EXTRA
	DWORD ViewPoint;
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
	DWORD ViewExperience;
	DWORD ViewNextExperience;
};

struct PMSG_LEVEL_UP_POINT_RECV
{
	PSBMSG_HEAD header; // C1:F3:06
	BYTE result;
	WORD MaxLifeAndMana;
	WORD MaxShield;
	WORD MaxBP;
	//EXTRA
	DWORD ViewPoint;
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};

struct PMSG_MONSTER_DAMAGE_RECV
{
	PSBMSG_HEAD header;
	BYTE damage[2];
	BYTE ShieldDamage[2];
//Extra
	DWORD ViewCurHP;
	DWORD ViewCurSD;
	DWORD ViewDamageHP;
	DWORD ViewDamageSD;
};

struct PMSG_MASTER_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F3:50
	WORD MasterLevel;
	BYTE Experience[8];
	BYTE NextExperience[8];
	WORD MasterPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
	WORD MaxBP;
	//EXTRA
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
};

struct PMSG_MASTER_LEVEL_UP_RECV
{
	PSBMSG_HEAD header; // C1:F3:51
	WORD MasterLevel;
	WORD MinMasterLevel;
	WORD MasterPoint;
	WORD MaxMasterLevel;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
	WORD MaxBP;
	//EXTRA
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
	QWORD ViewMasterExperience;
	QWORD ViewMasterNextExperience;
};

struct PMSG_NEW_CHARACTER_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F3:E0
	WORD Level;
	WORD LevelUpPoint;
	DWORD Experience;
	DWORD NextExperience;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Leadership;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	WORD BP;
	WORD MaxBP;
	WORD Shield;
	WORD MaxShield;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	//EXTRA
	DWORD ViewReset;
	DWORD ViewMasterReset;
	DWORD ViewPoint;
	DWORD ViewCurHP;
	DWORD ViewMaxHP;
	DWORD ViewCurMP;
	DWORD ViewMaxMP;
	DWORD ViewCurBP;
	DWORD ViewMaxBP;
	DWORD ViewCurSD;
	DWORD ViewMaxSD;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};


struct PMSG_NEW_CHARACTER_CALC_RECV
{
	PSBMSG_HEAD header; // C1:F3:E1
	DWORD ViewCurHP;
	DWORD ViewMaxHP;
	DWORD ViewCurMP;
	DWORD ViewMaxMP;
	DWORD ViewCurBP;
	DWORD ViewMaxBP;
	DWORD ViewCurSD;
	DWORD ViewMaxSD;
	DWORD ViewAddStrength;
	DWORD ViewAddDexterity;
	DWORD ViewAddVitality;
	DWORD ViewAddEnergy;
	DWORD ViewAddLeadership;
	DWORD ViewPhysiDamageMin;
	DWORD ViewPhysiDamageMax;
	DWORD ViewMagicDamageMin;
	DWORD ViewMagicDamageMax;
	DWORD ViewCurseDamageMin;
	DWORD ViewCurseDamageMax;
	DWORD ViewMulPhysiDamage;
	DWORD ViewDivPhysiDamage;
	DWORD ViewMulMagicDamage;
	DWORD ViewDivMagicDamage;
	DWORD ViewMulCurseDamage;
	DWORD ViewDivCurseDamage;
	DWORD ViewMagicDamageRate;
	DWORD ViewCurseDamageRate;
	DWORD ViewPhysiSpeed;
	DWORD ViewMagicSpeed;
	DWORD ViewAttackSuccessRate;
	DWORD ViewAttackSuccessRatePvP;
	DWORD ViewDefense;
	DWORD ViewDefenseSuccessRate;
	DWORD ViewDefenseSuccessRatePvP;
	DWORD ViewDamageMultiplier;
	DWORD ViewRFDamageMultiplierA;
	DWORD ViewRFDamageMultiplierB;
	DWORD ViewRFDamageMultiplierC;
	DWORD ViewDarkSpiritAttackDamageMin;
	DWORD ViewDarkSpiritAttackDamageMax;
	DWORD ViewDarkSpiritAttackSpeed;
	DWORD ViewDarkSpiritAttackSuccessRate;
};

#define SET_NUMBERH(x) ( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x) ( (BYTE)((DWORD)(x) & 0xFF) )
struct PWMSG_HEAD22	// Packet - Word Type
{
public:

	void set(LPBYTE lpBuf, BYTE head, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};

	void setE(LPBYTE lpBuf, BYTE head, int size)	// line : 49
	{
		lpBuf[0] = 0xC4;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};

	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
};
struct PMSG_NEW_HEALTH_BAR_RECV
{
	PSWMSG_HEAD header;
	BYTE Count;
};

struct PMSG_NEW_HEALTH_RECV
{
	WORD index;
	BYTE type;
	BYTE rate;
};

struct PMSG_NEW_GENS_BATTLE_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F3:E3
	BYTE GensBattleMapCount;
	BYTE GensMoveIndexCount;
	BYTE GensBattleMap[120];
	BYTE GensMoveIndex[120];
};

struct PMSG_NEW_MESSAGE_RECV
{
	PSBMSG_HEAD header; // C1:F3:E4
	char message[128];
};

//**********************************************//
//************ Client -> GameServer ************//
//**********************************************//

struct PMSG_CONNECT_ACCOUNT_SEND
{
	#pragma pack(1)
	PSBMSG_HEAD header; // C3:F1:01
	char account[10];
	char password[10];
	DWORD TickCount;
	BYTE ClientVersion[5];
	BYTE ClientSerial[16];
	#pragma pack()
};

struct PMSG_CHARACTER_LIST_SEND
{
	PSBMSG_HEAD header; // C1:F3:00
};

struct PMSG_CHARACTER_INFO_SEND
{
	PSBMSG_HEAD header; // C1:F3:03
	char name[10];
};

//**********************************************//
//**********************************************//
//**********************************************//

BOOL ProtocolCoreEx(BYTE head,BYTE* lpMsg,int size,int key);
void GCDamageRecv(PMSG_DAMAGE_RECV* lpMsg);
void GCMonsterDieRecv(PMSG_MONSTER_DIE_RECV* lpMsg);
void GCUserDieRecv(PMSG_USER_DIE_RECV* lpMsg);
void GCLifeRecv(PMSG_LIFE_RECV* lpMsg);
void GCManaRecv(PMSG_MANA_RECV* lpMsg);
void GCFruitResultRecv(PMSG_FRUIT_RESULT_RECV* lpMsg);
void GCRewardExperienceRecv(PMSG_REWARD_EXPERIENCE_RECV* lpMsg);
void GCQuestRewardRecv(PMSG_QUEST_REWARD_RECV* lpMsg);
void GCMapServerMoveRecv(PMSG_MAP_SERVER_MOVE_RECV* lpMsg);
void GCMapServerMoveAuthRecv(PMSG_MAP_SERVER_MOVE_AUTH_RECV* lpMsg);
void GCConnectClientRecv(PMSG_CONNECT_CLIENT_RECV* lpMsg);
void GCConnectAccountRecv(PMSG_CONNECT_ACCOUNT_RECV* lpMsg);
void GCCloseClientRecv(PMSG_CLOSE_CLIENT_RECV* lpMsg);
void GCCharacterListRecv(PMSG_CHARACTER_LIST_RECV* lpMsg);
void GCCharacterInfoRecv(PMSG_CHARACTER_INFO_RECV* lpMsg);
void GCCharacterRegenRecv(PMSG_CHARACTER_REGEN_RECV* lpMsg);
void GCLevelUpRecv(PMSG_LEVEL_UP_RECV* lpMsg);
void GCLevelUpPointRecv(PMSG_LEVEL_UP_POINT_RECV* lpMsg);
void GCMonsterDamageRecv(PMSG_MONSTER_DAMAGE_RECV* lpMsg);
void GCMasterInfoRecv(PMSG_MASTER_INFO_RECV* lpMsg);
void GCMasterLevelUpRecv(PMSG_MASTER_LEVEL_UP_RECV* lpMsg);
void GCNewCharacterInfoRecv(PMSG_NEW_CHARACTER_INFO_RECV* lpMsg);
void GCNewCharacterCalcRecv(PMSG_NEW_CHARACTER_CALC_RECV* lpMsg);
void GCNewHealthBarRecv(PMSG_NEW_HEALTH_BAR_RECV* lpMsg);
void GCNewGensBattleInfoRecv(PMSG_NEW_GENS_BATTLE_INFO_RECV* lpMsg);
void GCNewMessageRecv(PMSG_NEW_MESSAGE_RECV* lpMsg);
void DataSend(BYTE* lpMsg,DWORD size);
