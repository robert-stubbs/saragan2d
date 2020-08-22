#ifndef _TYPES_H_
#define _TYPES_H_
namespace GameEngine {

#pragma region Events
	struct EventType {
		class Event* event;
		std::string name;
	};
#pragma endregion Events

#pragma region Positions
	struct viewPos
	{
		float x;
		float y;
		float width;
		float height;
	};

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
		float  pos[4];
		float  Text[2];
		float  col[4];
	} vert2D;
#pragma endregion Positions

#pragma region platform enums

	enum class PLATFORM
	{
		WINDOWS,
		GLFW,
		LINUX,
		MAC
	};

	enum RenderEngines
	{
		None = 0,
		OpenGL,
		DirectX
	};

	enum class SHADER_TYPES
	{
		UNIFORM,
		ATRIBLOCATION
	};

	enum class SHADER_VAR_TYPES
	{
		INT,
		FLOAT,
		VEC2,
		VEC3,
		VEC4,
		MAT4		
	};

	typedef struct
	{
		SHADER_TYPES location_type;
		std::string name;
		unsigned int index;
	} ShaderBinding;

	enum class DRAW_TYPE
	{
		LINE,
		LINES,
		LINE_LOOP,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		QUADS,
		QUAD_STRIP
	};

	enum class VALUE_TYPE
	{
		UNSIGNED_BYTE, 
		UNSIGNED_SHORT,
		UNSIGNED_INT
	};

	enum class BLEND_TYPE
	{
		SRC_COLOR,
		ONE_MINUS_SRC_COLOR,
		SRC_ALPHA,
		ONE_MINUS_SRC_ALPHA,
		DST_ALPHA,
		ONE_MINUS_DST_ALPHA,
		DST_COLOR,
		ONE_MINUS_DST_COLOR,
		SRC_ALPHA_SATURATE
	};
#pragma endregion platform enums
}

#endif 