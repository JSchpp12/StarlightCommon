#pragma once 

#include "Enums.h"
#include "Entity.hpp"
#include "Handle.hpp"
#include "GameObject.hpp"

#include <glm/glm.hpp>

namespace star {
namespace common {
	class Light : public Entity{
	public:
		Light(common::Type::Light type) : Entity(), type(type) { }

		Light(Type::Light type, glm::vec3 position) : Entity(position), type(type) { }

		Light(Type::Light type, glm::vec3 position, glm::vec4 color) : Entity(position), type(type), color(color) { }

		Light(Type::Light type, glm::vec3 position, glm::vec4 color, 
			glm::vec3 scale) : Entity(position) {}

		Light(Type::Light type, glm::vec3 position, glm::vec4 color,
			glm::vec3 scale, common::Handle linkedObjectHandle,
			common::GameObject* linkedObject) : 
			Entity(position, scale), type(type), 
			color(color), linkedObjectHandle(std::make_unique<common::Handle>(linkedObjectHandle)), 
			linkedObject(linkedObject) { }
		
		//check if the light has a linked render object
		bool hasObject(){
			if (this->linkedObjectHandle)
				return true;
			return false; 
		}

		virtual void moveRelative(glm::vec3 movement) override {
			if (this->linkedObjectHandle) {
				this->linkedObject->moveRelative(movement);
			}
			this->Entity::moveRelative(movement);
		}

		void setLinkedObjectHandle(common::Handle handle) { this->linkedObjectHandle = std::make_unique<common::Handle>(handle); }
		void setLinkedObject(common::GameObject* object) { this->linkedObject = object; }
		common::Handle getLinkedObjectHandle() { return *this->linkedObjectHandle; }
		Type::Light getType() { return this->type; }
		glm::vec4 getColor() { return this->color; }

	private:
		//handle to the object that will be rendered along with the light (positional object such as billboard)
		std::unique_ptr<common::Handle> linkedObjectHandle;
		common::GameObject* linkedObject = nullptr; 

		Type::Light type;
		glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f};

	};
}
}