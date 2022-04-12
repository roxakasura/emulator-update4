#pragma once

#include "stdafx.h"

#define ItemArray 649
#define ItemId(x, y) (x * 512 + y)
#define ObjectId(x, y) (x * 512 + y) + ItemArray

#define pCursorX				*(int*)0x7AFE950 //1.04j
#define pCursorY				*(int*)0x7AFE94C //1.04j

void ItemNoExcellent();
void GlobalMessage();
char CreatePetEffect(int Arg1, char Arg2);
int CentrarItems(float PosResuX, float PosResuY, float X, float Y, int IDItems, int Level, int a7, int a8, int Tamao);