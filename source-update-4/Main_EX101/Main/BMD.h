#pragma once

#include "MathLib.h"
#define oModelsClassPointer		0x05756AB8 //1.01t

class cModel
{
public:
	cModel();

	void TransformPosition(vec34_t Matrix,vec3_t Position,vec3_t WorldPosition,bool Translate=false);

public:
	char          Name[32];
	char          Version;					// 33
    short         NumBones;					// 34
	short         NumMeshs;					// 36
	short         NumActions;				// 38
	void		  *Meshs;					// 40
	void		  *Bones;					// 44
	void		  *Actions;					// 48
	void		  *Textures;				// 50
	short		  *IndexTexture;			// 54
	short         NumLightMaps;				// 58
	short         IndexLightMap;			// 60
	void          *LightMaps;				// 64
	bool          LightEnable;				// 68
	bool          ConstratEnable;			// 69
	vec3_t        BodyLight;				// 72, 76, 80
	int           BoneHead;					// 84
	int           BoneFoot[4];				// 88 92 96 100
	float         BodyScale;				// 104
	vec3_t        BodyOrigin;				// 108, 112, 116
	vec3_t        BodyAngle;				// 120, 124, 128
	float         BodyHeight;				// 133
	char          StreamMesh;				// 136
	vec3_t        ShadowAngle;				// 137, 141, 145
	char          Skin;						// 152
	bool          HideSkin;					// 153
    float         Velocity;					// 157
	unsigned char CurrentAction;			// 160
	unsigned char PriorAction;				// 161
	float         CurrentAnimation;			// 164
	short         CurrentAnimationFrame;	// 168
	short         Sounds[10];				// 170
	bool          LightMapEnable;			// 192
	// ----
	BYTE          Other[32];				// size 0xE0	ESTE ES EL TAMAÑO TOTAL REAL DE ESTA CLASE SOLO QUE NO TENGO TODOS LOS MIEMBROS, HERMEX ME DIO SOLAMENTE HASTA: "LightMapEnable"
											// PERO ACA EL TEMA ES EL SIGUIENTE MIRE:
};

extern cModel *&Models;
extern vec34_t*	BoneTransform;
