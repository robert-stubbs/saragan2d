#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "Types.h"
#include "ContextPlatform.h"

namespace GameEngine
{
	class Context
	{
		private:
			ContextPlatform* _platform;

		public:

			void SetPlatform(PLATFORM platform);

			bool InitWindow(int width, int height, std::string window_name, bool fullscreen = false);
			bool InitContext();

			inline ContextPlatform& GetWindow() { return *_platform; }
	};
}

#endif