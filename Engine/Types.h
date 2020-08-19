#ifndef _TYPES_H_
#define _TYPES_H_
namespace GameEngine {

	typedef struct
	{
		float  pos[4];
		float  Text[2];
	} vert;

	typedef struct
	{
		float  pos[4];
		float  Text[2];
		float  Normal[3];
		float  BoneWeight[4];
		float  BoneIndex[4];

	} animVert;

	typedef struct
	{
		float  pos[3];
		float  Text[2];
		float  col[4];
	} vert2D;
}

#endif 