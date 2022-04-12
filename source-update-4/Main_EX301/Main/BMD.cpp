#include "StdAfx.h"
#include "BMD.h"
#include "EffectManager.h"

MODEL *&Models = *(MODEL**)oModelsClassPointer;
vec34_t* BoneTransform	= (vec34_t*)(oBoneTransformPointer); // MAX BONE 200

MODEL::MODEL()
{
}

void MODEL::TransformPosition(vec34_t Matrix,vec3_t Position,vec3_t WorldPosition,bool Translate)
{
	pTransformPosition2(this,Matrix,Position,WorldPosition,Translate);
}