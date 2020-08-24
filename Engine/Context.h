#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "Layer.h"
#include "Types.h"
#include "ContextPlatform.h"

namespace GameEngine
{
	class Context : public Layer<ContextPlatform>
	{
		public:

			virtual void SetPlatform(PLATFORM platform) override;

			bool InitWindow(int width, int height, std::string window_name, bool fullscreen = false);
			bool InitContext();
			void SwapContextBuffers();
	};
}

#endif