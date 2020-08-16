#ifndef _OBJECT_H
#define	_OBJECT_H


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

class Object
{
public:

	bool hasUpdate;

	bool isLoaded;

	Object();
	~Object();
	virtual void Init();
	virtual void Update(float dt);
	virtual bool Render();
	virtual void CleanUp();

};

#endif