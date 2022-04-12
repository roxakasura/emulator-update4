#pragma once

#define GET_MAX_WORD_VALUE(x) (((x)>65000)?65000:((WORD)(x)))

void InitPrintPlayer();
void PrintFixStatPoint();
void PrintPlayerViewText();

void PrintPlayerViewHP1(DWORD a, char* b);
void PrintPlayerViewSD1(DWORD a, char* b);
void PrintPlayerViewBP1(DWORD a, char* b);
void PrintPlayerViewMP1(DWORD a, char* b);

void PrintPlayerViewHP2(float a, float b, DWORD c, float d, float e);
void PrintPlayerViewSD2(float a, float b, DWORD c, float d, float e);
void PrintPlayerViewBP2(float a, float b, DWORD c, float d, float e);
void PrintPlayerViewMP2(float a, float b, DWORD c, float d, float e);
void PrintTextReplace(DWORD* value,DWORD type);

void PrintDamageOnScreenHP(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e);
void PrintDamageOnScreenSD(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e);

void GetViewPhisyDamage(DWORD* DamageMin,DWORD* DamageMax);
void GetViewSkillDamage(DWORD* DamageMin,DWORD* DamageMax);
void GetViewMagicDamage(DWORD* DamageMin,DWORD* DamageMax);
void GetViewMagicDamage(DWORD* DamageMin,DWORD* DamageMax,DWORD* DamageRate);
void GetViewCurseDamage(DWORD* DamageMin,DWORD* DamageMax);
void GetViewCurseDamage(DWORD* DamageMin,DWORD* DamageMax,DWORD* DamageRate);
void GetViewDarkSpiritDamage(DWORD* DamageMin,DWORD* DamageMax);
void GetViewDarkHorseDamage(DWORD* DamageMin,DWORD* DamageMax);

extern DWORD ViewIndex;
extern DWORD ViewReset;
extern DWORD ViewValue;
extern DWORD ViewPoint;
extern DWORD ViewCurHP;
extern DWORD ViewMaxHP;
extern DWORD ViewCurMP;
extern DWORD ViewMaxMP;
extern DWORD ViewCurBP;
extern DWORD ViewMaxBP;
extern DWORD ViewCurSD;
extern DWORD ViewMaxSD;
extern DWORD ViewDamageHP;
extern DWORD ViewDamageSD;
extern DWORD ViewExperience;
extern DWORD ViewNextExperience;
extern QWORD ViewMasterExperience;
extern QWORD ViewMasterNextExperience;
extern DWORD ViewStrength;
extern DWORD ViewDexterity;
extern DWORD ViewVitality;
extern DWORD ViewEnergy;
extern DWORD ViewLeadership;
extern DWORD ViewAddStrength;
extern DWORD ViewAddDexterity;
extern DWORD ViewAddVitality;
extern DWORD ViewAddEnergy;
extern DWORD ViewAddLeadership;
extern DWORD ViewPhysiDamageMin;
extern DWORD ViewPhysiDamageMax;
extern DWORD ViewMagicDamageMin;
extern DWORD ViewMagicDamageMax;
extern DWORD ViewCurseDamageMin;
extern DWORD ViewCurseDamageMax;
extern DWORD ViewMulPhysiDamage;
extern DWORD ViewDivPhysiDamage;
extern DWORD ViewMulMagicDamage;
extern DWORD ViewDivMagicDamage;
extern DWORD ViewMulCurseDamage;
extern DWORD ViewDivCurseDamage;
extern DWORD ViewMagicDamageRate;
extern DWORD ViewCurseDamageRate;
extern DWORD ViewPhysiSpeed;
extern DWORD ViewMagicSpeed;
extern DWORD ViewAttackSuccessRate;
extern DWORD ViewAttackSuccessRatePvP;
extern DWORD ViewDefense;
extern DWORD ViewDefenseSuccessRate;
extern DWORD ViewDefenseSuccessRatePvP;
extern DWORD ViewDamageMultiplier;
extern DWORD ViewDarkSpiritAttackDamageMin;
extern DWORD ViewDarkSpiritAttackDamageMax;
extern DWORD ViewDarkSpiritAttackSpeed;
extern DWORD ViewDarkSpiritAttackSuccessRate;
