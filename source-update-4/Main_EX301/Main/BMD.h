#ifndef __BMD_H__
#define __BMD_H__

#include "MathLib.h"
#define oModelsClassPointer							0x05801AE8

class MODEL
{
public:
	MODEL();

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
	bool          LightMapEnable;
	// ----
	BYTE          Other[48];				// size 0xF0
};

extern MODEL *&Models;
extern vec34_t*	BoneTransform;

#endif	// __BMD_H__