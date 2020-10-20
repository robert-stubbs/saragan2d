#ifndef _BASE_TOOL_H_
#define _BASE_TOOL_H_

namespace Editor {

	class BaseTool
	{
		public:
			BaseTool() {};
			~BaseTool() {};

			virtual void Init() {}
			virtual void RenderUI() = 0;
	};
}

#endif