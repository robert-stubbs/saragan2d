#ifndef _INPUT_H_
#define _INPUT_H_

#include "InputPlatform.h"
#include "Types.h"
#include "Layer.h"

namespace GameEngine
{
	class Input : public Layer<InputPlatform>
	{
		private:
			static Input _input;

		public:
			virtual void SetPlatform(PLATFORM platform) override;

			static Input& GetInput() {
				return _input;
			}

			static inline InputPlatform& Get() { return GetInput().Get(); }
	};
}

#endif