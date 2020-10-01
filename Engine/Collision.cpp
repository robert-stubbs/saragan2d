#include "EnginePCH.h"
#include "Collision.h"

#include "Engine.h"
#include "Location.h"

namespace GameEngine {

	Collision::Collision()
	{
		m_type = "COLLISION";
		_type = CollisionType::BOX;

		// for box
		_min = glm::vec3(0.0f, 0.0f, 0.0f);
		_max = glm::vec3(0.0f, 0.0f, 0.0f);

		// for sphere
		_center = glm::vec3(0.0f, 0.0f, 0.0f);
		_radius = 0;

		_verts = std::vector<vert2D>();
		_color = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
		_color_collide = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f);

		_loaded = false;
		_render_collision = false;
		_shader_name = "DEFAULT2D";
	}

	Collision::~Collision()
	{
		if (e) {
			e = nullptr;
		}
	}

	bool Collision::Init()
	{



		return true;
	}

	void Collision::Update(float dt)
	{

	}

	void Collision::Render() 
	{
		if (_render_collision)
		{
			if (!_loaded) {
				GenerateSphereVerts();
			} else {
				Engine::getShader().BindNewShader(_shader_name);

				Location* loc = (Location*)e->getComponent("LOCATION");
				if (loc != nullptr) {
					Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], loc->getPositionMat(), 1, false);
				}
				else {
					Engine::getRenderer().UniformMat4(Engine::getCurrentShader()["modelMatrix"], glm::mat4(1.0f), 1, false);
				}

				Engine::getRenderer().BindVertexBuffer(VAO);

				Engine::getRenderer().DrawArrays(DRAW_TYPE::TRIANGLE_FAN, (int)_verts.size());

				Engine::getRenderer().UnbindVertexBuffer();
			}
		}
	}

	void Collision::CleanUp()
	{
		Engine::getRenderer().DeleteBuffer(VBO);
		Engine::getRenderer().DeleteVertexBuffer(VAO);
		_verts.clear();
	}

	void Collision::setColors(glm::vec4 col, glm::vec4 collision_col)
	{
		_color = col;
		_color_collide = collision_col;
	}

	void Collision::GenerateSphereVerts()
	{
		_verts.clear();
		_verts.push_back({ { _center.x, _center.y, _center.z,1.0f }, { -99.0f, -99.0f }, {_color.r, _color.g, _color.b, _color.a } });

		for (int i = 0; i <= 20; i++) {

			float c = (float)cos((double)i * TWO_PI / 20.0f);
			float s = (float)sin((double)i * TWO_PI / 20.0f);
			_verts.push_back({ { _center.x + (_radius * c), _center.y + (_radius * s), _center.z,1.0f }, { -99.0f, -99.0f }, {_color.r, _color.g, _color.b, _color.a } });
		}

		if (!VBO || VBO == 0)
		{
			Shader& s = Engine::getShader()[_shader_name];

			Engine::getRenderer().GenerateVertexArrayBuffer(VAO);
			Engine::getRenderer().GenerateBuffer(VBO, _verts);

			s.BindShaderStructure();

			Engine::getRenderer().UnbindBuffer();
			Engine::getRenderer().UnbindVertexBuffer();

			_loaded = true;
		}
	}

	void Collision::UpdateSphereVerts(bool collide)
	{
		if (_loaded) {
			glm::vec4 selected_color = _color;
			if (collide) {
				selected_color = _color_collide;
			}

			_verts.clear();
			_verts.push_back({ { _center.x, _center.y, _center.z,1.0f }, { -99.0f, -99.0f }, {selected_color.r, selected_color.g, selected_color.b, selected_color.a } });

			for (int i = 0; i <= 20; i++) {

				float c = (float)cos((double)i * TWO_PI / 20.0f);
				float s = (float)sin((double)i * TWO_PI / 20.0f);
				_verts.push_back({ { _center.x + (_radius * c), _center.y + (_radius * s), _center.z,1.0f }, { -99.0f, -99.0f }, {selected_color.r, selected_color.g, selected_color.b, selected_color.a } });
			}

			if (VBO != 0)
			{
				Shader& s = Engine::getShader()[_shader_name];

				Engine::getRenderer().BindVertexBuffer(VAO);
				Engine::getRenderer().BindBuffer(VBO);

				Engine::getRenderer().UpdateBuffer(VBO, _verts);

				Engine::getRenderer().UnbindBuffer();
				Engine::getRenderer().UnbindVertexBuffer();
			}
		}
	}

	glm::vec3 Collision::GetCollisionWorldPos()
	{
		glm::vec3 ent_pos = glm::vec3(0.0f, 0.0f, 1.0f);
		Location* loc = (Location*)e->getComponent("LOCATION");
		if (loc != nullptr) {
			glm::vec3& locpos = loc->getPosition();
			ent_pos = glm::vec3(locpos.x, locpos.y, 1.0f);
		}
		return ent_pos;
	}

	bool Collision::doesCollide(Collision* col)
	{
		if (_type == CollisionType::BOX) {
			if (col->_type == CollisionType::BOX) {
				return BoxToBoxCollision(_min, _max, col->_min, col->_max);
			} else if (col->_type == CollisionType::SPEHERE) {
				return SphereToBoxCollision(col->_center, col->_radius, _min, _max);
			}
		} else if (_type == CollisionType::SPEHERE) {
			if (col->_type == CollisionType::BOX) {
				return SphereToBoxCollision(col->_center, col->_radius, _min, _max);
			} else if (col->_type == CollisionType::SPEHERE) {

				glm::vec3 worldpos = GetCollisionWorldPos();
				glm::vec3 c = worldpos + _center;

				glm::vec3 worldpos2 = col->GetCollisionWorldPos();
				glm::vec3 c2 = worldpos2 + col->_center;

				return SphereToSphereCollision(c2, col->_radius, c, _radius);
			}
		}
		return false;
	}

	void Collision::setBoxCollision(glm::vec3 min, glm::vec3 max)
	{
		_min = min;
		_max = max;
		_type = CollisionType::BOX;
	}

	void Collision::setSphereCollision(glm::vec3 center, float radius)
	{
		_center = center;
		_radius = radius;
		_type = CollisionType::SPEHERE;
	}

	bool Collision::SphereToSphereCollision(glm::vec3 center, float radius, glm::vec3 center2, float radius2)
	{
		float dist = glm::distance(center2, center);
		float rad = radius + radius2;
		bool collides = (dist < rad);

		if (_render_collision) {
			UpdateSphereVerts(collides);
		}

		return collides;
	}

	bool Collision::SphereToBoxCollision(glm::vec3 center, float radius, glm::vec3 min, glm::vec3 max)
	{

		return false;
	}

	bool Collision::BoxToBoxCollision(glm::vec3 min, glm::vec3 max, glm::vec3 min2, glm::vec3 max2)
	{

		return false;
	}

}