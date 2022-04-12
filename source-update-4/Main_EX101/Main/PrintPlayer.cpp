#include "stdafx.h"

DWORD ViewIndex = 0;
DWORD ViewReset = 0;
DWORD ViewValue = 0;
DWORD ViewPoint = 0;
DWORD ViewCurHP = 0;
DWORD ViewMaxHP = 0;
DWORD ViewCurMP = 0;
DWORD ViewMaxMP = 0;
DWORD ViewCurBP = 0;
DWORD ViewMaxBP = 0;
DWORD ViewCurSD = 0;
DWORD ViewMaxSD = 0;
DWORD ViewDamageHP = 0;
DWORD ViewDamageSD = 0;
DWORD ViewExperience = 0;
DWORD ViewNextExperience = 0;
QWORD ViewMasterExperience = 0;
QWORD ViewMasterNextExperience = 0;
DWORD ViewStrength = 0;
DWORD ViewDexterity = 0;
DWORD ViewVitality = 0;
DWORD ViewEnergy = 0;
DWORD ViewLeadership = 0;
DWORD ViewAddStrength = 0;
DWORD ViewAddDexterity = 0;
DWORD ViewAddVitality = 0;
DWORD ViewAddEnergy = 0;
DWORD ViewAddLeadership = 0;
DWORD ViewPhysiDamageMin = 0;
DWORD ViewPhysiDamageMax = 0;
DWORD ViewMagicDamageMin = 0;
DWORD ViewMagicDamageMax = 0;
DWORD ViewCurseDamageMin = 0;
DWORD ViewCurseDamageMax = 0;
DWORD ViewMulPhysiDamage = 0;
DWORD ViewDivPhysiDamage = 0;
DWORD ViewMulMagicDamage = 0;
DWORD ViewDivMagicDamage = 0;
DWORD ViewMulCurseDamage = 0;
DWORD ViewDivCurseDamage = 0;
DWORD ViewMagicDamageRate = 0;
DWORD ViewCurseDamageRate = 0;
DWORD ViewPhysiSpeed = 0;
DWORD ViewMagicSpeed = 0;
DWORD ViewAttackSuccessRate = 0;
DWORD ViewAttackSuccessRatePvP = 0;
DWORD ViewDefense = 0;
DWORD ViewDefenseSuccessRate = 0;
DWORD ViewDefenseSuccessRatePvP = 0;
DWORD ViewDamageMultiplier = 0;
DWORD ViewDarkSpiritAttackDamageMin = 0;
DWORD ViewDarkSpiritAttackDamageMax = 0;
DWORD ViewDarkSpiritAttackSpeed = 0;
DWORD ViewDarkSpiritAttackSuccessRate = 0;
DWORD ViewSkillMagicDamage = 0;
DWORD ViewSkillPhysiDamage = 0;

void InitPrintPlayer() // OK
{
	SetCompleteHook(0xE8, 0x0059A086, &PrintPlayerViewHP2); //ok interface
	SetCompleteHook(0xE8, 0x0059A0AD, &PrintPlayerViewMP2); //ok interface
	SetCompleteHook(0xE8, 0x00598978, &PrintPlayerViewBP2); //ok interface

	SetCompleteHook(0xE8, 0x0059936F, &PrintPlayerViewHP1); //ok ao passar cursor
	SetCompleteHook(0xE8, 0x00599434, &PrintPlayerViewMP1); //ok ao passar cursor
	SetCompleteHook(0xE8, 0x005989C0, &PrintPlayerViewBP1); //ok ao passar cursor
	
/*
	SetDword(0x0049F6ED,0xA0000001); // PrintTextReplace 64

	SetDword(0x004AB73A,0xA0000002); // PrintTextReplace 64

	SetDword(0x005B3AD4,0xA0000003); // PrintTextReplace 64

//	SetDword(0x005B4931,0xA0000004); // PrintTextReplace 64 bug de visualização de speed arma

	SetDword(0x0049F68B,0xA0000001); // PrintTextReplace 64

	SetDword(0x004AB6DE,0xA0000002); // PrintTextReplace 203

	SetCompleteHook(0xE9,0x00402267,&PrintPlayerViewText);*/

	SetCompleteHook(0xE8,0x004C4375,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C4C01,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C4D66,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C4DB6,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C4E3F,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C4E8F,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C4EAE,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C83F1,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C8D46,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C8D7B,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C9828,&PrintDamageOnScreenHP); //s1

	SetCompleteHook(0xE8,0x004C985D,&PrintDamageOnScreenHP); //s1
	
	SetCompleteHook(0xE8,0x005DEB82,&PrintPlayerViewMP);

	SetCompleteHook(0xE8,0x005DEA6F,&PrintPlayerViewHP);

	//SetCompleteHook(0xE8,0x005DEEDC,&PrintPlayerViewExperience);
}

void PrintPlayerViewExperience(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)
{
	char Status[50];

	sprintf_s(Status, "Experience: %d", ViewPoint);
	// ---
	pDrawInfo(a1, a2, Status, a4, a5, a6);
}

void PrintPlayerViewMP(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)
{
	char Status[50];

	sprintf_s(Status, "Mana: %d/%d", ViewCurMP, ViewMaxMP);
	// ---
	pDrawInfo(a1, a2, Status, a4, a5, a6);
}

void PrintPlayerViewHP(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)
{
	char Status[50];

	sprintf_s(Status, "HP: %d/%d", ViewCurHP, ViewMaxHP);
	// ---
	pDrawInfo(a1, a2, Status, a4, a5, a6);
}

void PrintPlayerViewMP1(DWORD a, char* b)
{
	((void(*)(DWORD,char*,...))0x0068EFC7)(a, b, ViewCurMP, ViewMaxMP);
}

void PrintPlayerViewBP1(DWORD a, char* b)
{
	((void(*)(DWORD,char*,...))0x0068EFC7)(a, b, ViewCurBP, ViewMaxBP);
}

void PrintPlayerViewHP1(DWORD a, char* b)
{
	((void(*)(DWORD,char*,...))0x0068EFC7)(a, b, ViewCurHP, ViewMaxHP);
}

void PrintPlayerViewHP2(float a, float b, DWORD c, float d, float e)
{
	PrintFixStatPoint();

	((void(*)(float,float,DWORD,float,float))0x0060DA80)(a + 21.0, b, ViewCurHP, d, e);
}

void PrintPlayerViewMP2(float a, float b, DWORD c, float d, float e)
{
	PrintFixStatPoint();

	((void(*)(float,float,DWORD,float,float))0x0060DA80)(a - 15.0, b, ViewCurMP, d, e);
}

void PrintPlayerViewBP2(float a, float b, DWORD c, float d, float e)
{
	PrintFixStatPoint();

	((void(*)(float,float,DWORD,float,float))0x0060DA80)(a, b, ViewCurBP, d, e);
}

void PrintFixStatPoint()
{
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x18) = GET_MAX_WORD_VALUE(ViewStrength);
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x32) = GET_MAX_WORD_VALUE(ViewAddStrength);
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1A) = GET_MAX_WORD_VALUE(ViewDexterity);
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x34) = GET_MAX_WORD_VALUE(ViewAddDexterity);
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1C) = GET_MAX_WORD_VALUE(ViewVitality);
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x36) = GET_MAX_WORD_VALUE(ViewAddVitality);
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1E) = GET_MAX_WORD_VALUE(ViewEnergy);
//	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x38) = GET_MAX_WORD_VALUE(ViewAddEnergy);
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x20) = GET_MAX_WORD_VALUE(ViewLeadership);
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x3E) = GET_MAX_WORD_VALUE(ViewAddLeadership);

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0E);

	if (*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x10) >  *(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x14))
	{
		*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x10) = 0;
	}

}

void PrintDamageOnScreenHP(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) // OK
{
	if(((int)b) > 0)
	{
		b = ViewDamageHP;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x0053DA80)(a,b,c,d,e);
}
