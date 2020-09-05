#include "EnginePCH.h"
#include "Sprite.h"
#include "Engine.h"
#include "RenderEngineBase.h"


namespace GameEngine {

	Sprite::Sprite()
	{
		// TODO
		/*
		
			1. Load AnimSprite
			2. Load Sprite Anim Defs
			3. Load Sprite Anim Frames


		*/
		AnimTime = 0.0f;
		last_frame = 0;
		current_frame = 0;
		next_anim = "";
		anim_loop_count = 0;
		last_anim_loop_count = 0;
	}

	Sprite::~Sprite()
	{

	}

	bool Sprite::Init()
	{
		return true;
	}

	void Sprite::Update(float dt)
	{
		if (loaded && current_anim.length() > 0) {
			// update which frame we should be on in the animation
			int numFrames = (int)_anim.anims[current_anim].number_of_frames;

			AnimTime += dt;

			float fFramNum = AnimTime * (float)_anim.anims[current_anim].frame_speed;
			int iFrame0 = (int)floorf(fFramNum);

			iFrame0 = iFrame0 % numFrames;

			if (iFrame0 > numFrames)
			{
				current_frame = 0;

			}  else {

				if (current_frame != last_frame)
				{
					last_frame = current_frame;

					if (last_frame >= numFrames - 1)
					{
						anim_loop_count++;
						//std::cout << "Loop Count " << anim_loop_count << std::endl;

					}
				}
				current_frame = iFrame0;
			}

			SpriteAnimDef* current = &_anim.anims[current_anim];

			if (current->wait_til_finished && current->loop_count == 0 && next_anim.size() > 0) {
				if (last_anim_loop_count != anim_loop_count) {
					// loop finished
					current_anim = next_anim.size() > 0 ? next_anim : _anim.idle_anim;

					last_anim_loop_count = 0;
					anim_loop_count = 0;
					AnimTime = 0;
					next_anim = "";
				}
			} else if (current->wait_til_finished &&  current->loop_count != 0 && anim_loop_count >= current->loop_count)
			{
				anim_loop_count = 0;
				AnimTime = 0;
				//std::cout << "Current Anim " << current_anim << " switching to " << next_anim << std::endl;
				current_anim = next_anim.size() > 0 ? next_anim : _anim.idle_anim;
				next_anim = "";
			}
		}
	}

	void Sprite::Render()
	{
		if (loaded && current_anim.length() > 0) {
			Engine::getShader().BindNewShader(m_shader);

			Engine::getRenderer().EnableBlend(true, BLEND_TYPE::SRC_ALPHA, BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

			if (Engine::getRenderer().CurrentTextureID != _anim.anims[current_anim].texture_id)
			{
				Engine::getRenderer().CurrentTextureID = _anim.anims[current_anim].texture_id;

				Engine::getRenderer().BindTextureBuffer(Engine::getRenderer().CurrentTextureID);
			}

			Engine::getRenderer().BindVertexBuffer(_anim.VAIO);
			Engine::getRenderer().BindIndexBuffer(_anim.IBO);

			
			int start_index = _anim.anims[current_anim].start_buffer_index;
			int frame_count = current_frame * 6;

			int start = (start_index + frame_count);
			 
			Engine::getRenderer().DrawIntElements(DRAW_TYPE::TRIANGLES, 6, start);

			Engine::getRenderer().UnbindIndexBuffer();
			Engine::getRenderer().UnbindVertexBuffer();

			Engine::getRenderer().EnableBlend(false);
		}
	}

	void Sprite::CleanUp()
	{

	}

	void Sprite::SetAnim(std::string name)
	{
		SpriteAnimDef* current = &_anim.anims[current_anim];
		SpriteAnimDef* def = &_anim.anims[name];

		if (current->wait_til_finished)
		{
			next_anim = name;
			//std::cout << "Trying to set next anim: " << next_anim << std::endl;
		}
		else {
			if (_anim.anims[name].reset_on_start) {
				current_frame = 0;
				AnimTime = 0;
			}
			current_anim = name;
			anim_loop_count = 0;
		}
	}
	
	void Sprite::LoadAnimSprite(AnimSprite& sprite)
	{
		_anim = sprite;

		// TODO this loading will move to the resource manager i think

		Engine::getRenderer().GenerateVertexArrayBuffer(_anim.VAIO);
		
		for (std::pair<std::string, SpriteAnimDef> def : _anim.anims)
		{
			LoadAnimSpriteDef(def.first);
		}

		Shader& s = Engine::getShader()[m_shader];

		Engine::getRenderer().GenerateIndexBuffer(_anim.IBO, _anim.vert_indices);
		Engine::getRenderer().GenerateBuffer(_anim.VBO, _anim.verts);

		Engine::getRenderer().VertexStructurePointerF(s["in_Position"], 4, GL_FALSE, sizeof(vert2D), 0);
		Engine::getRenderer().VertexStructurePointerF(s["in_Texture"], 2, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, Text));
		Engine::getRenderer().VertexStructurePointerF(s["in_Color"], 4, GL_TRUE, sizeof(vert2D), (GLvoid*)offsetof(vert2D, col));

		Engine::getRenderer().UnbindBuffer();
		Engine::getRenderer().UnbindIndexBuffer();
		Engine::getRenderer().UnbindVertexBuffer();

		loaded = true;
	}

	void Sprite::LoadAnimSpriteDef(std::string name)
	{
		SpriteAnimDef* def = &_anim.anims[name];

		// set the start of the buffers index
		def->start_buffer_index = (int)_anim.vert_indices.size();

		if (def->frames.size() == 0) {
			PopulateSpriteFrames(name, def->frame_width, def->frame_height);
		}

		for (SpriteAnimFrame& f: def->frames)
		{
			LoadAnimSpriteFrame(f);
			_anim.index_counter += 4;
		}

		def->number_of_frames = (int)def->frames.size();

		// set the end of the buffer and increment by 1 for next buffer
		def->end_buffer_index = (int)_anim.vert_indices.size() - 1;// _anim.index_counter;
		//_anim.index_counter++;
	}

	void Sprite::PopulateSpriteFrames(std::string name, float width, float height)
	{
		SpriteAnimDef* def = &_anim.anims[name];

		float width_index = (float)(_anim.sheet_width / _anim.sheet_columns) / (float)_anim.sheet_width;
		float height_index = (float)(_anim.sheet_height / _anim.sheet_rows) / (float)_anim.sheet_height;
		int row = def->sheet_row;
		int start_column = def->sheet_column;
		int number_of_frames = def->number_of_frames;

		def->frames = std::vector<SpriteAnimFrame>();
		for (int i = 0; i < number_of_frames; i++)
		{
			int column = start_column + i;
			def->frames.push_back({ {column*width_index, row * height_index}, {(column+1) * width_index,(row + 1) * height_index}, width, height });
		}
	}

	void Sprite::LoadAnimSpriteFrame(SpriteAnimFrame& frame)
	{
		vert2D tleft  = { {0.0f,0.0f,0.0f,1.0f				 },{frame.min_texture_coords[0], frame.min_texture_coords[1]}, { 1.0f, 1.0f, 1.0f, 1.0f } };
		vert2D tright = { {frame.width,0.0f,0.0f,1.0f		 },{frame.max_texture_coords[0], frame.min_texture_coords[1]}, { 1.0f, 1.0f, 1.0f, 1.0f } };
		vert2D bright = { {frame.width,frame.height,0.0f,1.0f},{frame.max_texture_coords[0], frame.max_texture_coords[1]}, { 1.0f, 1.0f, 1.0f, 1.0f } };
		vert2D bleft  = { {0.0f,frame.height,0.0f,1.0f		 },{frame.min_texture_coords[0], frame.max_texture_coords[1]}, { 1.0f, 1.0f, 1.0f, 1.0f } };

		_anim.verts.push_back(tleft);
		_anim.verts.push_back(tright);
		_anim.verts.push_back(bright);
		_anim.verts.push_back(bleft);

		_anim.vert_indices.push_back(_anim.index_counter + 0);
		_anim.vert_indices.push_back(_anim.index_counter + 1);
		_anim.vert_indices.push_back(_anim.index_counter + 2);

		_anim.vert_indices.push_back(_anim.index_counter + 2);
		_anim.vert_indices.push_back(_anim.index_counter + 3);
		_anim.vert_indices.push_back(_anim.index_counter + 0);

	}
}