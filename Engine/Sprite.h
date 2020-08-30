#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Types.h"
#include "Component.h"

namespace GameEngine {

	class Sprite : public Component {
		private:
			AnimSprite _anim;
			std::string current_anim;
			int current_frame;
			int last_frame;
			float AnimTime;

		public:
			Sprite();
			virtual ~Sprite();

			virtual bool Init() override;

			virtual void Update(float dt) override;

			virtual void Render() override;

			virtual void CleanUp() override;

			virtual void SetAnim(std::string name);

			virtual void LoadAnimSprite(AnimSprite& sprite);
			virtual void LoadAnimSpriteDef(std::string name);
			virtual void PopulateSpriteFrames(std::string name);
			virtual void LoadAnimSpriteFrame(SpriteAnimFrame& frame);
	};

}

#endif