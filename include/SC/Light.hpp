#pragma once 

#include "Enums.h"
#include "Entity.hpp"

#include <glm/glm.hpp>

namespace star {
namespace common {
	class Light : public Entity{
	public:
		Light(common::Type::Light type) : Entity(), type(type) { }

		Light(Type::Light type, glm::vec3 position) : Entity(position), type(type) { }

		Light(Type::Light type, glm::vec3 position, glm::vec4 color) : Entity(position), type(type), color(color) { }
		
		Type::Light getType() { return this->type; }
		glm::vec4 getColor() { return this->color;  }

	protected:
		Type::Light type;
		glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f};

	private: 

	};
}
}