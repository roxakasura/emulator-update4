#pragma once

#define ITEM_ATTRIBUTE_ADDR									0x203
//--------
#define MIN_WING_INDEX										0x23
#define MAX_WING_INDEX										0x12C
//--------
#define MIN_WING_ITEMID										0x1823
#define MAX_WING_ITEMID										0x192C
//--------
#define MIN_WING_ITEMID2									0x1823+ITEM_ATTRIBUTE_ADDR
#define MAX_WING_ITEMID2									0x192C+ITEM_ATTRIBUTE_ADDR
//--------
#define ITEMGET2(x, y) (x * 512 + y) + WING_ID
#define ITEMGET(x, y) (x * 512 + y)
//--------
#define GET_ITEMTYPE(x)				((x)/512)
#define GET_ITEMINDEX(x)			((x)%512)

const int WING_ID = 0x203;
//--------
#define ITEMGET2(x, y) (x * 512 + y) + WING_ID
#define WING_CHARSET 17
#define ITEM_BASE_MODEL 0x203
#define ITEM_ATTRIBUTE_ADDR 0x203
#define MAX_ITEM_TYPE 512
#define ITEM(x,y)				((x*512)+y)
#define GET_ITEM(x,y) (((x)*MAX_ITEM_TYPE)+(y))
#define MIN_WING_INDEX										0x24
#define ITEM_ID(x,y)			((x*512)+y+515)
#define pInitModelData			((void(__cdecl*)()) 0x005FD0E0)
#define pInitTextureData		((void(__cdecl*)()) 0x005FE910)
#define pMakePreviewCharSet     ((void(*)(int aIndex, BYTE * CharSet, int PreviewObject, int Mode, int Agr5, int Agr6, int Agr7)) 0x0050A590)
#define _MakePreviewCharSet		((void(__cdecl*)(int aIndex,BYTE *CharSet,int Struct,int Mode))0x50A590)
#define pItemSetOptionAdd ((void(*)(LPVOID, unsigned __int8, unsigned __int8, BYTE))0x00540A50)//005493F0  /$ 55             PUSH EBP

#define GET_ITEM_MODEL(x,y) ((((x)*MAX_ITEM_TYPE)+(y))+ITEM_ATTRIBUTE_ADDR)

void InitItem();
void InitJewel();
void InitWing();
void ItemModelLoad();
void ItemTextureLoad();
void LoadItemModel(int index,char* folder,char* name,int value);
void LoadItemTexture(int index,char* folder,char* name,int value);
void GetItemColor(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e);
void LoadJewelUpgrade();
void LoadJewelApply();
void WingMakePreviewCharSet();
void ItemSetOption(LPVOID ItemStruct, unsigned __int8 Option, unsigned __int8 Special, BYTE Value);
void FixBoxTexture();
void CustomWingFunction01();
void CustomWingFunction02();
void CustomWingFunction03();
void CustomWingFunction04();
void CustomWingFunction05();
void CustomWingFunction06();
void CustomWingFunction07();
void CustomWingFunction08();
void CustomWingFunction09();
void CustomWingFunction10();
void CustomWingFunction11();
void CustomWingFunction12();
void CustomWingFunction13();
void CustomWingFunction14();
void CustomWingFunction15();
void CustomWingFunction16();
void CustomWingFunction17();
void CustomWingFunction18();
void CustomWingFunction19();
void CustomWingFunction20();
void CustomWingFunction21();
void CustomWingFunction22();
void CustomWingFunction23();
void CustomWingFunction24();
void DisableShine();
void _WingsCharSet(int aIndex,BYTE *CharSet,int Struct,int Mode);
void MakePreviewCharSet(int aIndex,BYTE *CharSet,int Struct,int Mode);
void AddWingCharSet();
void WingHideExcellentGlow();
void WingSetIncDamage(); // OK
void Teste();

void WingRemoveExcellent01();
void WingRemoveExcellent02();