#include "stdafx.h"
#include "Extra.h"
#include "ObjectManager.h"
#include "User.h"
#include "Protocol.h"

cPatentSystem gPatentSystem;

void cPatentSystem::PatentSystem(LPOBJ lpObj)
{
#if(WILLIAMCUSTOM)
	switch (lpObj->ExpWar)
	{
	case 30:
		lpObj->AddLife += 10;
		break;
	case 50:
		lpObj->AddLife += 15;
		break;
	case 100:
		lpObj->AddLife += 20;
		lpObj->PhysiSpeed += 3;
		lpObj->MagicSpeed += 3;
		break;
	case 200:
		lpObj->AddLife += 35;
		lpObj->PhysiSpeed += 7;
		lpObj->MagicSpeed += 7;
		break;
	case 300:
		lpObj->AddLife += 60;
		lpObj->PhysiSpeed += 7;
		lpObj->MagicSpeed += 7;
		break;
	case 400:
		lpObj->AddLife += 90;
		lpObj->PhysiSpeed += 10;
		lpObj->MagicSpeed += 10;
		break;
	case 500:
		lpObj->AddLife += 125;
		lpObj->PhysiSpeed += 13;
		lpObj->MagicSpeed += 13;
		break;
	case 1000:
		lpObj->AddLife += 200;
		lpObj->PhysiSpeed += 18;
		lpObj->MagicSpeed += 18;
		lpObj->CriticalDamageRate += 1;
		break;
	case 2000:
		lpObj->AddLife += 250;
		lpObj->PhysiSpeed += 23;
		lpObj->MagicSpeed += 23;
		lpObj->CriticalDamageRate += 2;
		break;
	case 3000:
		lpObj->AddLife += 300;
		lpObj->PhysiSpeed += 28;
		lpObj->MagicSpeed += 28;
		lpObj->CriticalDamageRate += 3;
		break;
	case 4000:
		lpObj->AddLife += 350;
		lpObj->PhysiSpeed += 33;
		lpObj->MagicSpeed += 33;
		lpObj->CriticalDamageRate += 4;
		break;
	case 5000:
		lpObj->AddLife += 400;
		lpObj->PhysiSpeed += 38;
		lpObj->MagicSpeed += 38;
		lpObj->CriticalDamageRate += 5;
		break;
	case 7000:
		lpObj->AddLife += 500;
		lpObj->PhysiSpeed += 50;
		lpObj->MagicSpeed += 50;
		lpObj->CriticalDamageRate += 5;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 1;
		break;
	case 12000:
		lpObj->AddLife += 1000;
		lpObj->PhysiSpeed += 65;
		lpObj->MagicSpeed += 65;
		lpObj->CriticalDamageRate += 5;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 2;
		break;
	case 17000:
		lpObj->AddLife += 1500;
		lpObj->PhysiSpeed += 80;
		lpObj->MagicSpeed += 80;
		lpObj->CriticalDamageRate += 5;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 3;
		break;
	case 23000:
		lpObj->AddLife += 2000;
		lpObj->PhysiSpeed += 90;
		lpObj->MagicSpeed += 90;
		lpObj->CriticalDamageRate += 6;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 4;
		break;
	case 28000:
		lpObj->AddLife += 2500;
		lpObj->PhysiSpeed += 100;
		lpObj->MagicSpeed += 100;
		lpObj->CriticalDamageRate += 7;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 5;
		break;
	case 33000:
		lpObj->AddLife += 3000;
		lpObj->PhysiSpeed += 110;
		lpObj->MagicSpeed += 110;
		lpObj->CriticalDamageRate += 8;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 5;
		break;
	case 40000:
		lpObj->AddLife += 5000;
		lpObj->PhysiSpeed += 125;
		lpObj->MagicSpeed += 125;
		lpObj->CriticalDamageRate += 10;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 5;
		break;
	case 50000:
		lpObj->AddLife += 6500;
		lpObj->PhysiSpeed += 140;
		lpObj->MagicSpeed += 140;
		lpObj->CriticalDamageRate += 10;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 7;
		lpObj->ExcellentDamageRate += 1;
		break;
	case 75000:
		lpObj->AddLife += 9000;
		lpObj->PhysiSpeed += 160;
		lpObj->MagicSpeed += 160;
		lpObj->CriticalDamageRate += 10;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 7;
		lpObj->ExcellentDamageRate += 3;
		break;
	case 100000:
		lpObj->AddLife += 12000;
		lpObj->PhysiSpeed += 180;
		lpObj->MagicSpeed += 180;
		lpObj->CriticalDamageRate += 10;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 7;
		lpObj->ExcellentDamageRate += 5;
		break;
	case 125000:
		lpObj->AddLife += 12000;
		lpObj->PhysiSpeed += 200;
		lpObj->MagicSpeed += 200;
		lpObj->CriticalDamageRate += 12;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 8;
		lpObj->ExcellentDamageRate += 7;
		break;
	case 200000:
		lpObj->AddLife += 15000;
		lpObj->PhysiSpeed += 200;
		lpObj->MagicSpeed += 200;
		lpObj->CriticalDamageRate += 15;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 10;
		lpObj->ExcellentDamageRate += 10;
		break;
	case 250000:
		lpObj->AddLife += 15000;
		lpObj->PhysiSpeed += 200;
		lpObj->MagicSpeed += 200;
		lpObj->CriticalDamageRate += 15;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 15;
		lpObj->ExcellentDamageRate += 15;
		break;
	case 300000:
		lpObj->AddLife += 20000;
		lpObj->PhysiSpeed += 200;
		lpObj->MagicSpeed += 200;
		lpObj->CriticalDamageRate += 18;
		lpObj->DamageReduction[DAMAGE_REDUCTION_EXCELLENT_ITEM] += 18;
		lpObj->ExcellentDamageRate += 18;
		break;
	}
#endif
}