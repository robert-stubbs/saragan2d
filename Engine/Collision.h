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

	class Collision : public Component {

		private:
			CollisionType _type;

			// for box
			glm::vec3 _min;
			glm::vec3 _max;

			// for sphere
			glm::vec3 _center;
			float _radius;
			
			bool _render_collision;
			bool _loaded;
			std::string _shader_name;

			std::vector<vert2D> _verts;
			glm::vec4 _color;
			glm::vec4 _color_collide;
			unsigned int VAO;
			unsigned int VBO;

		public:
			Collision();
			virtual ~Collision();

			virtual bool Init() override;

			virtual void Update(float dt) override;

			virtual void Render() override;

			virtual void CleanUp() override;

			inline void SetRenderCollision(bool render) { _render_collision = render; }

			void setColors(glm::vec4 col = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f), glm::vec4 collision_col = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

			void GenerateSphereVerts();
			void UpdateSphereVerts(bool collide = false);

			bool doesCollide(Collision* col);
			void setBoxCollision(glm::vec3 min, glm::vec3 max);
			void setSphereCollision(glm::vec3 center, float radius);

			bool SphereToSphereCollision(glm::vec3 center, float radius, glm::vec3 center2, float radius2);
			bool SphereToBoxCollision(glm::vec3 center, float radius, glm::vec3 min, glm::vec3 max);
			bool BoxToBoxCollision(glm::vec3 min, glm::vec3 max, glm::vec3 min2, glm::vec3 max2);
	};
}

#endif