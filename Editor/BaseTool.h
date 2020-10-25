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

			virtual inline void SetParent(BaseTool* parent) {
				_parent = parent;
			};

			virtual void Init() {}
			virtual void RenderUI() = 0;

			virtual void MouseDown(int button) {};
			virtual void MouseUp(int button) {};
			virtual void MouseMove(float x, float y) {};
	};
}

#endif