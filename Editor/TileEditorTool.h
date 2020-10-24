#ifndef _TILE_EDITOR_TOOL_H_
#define _TILE_EDITOR_TOOL_H_

#include "BaseTool.h"
#include "Texture.h"

namespace Editor {

	class TileEditorTool : public BaseTool
	{
	public:
		GameEngine::Texture _t;
		std::string _path;
		bool _hasTexture;

		TileEditorTool() {};
		~TileEditorTool() {};

		virtual void LoadTexture(std::string path);
		virtual void RenderUI() override;
	};
}

#endif