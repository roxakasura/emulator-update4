#include "stdafx.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Util.h"

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
	SetCompleteHook(0xE8, 0x005A096C, &PrintPlayerViewHP2); //ok interface
	SetCompleteHook(0xE8, 0x005A0993, &PrintPlayerViewMP2); //ok interface
	SetCompleteHook(0xE8, 0x0059F07A, &PrintPlayerViewSD2); //ok interface
	SetCompleteHook(0xE8, 0x0059ED0A, &PrintPlayerViewBP2); //ok interface

	SetCompleteHook(0xE8, 0x0059FAF6, &PrintPlayerViewHP1); //ok ao passar cursor
	SetCompleteHook(0xE8, 0x0059FBFF, &PrintPlayerViewMP1); //ok ao passar cursor
	SetCompleteHook(0xE8, 0x0059F103, &PrintPlayerViewSD1); //ok ao passar cursor
	SetCompleteHook(0xE8, 0x0059ED97, &PrintPlayerViewBP1); //ok ao passar cursor

	SetDword(0x0049F6ED,0xA0000001); // PrintTextReplace 64

	SetDword(0x004AB73A,0xA0000002); // PrintTextReplace 64

	SetDword(0x005B3AD4,0xA0000003); // PrintTextReplace 64

//	SetDword(0x005B4931,0xA0000004); // PrintTextReplace 64 bug de visualização de speed arma

	SetDword(0x0049F68B,0xA0000001); // PrintTextReplace 64

	SetDword(0x004AB6DE,0xA0000002); // PrintTextReplace 203

	SetCompleteHook(0xE9,0x00402267,&PrintPlayerViewText);

	SetCompleteHook(0xE8,0x004FF521,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x0067CCC7,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x0067D08C,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x0067D19A,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x0067D1F1,&PrintDamageOnScreenSD); //s3

	SetCompleteHook(0xE8,0x0067DDA8,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x0067DE03,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x0067DE9A,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x0067DEF5,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x0067DF10,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x0067DF6A,&PrintDamageOnScreenSD); //s3

	SetCompleteHook(0xE8,0x006821C9,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x00682B1E,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x00682B54,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x006835F0,&PrintDamageOnScreenHP); //s3

	SetCompleteHook(0xE8,0x00683626,&PrintDamageOnScreenHP); //s3
}

void PrintPlayerViewSD1(DWORD a, char* b)
{
	((void(*)(DWORD,char*,...))0x00739528)(a, b, ViewCurSD, ViewMaxSD);
}

void PrintPlayerViewMP1(DWORD a, char* b)
{
	((void(*)(DWORD,char*,...))0x00739528)(a, b, ViewCurMP, ViewMaxMP);
}

void PrintPlayerViewBP1(DWORD a, char* b)
{
	((void(*)(DWORD,char*,...))0x00739528)(a, b, ViewCurBP, ViewMaxBP);
}

void PrintPlayerViewHP1(DWORD a, char* b)
{
	((void(*)(DWORD,char*,...))0x00739528)(a, b, ViewCurHP, ViewMaxHP);
}

void PrintPlayerViewHP2(float a, float b, DWORD c, float d, float e)
{
	PrintFixStatPoint();

	//((void(*)(float, float, DWORD, float, float))0x006435D6)(a, b - 17.0, ViewCurHP, d, e);
	((void(*)(float, float, DWORD, float, float))0x006435D6)(a + 8, b, ViewCurHP, d, e);
}

void PrintPlayerViewMP2(float a, float b, DWORD c, float d, float e)
{
	PrintFixStatPoint();

	//((void(*)(float,float,DWORD,float,float))0x006435D6)(a, b - 17.0, ViewCurMP, d, e);
	((void(*)(float, float, DWORD, float, float))0x006435D6)(a - 17, b, ViewCurMP, d, e);
}

void PrintPlayerViewSD2(float a, float b, DWORD c, float d, float e)
{
	PrintFixStatPoint();

	((void(*)(float,float,DWORD,float,float))0x006435D6)(a, b, ViewCurSD, d, e);
}

void PrintPlayerViewBP2(float a, float b, DWORD c, float d, float e)
{
	PrintFixStatPoint();

	((void(*)(float,float,DWORD,float,float))0x006435D6)(a, b, ViewCurBP, d, e);
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
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x38) = GET_MAX_WORD_VALUE(ViewAddEnergy);
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

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x006F3D60)(a,b,c,d,e);
}

void PrintDamageOnScreenSD(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) // OK
{
	if(((int)b) > 0)
	{
		b = ViewDamageSD;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x006F3D60)(a,b,c,d,e);
}

__declspec(naked) void PrintPlayerViewText() // OK
{
	static DWORD PrintPlayerViewTextAddress1 = 0x0040226E;

	_asm
	{
		Cmp Ecx,0xA0000000
		Jle NEXT1
		Mov Dword Ptr Ss:[Ebp-0x04],0x0750DF88
		Sub Ecx,0xA0000000
		Jmp NEXT2
		NEXT1:
		Xor Ecx,Ecx
		NEXT2:
		Push Ecx
		Mov Edx,Ebp
		Add Edx,0x08
		Push Edx
		Call [PrintTextReplace]
		Add Esp,0x08
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Jmp [PrintPlayerViewTextAddress1]
	}
}


void PrintTextReplace(DWORD* value,DWORD type) // OK
{
	switch(value[0])
	{
		case 64: //"Velocidade de ataque: %d"
			switch(type)
			{
				case 1:
					value[1] = ViewDarkSpiritAttackSpeed;
					break;
				case 2:
					value[1] = ViewPhysiSpeed;
					break;
				case 3:
					value[1] = ViewPhysiSpeed;
					break;
				case 4:
					value[1] = ViewDarkSpiritAttackSpeed;
					break;
				case 5:
					value[1] = ViewDarkSpiritAttackSpeed;
					break;
			}
			break;
		case 170: //"Dano mágico:%d~%d"
			GetViewMagicDamage(&value[1],&value[2]);
			break;
		case 203: //"Taxa de dano: %d~%d (%d)"
			switch(type)
			{
				case 1:
					GetViewDarkSpiritDamage(&value[1],&value[2]);
					value[3] = ViewDarkSpiritAttackSuccessRate;
					break;
				case 2:
					GetViewPhisyDamage(&value[1],&value[2]);
					value[3] = ViewAttackSuccessRate;
					break;
				case 3:
					GetViewPhisyDamage(&value[1],&value[2]);
					value[3] = ViewAttackSuccessRate;
					break;
				case 4:
					GetViewDarkHorseDamage(&value[1],&value[2]);
					value[3] = ViewDarkSpiritAttackSuccessRate;
					break;
				case 5:
					GetViewDarkSpiritDamage(&value[1],&value[2]);
					value[3] = ViewDarkSpiritAttackSuccessRate;
					break;
			}
			break;
		case 204: //"Dano: %d~%d"
			GetViewPhisyDamage(&value[1],&value[2]);
			break;
		case 206: //"Taxa de defesa: %d (%d +%d)"
			value[0] = 208;
			value[1] = ViewDefense;
			value[2] = ViewDefenseSuccessRate;
			break;
		case 207: //"Defesa: %d (+%d)"
			value[0] = 209;
			value[1] = ViewDefense;
			break;
		case 208: //"Taxa de defesa: %d (%d)"
			value[1] = ViewDefense;
			value[2] = ViewDefenseSuccessRate;
			break;
		case 209: //"Defesa: %d"
			value[1] = ViewDefense;
			break;
		case 211: //"HP: %d / %d"
			value[1] = ViewCurHP;
			value[2] = ViewMaxHP;
			break;
		case 213: //"Mana: %d / %d"
			value[1] = ViewCurMP;
			value[2] = ViewMaxMP;
			break;
		case 214: //"AG: %d / %d"
			value[1] = ViewCurBP;
			value[2] = ViewMaxBP;
			break;
		case 215: //"Dano mágico: %d~%d (+%d) - Wizardry Dmg
			GetViewMagicDamage(&value[1],&value[2],&value[3]);
			break;
		case 216: //"Dano mágico: %d~%d"
			GetViewMagicDamage(&value[1],&value[2]);
			break;
		case 217: //"Ponto(s): %d"
			value[1] = ViewPoint;
			break;
		case 358: //"Vida: %d/%d"
			switch(type)
			{
				case 1:
					value[1] = ViewCurHP;
					value[2] = ViewMaxHP;
					break;
				case 2:
					value[1] = value[1];
					value[2] = value[2];
					break;
				case 3:
					value[1] = value[1];
					value[2] = value[2];
					break;
			}
			break;
		case 359: //"Mana: %d/%d"
			value[1] = ViewCurMP;
			value[2] = ViewMaxMP;
			break;
		case 379: //"(%s fruta(s)) %d pontos de atributo foram %s."
			value[2] = ViewValue;
			break;
		case 582: //"Dano da habilidade: %d%%"
			value[1] = ViewDamageMultiplier;
			break;
		case 879: //"Dano da habilidade: %d~%d"
			GetViewSkillDamage(&value[1],&value[2]);
			break;
		case 1692: //"Curse Spell: %d ~ %d"
			GetViewCurseDamage(&value[1],&value[2]);
			break;
		case 1693: //"Curse Spell: %d ~ %d(+%d)"
			GetViewCurseDamage(&value[1],&value[2],&value[3]);
			break;
		case 1694: //"Curse Spell: %d ~ %d"
			GetViewCurseDamage(&value[1],&value[2]);
			break;
		case 2037: //"SD : %d / %d"
			value[1] = ViewCurSD;
			value[2] = ViewMaxSD;
			break;
		case 2044: //"Taxa de ataque: %d"
			value[1] = ViewAttackSuccessRatePvP;
			break;
		case 2045: //"Taxa de defesa: %d"
			value[1] = ViewDefenseSuccessRatePvP;
			break;
		case 2109: //"Taxa de ataque: %d (+%d)"
			value[0] = 2044;
			value[1] = ViewAttackSuccessRatePvP;
			break;
		case 2110: //"Taxa de defesa:%d (+%d)"
			value[0] = 2045;
			value[1] = ViewDefenseSuccessRatePvP;
			break;
	}
}

void GetViewPhisyDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewPhysiDamageMin;

	(*DamageMax) = ViewPhysiDamageMax;

	(*DamageMin) += ((*DamageMin)*ViewMulPhysiDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulPhysiDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivPhysiDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivPhysiDamage)/100;
}

void GetViewSkillDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewPhysiDamageMin;

	(*DamageMax) = ViewPhysiDamageMax;

	(*DamageMin) += ViewSkillPhysiDamage;

	(*DamageMax) += ViewSkillPhysiDamage+(ViewSkillPhysiDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulPhysiDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulPhysiDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivPhysiDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivPhysiDamage)/100;
}

void GetViewMagicDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewMagicDamageMin;

	(*DamageMax) = ViewMagicDamageMax;

	(*DamageMin) += ViewSkillMagicDamage;

	(*DamageMax) += ViewSkillMagicDamage+(ViewSkillMagicDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulMagicDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulMagicDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivMagicDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivMagicDamage)/100;
}

void GetViewMagicDamage(DWORD* DamageMin,DWORD* DamageMax,DWORD* DamageRate) // OK
{
	(*DamageMin) = ViewMagicDamageMin;

	(*DamageMax) = ViewMagicDamageMax;

	(*DamageMin) += ViewSkillMagicDamage;

	(*DamageMax) += ViewSkillMagicDamage+(ViewSkillMagicDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulMagicDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulMagicDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivMagicDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivMagicDamage)/100;

	(*DamageRate) = ((*DamageMax)*ViewMagicDamageRate)/100;
}

void GetViewCurseDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewCurseDamageMin;

	(*DamageMax) = ViewCurseDamageMax;

	(*DamageMin) += ViewSkillMagicDamage;

	(*DamageMax) += ViewSkillMagicDamage+(ViewSkillMagicDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulCurseDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulCurseDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivCurseDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivCurseDamage)/100;
}

void GetViewCurseDamage(DWORD* DamageMin,DWORD* DamageMax,DWORD* DamageRate) // OK
{
	(*DamageMin) = ViewCurseDamageMin;

	(*DamageMax) = ViewCurseDamageMax;

	(*DamageMin) += ViewSkillMagicDamage;

	(*DamageMax) += ViewSkillMagicDamage+(ViewSkillMagicDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulCurseDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulCurseDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivCurseDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivCurseDamage)/100;

	(*DamageRate) = ((*DamageMax)*ViewCurseDamageRate)/100;
}

void GetViewDarkSpiritDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewDarkSpiritAttackDamageMin;

	(*DamageMax) = ViewDarkSpiritAttackDamageMax;
}

void GetViewDarkHorseDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewPhysiDamageMin;

	(*DamageMax) = ViewPhysiDamageMax;

	(*DamageMin) += ViewSkillPhysiDamage;

	(*DamageMax) += ViewSkillPhysiDamage+(ViewSkillPhysiDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulPhysiDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulPhysiDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivPhysiDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivPhysiDamage)/100;
}
