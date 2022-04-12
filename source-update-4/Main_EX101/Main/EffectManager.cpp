#include "stdafx.h"

CEffectManager gEffectManager;

CEffectManager::CEffectManager()
{
	// -> Constructor
	this->Init();
}

CEffectManager::~CEffectManager()
{
	// -> Destructor
}

void CEffectManager::Init()
{
}

void CEffectManager::DrawItemEffect(LPOBJPREVIEW Owner,int ObjectId,vec3_t Light,float Alpha,int ItemLevel,int NewOption,int SetOption,int Select,int RenderType)
{
	vec3_t WorldPosition	= {0.0f,0.0f,0.0f};
	vec3_t Position			= {0.0f,0.0f,0.0f};
	vec3_t vColor			= {0.0f,0.0f,0.0f};
	vec3_t vAngle			= {0.0f,0.0f,0.0f};
	// ----
	cModel *Obj				= &Models[ObjectId];
	// ----

	//static effect
	for (std::vector<CUSTOM_WING_EFFECT_INFO>::iterator it = gCustomWingEffect.m_CustomWingEffectInfo.begin(); it != gCustomWingEffect.m_CustomWingEffectInfo.end(); it++)
	{
		if ((it->ItemIndex + ITEM_BASE_MODEL) == ObjectId)
		{
			Obj->TransformPosition(BoneTransform[it->EffectBone], Position, WorldPosition, true);
			Vector(it->ColorR, it->ColorG, it->ColorB, vColor);
			// ----
			pCreateSprite(it->EffectIndex, WorldPosition, it->EffectSize, vColor, Owner, 0.0f, 0);
		}
	}

	//dynamic effect
	for (std::vector<DYNAMIC_WING_EFFECT_INFO>::iterator it = gDynamicWingEffect.m_DynamicWingEffectInfo.begin(); it != gDynamicWingEffect.m_DynamicWingEffectInfo.end(); it++)
	{
		if ((it->ItemIndex + ITEM_BASE_MODEL) == ObjectId)
		{
			Obj->TransformPosition(BoneTransform[it->EffectBone], Position, WorldPosition, true);
			Vector(it->ColorR, it->ColorG, it->ColorB, vColor);
			// ----
			pCreateParticle(it->EffectIndex, WorldPosition, Owner->Angle, vColor, it->EffectSize, it->EffectSize, Owner);
		}
	}
	// ----
	pRenderPartObjectEffect(Owner,ObjectId,Light,Alpha,ItemLevel,NewOption,SetOption,Select,RenderType);
}

void CEffectManager::Load()
{
	if (gDynamicWingEffect.m_DynamicWingEffectInfo.size() || gCustomWingEffect.m_CustomWingEffectInfo.size())
	{
		SetOp((LPVOID)(0x0050074D), this->DrawItemEffect, ASM::CALL);// ok
		SetOp((LPVOID)(0x005FA6BB), this->DrawItemEffect, ASM::CALL);// ok -> esse causa conflitos no efeito
	}
}

