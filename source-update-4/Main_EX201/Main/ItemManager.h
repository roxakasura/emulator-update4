#pragma once

#define ITEM_BASE_MODEL			582
#define MAX_ITEM_TYPE			512
#define ITEM(x,y)				((x*MAX_ITEM_TYPE)+y)
#define GET_ITEM(x,y) (((x)*MAX_ITEM_TYPE)+(y))
#define ITEM2(x, y)		((x * 512) + y + ITEM_BASE_MODEL)

void InitItem();
void ItemModelLoad();
void ItemTextureLoad();
void LoadItemModel(int index,char* folder,char* name,int value);
void LoadItemTexture(int index,char* folder,char* name,int value);
void GetItemColor(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e);