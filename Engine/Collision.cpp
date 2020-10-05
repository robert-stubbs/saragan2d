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

		_update = false;
		_loaded = false;
		_has_collided = false;
		_render_collision = false;
		_shader_name = "DEFAULT2D";
	}

	Collision::~Collision()
	{
		if (e) {
			e = nullptr;
		}

		CleanUp();
	}

	bool Collision::Init()
	{
		return true;
	}

	void Collision::Update(float dt)
	{
		UpdateVerts();
	}

	void Collision::Render() 
	{
		if (_render_collision)
		{
			if (!_loaded) {
				if (_type == CollisionType::BOX) {
					GenerateBoxVerts();
				} else if (_type == CollisionType::SPEHERE) {
					GenerateSphereVerts();
				}
			}

			if (_loaded) {
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

		Shader& s = Engine::getShader()[_shader_name];

		Engine::getRenderer().GenerateVertexArrayBuffer(VAO);
		Engine::getRenderer().GenerateEmptyBuffer(VBO, ((int)_verts.size() + 1) * sizeof(vert2D));

		// When doing Dynamic - before creating initial buffer we need to bind the structure
		s.BindShaderStructure();

		Engine::getRenderer().BufferSubData(VBO, _verts);

		Engine::getRenderer().UnbindBuffer();
		Engine::getRenderer().UnbindVertexBuffer();

		_loaded = true;
		_update = false;
	}

	void Collision::GenerateBoxVerts()
	{
		_verts.clear();

		_verts.push_back({ { _min.x, _min.y, _min.z,1.0f }, { -99.0f, -99.0f }, {_color.r, _color.g, _color.b, _color.a } });
		_verts.push_back({ { _min.x, _max.y, _min.z,1.0f }, { -99.0f, -99.0f }, {_color.r, _color.g, _color.b, _color.a } });
		_verts.push_back({ { _max.x, _max.y, _max.z,1.0f }, { -99.0f, -99.0f }, {_color.r, _color.g, _color.b, _color.a } });
		_verts.push_back({ { _max.x, _min.y, _max.z,1.0f }, { -99.0f, -99.0f }, {_color.r, _color.g, _color.b, _color.a } });

		Shader& s = Engine::getShader()[_shader_name];

		Engine::getRenderer().GenerateVertexArrayBuffer(VAO);
		Engine::getRenderer().GenerateEmptyBuffer(VBO, ((int)_verts.size() + 1) * sizeof(vert2D));

		// When doing Dynamic - before creating initial buffer we need to bind the structure
		s.BindShaderStructure();

		Engine::getRenderer().BufferSubData(VBO, _verts);

		Engine::getRenderer().UnbindBuffer();
		Engine::getRenderer().UnbindVertexBuffer();

		_loaded = true;
		_update = false;
	}

	void Collision::UpdateVerts()
	{
		_selected_color = _has_collided ? _color_collide : _color;

		if (_selected_color != _current_color) {
			_current_color = _selected_color;

			for (int i = 0; i < (int)_verts.size(); i++)
			{
				vert2D& v = _verts[i];
				v.col[0] = _current_color.r;
				v.col[1] = _current_color.g;
				v.col[2] = _current_color.b;
				v.col[3] = _current_color.a;
			}

			Engine::getRenderer().BufferSubData(VBO, _verts);
		}
	}

	void Collision::setBoxCollision(glm::vec3 min, glm::vec3 max, CollisionEvent eventType)
	{
		_min = min;
		_max = max;
		_type = CollisionType::BOX;
		_eventType = eventType;
	}

	void Collision::setSphereCollision(glm::vec3 center, float radius, CollisionEvent eventType)
	{
		_center = center;
		_radius = radius;
		_type = CollisionType::SPEHERE;
		_eventType = eventType;
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
		if (!_render_collision || (_render_collision && _loaded)) {

			glm::vec3 worldpos = GetCollisionWorldPos();
			glm::vec3 worldpos2 = col->GetCollisionWorldPos();

			if (_type == CollisionType::BOX) {
				if (col->_type == CollisionType::BOX) {
					return BoxToBoxCollision(_min + worldpos, _max + worldpos, col->_min + worldpos2, col->_max + worldpos2);
				}
				else if (col->_type == CollisionType::SPEHERE) {
					return SphereToBoxCollision(worldpos2 + col->_center, col->_radius, _min + worldpos, _max + worldpos);
				}
			}
			else if (_type == CollisionType::SPEHERE) {
				if (col->_type == CollisionType::BOX) {
					return SphereToBoxCollision(worldpos + _center, _radius, col->_min + worldpos2, col->_max + worldpos2);
				}
				else if (col->_type == CollisionType::SPEHERE) {
					return SphereToSphereCollision(worldpos2 + col->_center, col->_radius, worldpos + _center, _radius);
				}
			}
		}
		return false;
	}

	bool Collision::SphereToSphereCollision(glm::vec3 center, float radius, glm::vec3 center2, float radius2)
	{
		float dist = glm::distance(center2, center);
		float rad = radius + radius2;
		_has_collided = (dist < rad);

		return _has_collided;
	}

	bool Collision::SphereToBoxCollision(glm::vec3 center, float radius, glm::vec3 min, glm::vec3 max)
	{
		// Compute squared distance between sphere center and AABB
		// the sqrt(dist) is fine to use as well, but this is faster.
		float sqDist = SqDistPointAABB(center, min, max);

		_has_collided = sqDist <= radius * radius;
		// Sphere and AABB intersect if the (squared) distance between them is
		// less than the (squared) sphere radius.
		return _has_collided;
	}

	float Collision::SqDistPointAABB(glm::vec3 p, glm::vec3 min, glm::vec3 max)
	{
		float sqDist = 0.0f;

		// x val
		if (p.x < min.x) sqDist += (min.x - p.x) * (min.x - p.x);
		if (p.x > max.x) sqDist += (p.x - max.x) * (p.x - max.x);

		// y val
		if (p.y < min.y) sqDist += (min.y - p.y) * (min.y - p.y);
		if (p.y > max.y) sqDist += (p.y - max.y) * (p.y - max.y);

		// z val
		if (p.z < min.z) sqDist += (min.z - p.z) * (min.z - p.z);
		if (p.z > max.z) sqDist += (p.z - max.z) * (p.z - max.z);

		return sqDist;
	}

	bool Collision::BoxToBoxCollision(glm::vec3 min, glm::vec3 max, glm::vec3 min2, glm::vec3 max2)
	{
		_has_collided = false;

		if (min.x < max2.x &&
			max.x > min2.x &&
			min.y < max2.y &&
			max.y > min2.y) {
			// collision detected!
			_has_collided = true;
		}
		return _has_collided;
	}

}