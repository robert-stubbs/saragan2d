#include "EnginePCH.h"
#include "Collision.h"

#include "Engine.h"

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
		if (_render_collision && _loaded)
		{
			Engine::getShader().BindNewShader(_shader_name);

			Engine::getRenderer().EnableBlend(true, BLEND_TYPE::SRC_ALPHA, BLEND_TYPE::ONE_MINUS_SRC_ALPHA);

			Engine::getRenderer().BindVertexBuffer(VAO);

			Engine::getRenderer().DrawArrays(DRAW_TYPE::TRIANGLE_FAN, (GLsizei)_verts.size());

			Engine::getRenderer().UnbindVertexBuffer();

			Engine::getRenderer().EnableBlend(false);
		}
	}

	void Collision::CleanUp()
	{

	}

	void Collision::GenerateSphereVerts()
	{
		_verts.clear();
		_verts.push_back({ { _center.x, _center.y, _center.z }, { -99.0f, -99.0f }, {_color.r, _color.g, _color.b, _color.a } });

		for (int i = 0; i <= 20; i++) {

			float c = (float)cos((double)i * TWO_PI / 20.0f);
			float s = (float)sin((double)i * TWO_PI / 20.0f);
			_verts.push_back({ { _center.x + (_radius * c), _center.y + (_radius * s), _center.z }, { -99.0f, -99.0f }, {_color.r, _color.g, _color.b, _color.a } });
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

	bool Collision::doesCollide(Collision* col)
	{
		if (_type == CollisionType::BOX) {
			if (col->_type == CollisionType::BOX) {
				return Collision::BoxToBoxCollision(_min, _max, col->_min, col->_max);
			} else if (col->_type == CollisionType::SPEHERE) {
				return Collision::SphereToBoxCollision(col->_center, col->_radius, _min, _max);
			}
		} else if (_type == CollisionType::SPEHERE) {
			if (col->_type == CollisionType::BOX) {
				return Collision::SphereToBoxCollision(col->_center, col->_radius, _min, _max);
			} else if (col->_type == CollisionType::SPEHERE) {
				return Collision::SphereToSphereCollision(col->_center, col->_radius, _center, _radius);
			}
		}
		return false;
	}

	void Collision::setBoxCollision(glm::vec3 min, glm::vec3 max)
	{

	}

	void Collision::setSphereCollision(glm::vec3 center, float radius)
	{

	}

	bool Collision::SphereToSphereCollision(glm::vec3 center, float radius, glm::vec3 center2, float radius2)
	{
		return (glm::distance(center2, center) < (radius + radius2));
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