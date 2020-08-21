#ifndef _TEXT_ITEM_H_
#define _TEXT_ITEM_H_

#include "Object.h"
#include "Component.h"
#include "Types.h"

namespace GameEngine
{
	class Font;

	class Text : public Component
	{
	public:
		bool loaded;
		bool readyForBuffer;

		GLuint VAIO;
		GLuint IBO;
		GLuint VBO;

		glm::mat4 modelMatrix;

		std::string text;
		float x;
		float y;
		float fontSize;
		glm::vec4 color;
		Font* f;
		glm::vec2 pen;

		std::vector<vert> verts;
		std::vector<int> VertIndex;

		Text();
		~Text();

		virtual bool Init();

		virtual void SetString(Font* font, std::string s, float X, float Y, glm::vec4 col);
		virtual void AddText(std::string text, glm::vec2* pen);

		virtual void changeText(std::string newText);

		virtual void Update(float dt);
		virtual void Render();
		virtual void RenderAnim() {};
		virtual void RenderUI() {};
		virtual bool handleMessage(SystemMessage msg);

		virtual void CleanUp();
	};
}
#endif