#pragma once
#define ITEM_INTER 649
#define ITEMS(x, y) ((x * 512) + y)
#define ITEMS2(x, y) ((x * 512) + y + ITEM_INTER)
#define Naked(Function) void __declspec(naked) Function()
#define RenderMesh ((void(__thiscall*)(int This, int a2, int a3, GLfloat alpha, int a5, float a6, float a7, float a8, int a9)) 0x00502F50)
#define sub_49CC70 ((double(__cdecl*)(float a1)) 0x0049CC70)
#define sub_644101 ((double(__cdecl*)(float a1)) 0x00644101)

void CEffect();
