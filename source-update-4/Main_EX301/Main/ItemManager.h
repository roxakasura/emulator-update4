#pragma once

#define MAX_ITEM_SECTION 16
#define MAX_ITEM_TYPE 512
#define MAX_ITEM (MAX_ITEM_SECTION*MAX_ITEM_TYPE)
#define ITEM_BASE_MODEL 649

#define GET_ITEM(x,y) (((x)*MAX_ITEM_TYPE)+(y))
#define GET_ITEM_MODEL(x,y) ((((x)*MAX_ITEM_TYPE)+(y))+ITEM_BASE_MODEL)
#define ITEM(x, y)		((x * 512) + y)
#define ITEM2(x, y)		((x * 512) + y + ITEM_BASE_MODEL)

void InitItem();
void InitJewel();
void InitWing();
void ItemModelLoad();
void ItemTextureLoad();
void LoadItemModel(int index,char* folder,char* name,int value);
void LoadItemTexture(int index,char* folder,char* name,int value);
void GetItemColor(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e);
BYTE CustomBuddlePack(int index);
void FixBoxTexture();
void RenaDescFix();
void GmBoxEffect();
void WingMakePreviewCharSet();
void WingDisableLevelGlow();
void WingSetIncDamage();
void WingSetDecDamage();
void WingSetModelType();
void WingCheckIndex1();
void WingCheckIndex3();
void WingCheckIndex4();
void WingCheckIndex5();
void WingCheckIndex6();
void WingCheckIndex7();
void WingCheckIndex8();
void WingCheckIndex9();
void WingCheckIndex10();
void WingCheckIndex11();
void WingCheckIndex12();
void WingCheckIndex13();
void WingCheckIndex14();
void WingCheckIndex15();
void WingCheckIndex16();
void WingCheckIndex17();
void WingCheckIndex18();
void WingCheckIndex20();
void WingCheckIndex21();
void WingCheckIndex23();
void WingCheckModelIndex1();
void WingCheckModelIndex2();
void WingCheckModelIndex3();
void WingsShowAdditionals();
void WingAddLifeOption();

void JewelSetSalePrice();
void JewelInsertOne();
void JewelInsertTwo();

void WingEnableMoveIcarus();
void WingEnableMoveIcarus2();
void WingEnableMoveKanturuEvent();

void WingShowDurability();
void WingEnableMoveKanturuEvent2();
void WingHideExcellentGlow();