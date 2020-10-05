#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Component.h"
#include "Types.h"

namespace GameEngine
{
	enum class CollisionType {
		BOX = 0,
		SPEHERE
	};

	enum class CollisionEvent {
		BLOCKING = 0,
		OVERLAP
	};

	class Collision : public Component {

		private:
			CollisionType _type;
			CollisionEvent _eventType;

			// for box
			glm::vec3 _min;
			glm::vec3 _max;

			// for sphere
			glm::vec3 _center;
			float _radius;
			
			bool _update;

			std::string _shader_name;

			std::vector<vert2D> _verts;
			glm::vec4 _color;
			glm::vec4 _color_collide;
			glm::vec4 _current_color;
			glm::vec4 _selected_color;

			unsigned int VAO;
			unsigned int VBO;

		public:

			bool _has_collided;
			bool _render_collision;
			bool _loaded;

			Collision();
			virtual ~Collision();

			virtual bool Init() override;

			virtual void Update(float dt) override;

			virtual void Render() override;

			virtual void CleanUp() override;

			void setColors(glm::vec4 col = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f), glm::vec4 collision_col = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

			void GenerateSphereVerts();
			void GenerateBoxVerts();

			void UpdateVerts();

			inline void SetRenderCollision(bool render) { _render_collision = render; }
			inline CollisionEvent GetCollisionType() { return _eventType; }

			void setBoxCollision(glm::vec3 min, glm::vec3 max, CollisionEvent eventType = CollisionEvent::BLOCKING);
			void setSphereCollision(glm::vec3 center, float radius, CollisionEvent eventType = CollisionEvent::BLOCKING);

			glm::vec3 GetCollisionWorldPos();

			bool doesCollide(Collision* col);
			bool SphereToSphereCollision(glm::vec3 center, float radius, glm::vec3 center2, float radius2);
			bool SphereToBoxCollision(glm::vec3 center, float radius, glm::vec3 min, glm::vec3 max);
			bool BoxToBoxCollision(glm::vec3 min, glm::vec3 max, glm::vec3 min2, glm::vec3 max2);

			// Returns the squared distance between a point p and an AABB b
			float SqDistPointAABB(glm::vec3 p, glm::vec3 min, glm::vec3 max);
	};
}

#endif