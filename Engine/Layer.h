#ifndef _LAYER_H_
#define _LAYER_H_

#include "Types.h"

namespace GameEngine
{
	template <typename T>
	class Layer
	{
		protected:
			std::shared_ptr<T> _instance;
			RenderEngines engine_type;

		public:
			virtual void SetPlatform(PLATFORM platform) = 0;
			virtual void SetPlatformAndRenderer(PLATFORM platform, RenderEngines engine) {};

			virtual inline T& Get() { return *_instance; }
			virtual inline bool isSet() { 
				return _instance != nullptr; 
			}
	};

}

#endif