#include "stdafx.h"
#include "EffectManager.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "ItemManager.h"
#include "MemScript.h"
#include "MathLib.h"
#include "Util.h"
#include "BMD.h"

CEffectManager gEffectManager;

void CEffectManager::Load()    
{
	SetOp((LPVOID)(0x0051D40E),this->DrawItemEffect,ASM::CALL);// ok
	//SetOp((LPVOID)(0x00628CDC),this->DrawItemEffect,ASM::CALL);// ok
	//SetOp((LPVOID)(0x0051CBB8),this->CreateSpriteEx,ASM::CALL);// ok
	//SetOp((LPVOID)(0x0048EE98),this->CreateParticleEx,ASM::CALL);// ok
	//SetOp((LPVOID)(0x0051CB9B),this->AllowStaticEffect,ASM::CALL);// ok
}

void CEffectManager::DrawItemEffect(LPOBJECT o,int Type,vec3_t Light,float Alpha,int ItemLevel,int NewOption,int SetOption,int Select,int RenderType)
{
	MODEL *Object = &Models[Type];
	//
	vec3_t WorldPosition	= {0.0f,0.0f,0.0f};
	vec3_t Position			= {0.0f,0.0f,0.0f};
	vec3_t Bone={0.0f,0.0f,0.0f};
	vec3_t Color={0.0f,0.0f,0.0f};
	vec3_t Color2={0.0f,0.0f,0.0f};
	vec3_t WorldPos;
	//
	if(Object)
	{
		for(int i=0;i<=gCustomWingEffect.count;i++)
		{
			if(Type == (gCustomWingEffect.m_CustomWingEffectInfo[i].ItemIndex+649))
			{
				Vector(gCustomWingEffect.m_CustomWingEffectInfo[i].ColorR,gCustomWingEffect.m_CustomWingEffectInfo[i].ColorG,gCustomWingEffect.m_CustomWingEffectInfo[i].ColorB,Color);
				pTransformPosition(Object,JointId(gCustomWingEffect.m_CustomWingEffectInfo[i].EffectBone),WorldPos,Bone,TRUE);
				pCreateSprite(gCustomWingEffect.m_CustomWingEffectInfo[i].EffectIndex,Bone,gCustomWingEffect.m_CustomWingEffectInfo[i].EffectSize,Color,o,0,0); 
			}
		}

		for(int i=0;i<=gDynamicWingEffect.count;i++)
		{
			if(Type == (gDynamicWingEffect.m_DynamicWingEffectInfo[i].ItemIndex+649))
			{
				Object->TransformPosition(BoneTransform[gDynamicWingEffect.m_DynamicWingEffectInfo[i].EffectBone],Position,WorldPosition,true);
				Vector(gDynamicWingEffect.m_DynamicWingEffectInfo[i].ColorR,gDynamicWingEffect.m_DynamicWingEffectInfo[i].ColorG,gDynamicWingEffect.m_DynamicWingEffectInfo[i].ColorB,Color2);
				pCreateParticle(gDynamicWingEffect.m_DynamicWingEffectInfo[i].EffectIndex,WorldPosition,o->Angle,Color2,11,gDynamicWingEffect.m_DynamicWingEffectInfo[i].EffectSize,o);
			}
		}
	}

	pDrawItemEffect(o,Type,Light,Alpha,ItemLevel,NewOption,SetOption,Select,RenderType);
}


int CEffectManager::CreateSpriteEx(int Type,vec3_t Position,float Scale,vec3_t Light,LPOBJECT Owner,float Rotation,int SubType)
{
	return pCreateSprite(Type,Position,gEffectManager.m_EffectInfo->EffectStaticSize,Light,Owner,Rotation,SubType); //ok 
}

int CEffectManager::CreateParticleEx(int Type,vec3_t Position,vec3_t Angle,vec3_t Light,int SubType,float Scale,LPOBJECT Owner)
{
	MODEL *Object = &Models[Type];

	Type = gEffectManager.m_EffectInfo->EffectDynamicIndex;
	Scale += 5.0;

//	return pCreateParticle(Type,Position,Angle,Light,SubType,Scale,Owner); //ok 
}

int CEffectManager::AllowStaticEffect(float *This, int a2, int a3, int a4, char a5)
{
	return pAllowStaticEffect(This, a2, a3, a4, a5); // 1.04j ok
}

