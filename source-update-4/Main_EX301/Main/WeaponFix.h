#pragma once

#define Naked(Function) void __declspec(naked) Function()
#define ITEMGET(type, index)		(type*512 + index)

#define MAX_ITEM									(512)
#define STACK_PTR									EBP
#define WEAPON_ID_CONTAINER							DWORD PTR SS:[EBP+0x1C]
#define OBJ_OFFS									0x289

#define RightHandFixup								0x2F0 
#define LeftHandFixup								0x310
#define WeaponViewFlagFixup							-0x1DC
#define HandFlagFixup								-0x1E4 
#define SafeZoneFlagFixup							-0x5C

#define SomeVal1Fixup								-0x1F0
#define SomeVal2Fixup								-0x1F4 
#define SomeVal3Fixup								8
#define SomeVal4									0x695CA2C

#define RotFixup									-0x2B8
#define TransFixup									-0x2AC

const int WeaponViewCheck_Hook = 0x00525BC1; //1.04j
const int WeaponViewCheck_Ret = 0x00525D18; //1.04j

const int SecondWeaponViewCheckReplacedCode_Hook = 0x00525F41;//1.04j
const int SecondWeaponViewCheck_Hook1 = 0x00525DD1 + 1;//1.04j
const int SecondWeaponViewCheck_Hook2 = 0x00525DDE + 1;//1.04j
const int SecondWeaponViewCheck_Ret = 0x00525F50;//1.04j
const int SecondWeaponViewFix_Hook = 0x0051D071; //1.04j
const int SecondWeaponViewFix_Ret = 0x0051D076; //1.04j

const int RotateFunc = 0x006F59F5; //1.04j
const int TransFunc = 0x006F5C91; //1.04j


void ReadyWeapon();
void WeaponViewCheck();
void SecondWeaponViewCheck();
void SecondWeaponViewCheckReplacedCode();
void SecondWeaponViewFix();
