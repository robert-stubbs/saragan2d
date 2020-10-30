#ifndef _BASE_TOOL_H_
#define _BASE_TOOL_H_

namespace Editor {

	class BaseTool
	{
		public:
			BaseTool() {};
			~BaseTool() {};

			BaseTool* _parent = nullptr;

			BaseTool* _current_tool;
			bool has_current_tool = false;

			float window_x = 0.0f;
			float window_y = 0.0f;
			float vp_width = 0.0f;
			float vp_height = 0.0f;

			float world_x = 0.0f;
			float world_y = 0.0f;

			float gui_mouse_x = 0.0f;
			float gui_mouse_y = 0.0f;
			float system_mouse_x = 0.0f;
			float system_mouse_y = 0.0f;

			virtual inline void SetParent(BaseTool* parent) {
				_parent = parent;
			};

			virtual void Init() {}
			virtual void RenderUI() = 0;

			virtual void MouseDown(int button) {};
			virtual void MouseUp(int button) {};
			virtual void MouseMove(float x, float y) {};
			virtual void MouseMoveContext(float x, float y) {};
			virtual void MouseScroll(float xoffset, float yoffset) {};
	};
}

#endif