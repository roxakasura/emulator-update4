#include "stdafx.h"
#include "CEffect.h"
#include "Util.h"
#include "TMemory.h"

// ----
DWORD dwItemId;
DWORD dwWingThis;
DWORD dwWingStyle;
DWORD dwWingEff;
// ----
DWORD dwCustomItemGlowJmp00 = 0x0061D3CB;
DWORD dwCustomItemGlowJmp01 = 0x0061D3BF;
Naked(CustomItemGlow)
{
 _asm
 { 
 // ----
 MOV EAX, DWORD PTR SS:[EBP+0x10]
 MOV dwItemId, EAX
 // ----
 MOV EDX,DWORD PTR SS:[EBP+0x8]
 MOV dwWingThis, EDX
 // ----
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV dwWingStyle, EAX
 // ----
 }
 
 if(dwItemId == ITEMS2(0,26)) //Flameberge
 {
 // ----
 glColor3fv((GLfloat*)(dwWingThis+72));
 // ----
 RenderMesh(dwWingThis,          
 0,
 2,
 *(GLfloat *)(dwWingStyle + 424),
 *(DWORD *)(dwWingStyle + 148),
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 RenderMesh(dwWingThis,
 2,
 2,
 *(GLfloat *)(dwWingStyle + 424),
 2,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 *(float *)(dwWingThis + 72) = 1.0;
 *(float *)(dwWingThis + 76) = 0.0;
 *(float *)(dwWingThis + 80) = 0.2;
 RenderMesh(dwWingThis,
 1,
 66,
 *(GLfloat *)(dwWingStyle + 424),
 1,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 *(float *)(dwWingThis + 72) = 1.0;
 *(float *)(dwWingThis + 76) = 1.0;
 *(float *)(dwWingThis + 80) = 1.0;
 RenderMesh(dwWingThis,
 1,
 70,
 *(GLfloat *)(dwWingStyle + 424),
 1,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 RenderMesh(dwWingThis,
 3,
 66,
 *(GLfloat *)(dwWingStyle + 424),
 3,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 RenderMesh(dwWingThis,      
 4,
 66,
 *(GLfloat *)(dwWingStyle + 424),
 4,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 float v407 = ((int)(timeGetTime() * 0.05) % 16 / 4) * 0.25;
 RenderMesh(dwWingThis,
 5,
 66,
 1.0,
 5,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 v407,
 -1);
 
 _asm
 {
 //---
 JMP dwCustomItemGlowJmp01
 }
 }

 if(dwItemId == ITEMS2(0,27)) //Sword Breaker
 {
 // ----
 glColor3fv((GLfloat*)(dwWingThis+72));
 // ----
 RenderMesh(dwWingThis,          
 0,
 2,
 *(GLfloat *)(dwWingStyle + 424),
 *(DWORD *)(dwWingStyle + 148),
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 RenderMesh(dwWingThis,          
 1,
 2,
 *(GLfloat *)(dwWingStyle + 424),
 *(DWORD *)(dwWingStyle + 148),
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 RenderMesh(dwWingThis,
 1,
 70,
 *(GLfloat *)(dwWingStyle + 424),
 1,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 
 _asm
 {
 //---
 JMP dwCustomItemGlowJmp01
 } 
 }
 /*
 if(dwItemId == ITEMS2(5,31)) //Inberial Staff
 {
 // ----
 glColor3fv((GLfloat*)(dwWingThis+72));
 // ----
 RenderMesh(dwWingThis,          
 0,
 2,
 *(GLfloat *)(dwWingStyle + 424),
 *(DWORD *)(dwWingStyle + 148),
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 RenderMesh(dwWingThis,          
 1,
 66,
 *(GLfloat *)(dwWingStyle + 424),
 1,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 float v40 = (int)timeGetTime() * 0.001000000047497451;
 float v41 = sub_49CC70(v40);
 RenderMesh(dwWingThis,          
 0,
 66,
 *(GLfloat *)(dwWingStyle + 424),
 0,
 v41,
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 32401);
 
 _asm
 {
 //---
 JMP dwCustomItemGlowJmp01
 }
 }
 */
 
 if(dwItemId == ITEMS2(6,17)) //Crimson Glory
 {
 // ----
 glColor3fv((GLfloat*)(dwWingThis+72));
 // ----
 RenderMesh(dwWingThis,          
 0,
 2,
 *(GLfloat *)(dwWingStyle + 424),
 *(DWORD *)(dwWingStyle + 148),
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 RenderMesh(dwWingThis,          
 1,
 66,
 *(GLfloat *)(dwWingStyle + 424),
 1,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 RenderMesh(dwWingThis,          
 2,
 70,
 *(GLfloat *)(dwWingStyle + 424),
 2,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 
 _asm
 {
 //---
 JMP dwCustomItemGlowJmp01
 }
 }
 
 if(dwItemId == ITEMS2(6,19)) //Frost Barrier
 {
 // ----
 glColor3fv((GLfloat*)(dwWingThis+72));
 // ----
 RenderMesh(dwWingThis,          
 0,
 2,
 *(GLfloat *)(dwWingStyle + 424),
 *(DWORD *)(dwWingStyle + 148),
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 RenderMesh(dwWingThis,          
 1,
 66,
 *(GLfloat *)(dwWingStyle + 424),
 1,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);
 float v40 = (int)timeGetTime() * 0.001000000047497451;
 float v41 = sub_49CC70(v40);
 RenderMesh(dwWingThis,          
 2,
 66,
 *(GLfloat *)(dwWingStyle + 424),
 2,
 v41,
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);

 _asm
 {
 //---
 JMP dwCustomItemGlowJmp01
 }
 }
 
 if(dwItemId == ITEMS2(6,21)) //Cross Shield
 {
 // ----
 glColor3fv((GLfloat*)(dwWingThis+72));
 // ----
 RenderMesh(dwWingThis,          
 0,
 2,
 *(GLfloat *)(dwWingStyle + 424),
 *(DWORD *)(dwWingStyle + 148),
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1); 
 float v407 = ((int)timeGetTime() % 2000) * 0.25;
 RenderMesh(dwWingThis,          
 1,
 70,
 *(GLfloat *)(dwWingStyle + 424),
 *(DWORD *)(dwWingStyle + 148),
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 v407,
 -1); 
 RenderMesh(dwWingThis,          
 2,
 66,
 *(GLfloat *)(dwWingStyle + 424),
 2,
 *(float *)(dwWingStyle + 152),
 *(float *)(dwWingStyle + 156),
 *(float *)(dwWingStyle + 160),
 -1);

 _asm
 {
 //---
 JMP dwCustomItemGlowJmp01
 }
 }
 // ----
 _asm
 {
 //---
 CMP DWORD PTR SS:[EBP+0x10],0x1AAD //Wing of Storm
 JMP dwCustomItemGlowJmp00
 }
}

void __declspec ( naked ) NOGlow1() 
{
    static DWORD Return = 0x0062356D;
 static DWORD CALL = 0x005059D2;
 static DWORD JMP = 0x00623674;
    // ----
    _asm 
 {
 CMP DWORD PTR SS:[EBP+0x10],0x29E
 JNZ NOGlow1Prop_Label1
 MOV EDX,DWORD PTR SS:[EBP+0x20]
 PUSH EDX
 PUSH 0
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0xA0]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0xC]
 MOV EAX,DWORD PTR DS:[EDX+0x9C]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0x98]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0x94]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0x14]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0x18]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0x8]
 CALL CALL
 JMP JMP
 // ----
        NOGlow1Prop_Label1:
 // ----
 CMP DWORD PTR SS:[EBP+0x10],ITEMS2(0,26)//Flameberge
 JNZ NOGlow1Prop_Label2
 MOV EDX,DWORD PTR SS:[EBP+0x20]
 PUSH EDX
 PUSH 5 //<<Grupo de la Textura
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0xA0]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0xC]
 MOV EAX,DWORD PTR DS:[EDX+0x9C]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0x98]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0x94]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0x14]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0x18]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0x8]
 CALL CALL
 JMP JMP
 // ----
        NOGlow1Prop_Label2:
 // ----
 CMP DWORD PTR SS:[EBP+0x10],ITEMS2(0,27)//Sword Breaker
 JNZ NOGlow1Prop_Label3
 MOV EDX,DWORD PTR SS:[EBP+0x20]
 PUSH EDX
 PUSH 1 //<<Grupo de la Textura
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0xA0]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0xC]
 MOV EAX,DWORD PTR DS:[EDX+0x9C]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0x98]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0x94]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0x14]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0x18]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0x8]
 CALL CALL
 JMP JMP
 // ----
        NOGlow1Prop_Label3:
 // ----
 CMP DWORD PTR SS:[EBP+0x10],ITEMS2(6,19)//Frost Barrier
 JNZ NOGlow1Prop_Label4
 MOV EDX,DWORD PTR SS:[EBP+0x20]
 PUSH EDX
 PUSH 2 //<<Grupo de la Textura
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0xA0]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0xC]
 MOV EAX,DWORD PTR DS:[EDX+0x9C]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0x98]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0x94]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0x14]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0x18]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0x8]
 CALL CALL
 JMP JMP
 // ----
        NOGlow1Prop_Label4:
 // ----
 CMP DWORD PTR SS:[EBP+0x10],ITEMS2(6,21)//Cross Shield
 JNZ NOGlow1Prop_Label5
 MOV EDX,DWORD PTR SS:[EBP+0x20]
 PUSH EDX
 PUSH 1 //<<Grupo de la Textura
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0xA0]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0xC]
 MOV EAX,DWORD PTR DS:[EDX+0x9C]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0x98]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0x94]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0x14]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0x18]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0x8]
 CALL CALL
 JMP JMP
 // ----
        NOGlow1Prop_Label5:
 // ----
        NOGlow1Prop_LabelReturn:
        // ----
 JMP Return
 } 
}

void __declspec ( naked ) NOGlow2() 
{
    static DWORD Return = 0x0062356D;
 static DWORD CALL = 0x005059D2;
 static DWORD JMP = 0x0062392D;
    // ----
    _asm 
 {
 CMP DWORD PTR SS:[EBP+0x10],0x29E
 JNZ NOGlow2Prop_Label1
 MOV EAX,DWORD PTR SS:[EBP+0x20]
 PUSH EAX
 PUSH 0
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0xA0]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0x9C]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0xC]
 MOV EAX,DWORD PTR DS:[EDX+0x98]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0x94]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0x14]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0x18]
 PUSH ECX
 MOV ECX,DWORD PTR SS:[EBP+0x8]
 CALL CALL
 JMP JMP
 // ----
        NOGlow2Prop_Label1:
 // ----
 CMP DWORD PTR SS:[EBP+0x10],ITEMS2(0,26)//Flameberge
 JNZ NOGlow2Prop_Label2
 MOV EAX,DWORD PTR SS:[EBP+0x20]
 PUSH EAX
 PUSH 5 //<<Grupo de la Textura
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0xA0]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0x9C]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0xC]
 MOV EAX,DWORD PTR DS:[EDX+0x98]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0x94]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0x14]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0x18]
 PUSH ECX
 MOV ECX,DWORD PTR SS:[EBP+0x8]
 CALL CALL
 JMP JMP
 // ----
        NOGlow2Prop_Label2:
 // ----
 CMP DWORD PTR SS:[EBP+0x10],ITEMS2(0,27)//Sword Breaker
 JNZ NOGlow2Prop_Label3
 MOV EAX,DWORD PTR SS:[EBP+0x20]
 PUSH EAX
 PUSH 1 //<<Grupo de la Textura
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0xA0]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0x9C]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0xC]
 MOV EAX,DWORD PTR DS:[EDX+0x98]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0x94]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0x14]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0x18]
 PUSH ECX
 MOV ECX,DWORD PTR SS:[EBP+0x8]
 CALL CALL
 JMP JMP
 // ----
        NOGlow2Prop_Label3:
 // ----
 CMP DWORD PTR SS:[EBP+0x10],ITEMS2(6,19)//Frost Barrier
 JNZ NOGlow2Prop_Label4
 MOV EAX,DWORD PTR SS:[EBP+0x20]
 PUSH EAX
 PUSH 2 //<<Grupo de la Textura
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0xA0]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0x9C]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0xC]
 MOV EAX,DWORD PTR DS:[EDX+0x98]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0x94]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0x14]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0x18]
 PUSH ECX
 MOV ECX,DWORD PTR SS:[EBP+0x8]
 CALL CALL
 JMP JMP
 // ----
        NOGlow2Prop_Label4:
 // ----
 CMP DWORD PTR SS:[EBP+0x10],ITEMS2(6,21)//Cross Shield
 JNZ NOGlow2Prop_Label5
 MOV EAX,DWORD PTR SS:[EBP+0x20]
 PUSH EAX
 PUSH 1 //<<Grupo de la Textura
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0xA0]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0xC]
 MOV ECX,DWORD PTR DS:[EAX+0x9C]
 PUSH ECX
 MOV EDX,DWORD PTR SS:[EBP+0xC]
 MOV EAX,DWORD PTR DS:[EDX+0x98]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0xC]
 MOV EDX,DWORD PTR DS:[ECX+0x94]
 PUSH EDX
 MOV EAX,DWORD PTR SS:[EBP+0x14]
 PUSH EAX
 MOV ECX,DWORD PTR SS:[EBP+0x18]
 PUSH ECX
 MOV ECX,DWORD PTR SS:[EBP+0x8]
 CALL CALL
 JMP JMP
 // ----
        NOGlow2Prop_Label5:
 // ----
        NOGlow2Prop_LabelReturn:
        // ----
 JMP Return
 } 
}

void CEffect()
{
 SetCompleteHook(0xE9,0x0061D3C4, &CustomItemGlow);
 SetCompleteHook(0xE9,0x00623521, &NOGlow1);
 SetCompleteHook(0xE9,0x006237B9, &NOGlow2);
}