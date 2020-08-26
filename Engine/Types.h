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

	typedef struct
	{
		std::string text;
		unsigned int VAIO;
		unsigned int IBO;
		unsigned int VBO;
		float x;
		float y;
		glm::vec4 color;
		texture_font_t* font;
		texture_atlas_t* atlas;
		std::vector<vert2D> verts;
		std::vector<int> VertIndex;
		bool loaded;
	} FontBuffer;

#pragma endregion platform enums

#pragma region Input 

#define ENGINE_KEY_SPACE              32
#define ENGINE_KEY_APOSTROPHE         39  /* ' */
#define ENGINE_KEY_COMMA              44  /* , */
#define ENGINE_KEY_MINUS              45  /* - */
#define ENGINE_KEY_PERIOD             46  /* . */
#define ENGINE_KEY_SLASH              47  /* / */
#define ENGINE_KEY_0                  48
#define ENGINE_KEY_1                  49
#define ENGINE_KEY_2                  50
#define ENGINE_KEY_3                  51
#define ENGINE_KEY_4                  52
#define ENGINE_KEY_5                  53
#define ENGINE_KEY_6                  54
#define ENGINE_KEY_7                  55
#define ENGINE_KEY_8                  56
#define ENGINE_KEY_9                  57
#define ENGINE_KEY_SEMICOLON          59  /* ; */
#define ENGINE_KEY_EQUAL              61  /* = */
#define ENGINE_KEY_A                  65
#define ENGINE_KEY_B                  66
#define ENGINE_KEY_C                  67
#define ENGINE_KEY_D                  68
#define ENGINE_KEY_E                  69
#define ENGINE_KEY_F                  70
#define ENGINE_KEY_G                  71
#define ENGINE_KEY_H                  72
#define ENGINE_KEY_I                  73
#define ENGINE_KEY_J                  74
#define ENGINE_KEY_K                  75
#define ENGINE_KEY_L                  76
#define ENGINE_KEY_M                  77
#define ENGINE_KEY_N                  78
#define ENGINE_KEY_O                  79
#define ENGINE_KEY_P                  80
#define ENGINE_KEY_Q                  81
#define ENGINE_KEY_R                  82
#define ENGINE_KEY_S                  83
#define ENGINE_KEY_T                  84
#define ENGINE_KEY_U                  85
#define ENGINE_KEY_V                  86
#define ENGINE_KEY_W                  87
#define ENGINE_KEY_X                  88
#define ENGINE_KEY_Y                  89
#define ENGINE_KEY_Z                  90
#define ENGINE_KEY_LEFT_BRACKET       91  /* [ */
#define ENGINE_KEY_BACKSLASH          92  /* \ */
#define ENGINE_KEY_RIGHT_BRACKET      93  /* ] */
#define ENGINE_KEY_GRAVE_ACCENT       96  /* ` */
#define ENGINE_KEY_WORLD_1            161 /* non-US #1 */
#define ENGINE_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define ENGINE_KEY_ESCAPE             256
#define ENGINE_KEY_ENTER              257
#define ENGINE_KEY_TAB                258
#define ENGINE_KEY_BACKSPACE          259
#define ENGINE_KEY_INSERT             260
#define ENGINE_KEY_DELETE             261
#define ENGINE_KEY_RIGHT              262
#define ENGINE_KEY_LEFT               263
#define ENGINE_KEY_DOWN               264
#define ENGINE_KEY_UP                 265
#define ENGINE_KEY_PAGE_UP            266
#define ENGINE_KEY_PAGE_DOWN          267
#define ENGINE_KEY_HOME               268
#define ENGINE_KEY_END                269
#define ENGINE_KEY_CAPS_LOCK          280
#define ENGINE_KEY_SCROLL_LOCK        281
#define ENGINE_KEY_NUM_LOCK           282
#define ENGINE_KEY_PRINT_SCREEN       283
#define ENGINE_KEY_PAUSE              284
#define ENGINE_KEY_F1                 290
#define ENGINE_KEY_F2                 291
#define ENGINE_KEY_F3                 292
#define ENGINE_KEY_F4                 293
#define ENGINE_KEY_F5                 294
#define ENGINE_KEY_F6                 295
#define ENGINE_KEY_F7                 296
#define ENGINE_KEY_F8                 297
#define ENGINE_KEY_F9                 298
#define ENGINE_KEY_F10                299
#define ENGINE_KEY_F11                300
#define ENGINE_KEY_F12                301
#define ENGINE_KEY_F13                302
#define ENGINE_KEY_F14                303
#define ENGINE_KEY_F15                304
#define ENGINE_KEY_F16                305
#define ENGINE_KEY_F17                306
#define ENGINE_KEY_F18                307
#define ENGINE_KEY_F19                308
#define ENGINE_KEY_F20                309
#define ENGINE_KEY_F21                310
#define ENGINE_KEY_F22                311
#define ENGINE_KEY_F23                312
#define ENGINE_KEY_F24                313
#define ENGINE_KEY_F25                314
#define ENGINE_KEY_KP_0               320
#define ENGINE_KEY_KP_1               321
#define ENGINE_KEY_KP_2               322
#define ENGINE_KEY_KP_3               323
#define ENGINE_KEY_KP_4               324
#define ENGINE_KEY_KP_5               325
#define ENGINE_KEY_KP_6               326
#define ENGINE_KEY_KP_7               327
#define ENGINE_KEY_KP_8               328
#define ENGINE_KEY_KP_9               329
#define ENGINE_KEY_KP_DECIMAL         330
#define ENGINE_KEY_KP_DIVIDE          331
#define ENGINE_KEY_KP_MULTIPLY        332
#define ENGINE_KEY_KP_SUBTRACT        333
#define ENGINE_KEY_KP_ADD             334
#define ENGINE_KEY_KP_ENTER           335
#define ENGINE_KEY_KP_EQUAL           336
#define ENGINE_KEY_LEFT_SHIFT         340
#define ENGINE_KEY_LEFT_CONTROL       341
#define ENGINE_KEY_LEFT_ALT           342
#define ENGINE_KEY_LEFT_SUPER         343
#define ENGINE_KEY_RIGHT_SHIFT        344
#define ENGINE_KEY_RIGHT_CONTROL      345
#define ENGINE_KEY_RIGHT_ALT          346
#define ENGINE_KEY_RIGHT_SUPER        347
#define ENGINE_KEY_MENU               348

#define ENGINE_MOUSE_BUTTON_1         0
#define ENGINE_MOUSE_BUTTON_2         1
#define ENGINE_MOUSE_BUTTON_3         2
#define ENGINE_MOUSE_BUTTON_4         3
#define ENGINE_MOUSE_BUTTON_5         4
#define ENGINE_MOUSE_BUTTON_6         5
#define ENGINE_MOUSE_BUTTON_7         6
#define ENGINE_MOUSE_BUTTON_8         7
#define ENGINE_MOUSE_BUTTON_LAST      ENGINE_MOUSE_BUTTON_8
#define ENGINE_MOUSE_BUTTON_LEFT      ENGINE_MOUSE_BUTTON_1
#define ENGINE_MOUSE_BUTTON_RIGHT     ENGINE_MOUSE_BUTTON_2
#define ENGINE_MOUSE_BUTTON_MIDDLE    ENGINE_MOUSE_BUTTON_3

#pragma endregion Input

}

#endif 