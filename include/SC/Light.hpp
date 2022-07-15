#pragma once 

#include "Enums.h"
#include "Entity.hpp"
#include "Handle.hpp"
#include "GameObject.hpp"

#include <glm/glm.hpp>

namespace star::common{
	class Light : public Entity{
	public:
		Light(Type::Light type, glm::vec3 position) : Entity(position) {
			this->type = type; 
		}

		//create light with no linked object
		Light(Type::Light type, glm::vec3 position, const glm::vec4* ambient = nullptr, 
			const glm::vec4* diffuse = nullptr, const glm::vec4* specular = nullptr) 
			: Entity(position){ 
			this->type = type; 
			if (ambient != nullptr)
				this->ambient = *ambient; 
			if (diffuse != nullptr)
				this->diffuse = *diffuse; 
			if (specular != nullptr)
				this->specular = *specular; 
		}
		//create light with linked object
		Light(Type::Light type, glm::vec3 position, glm::vec3 scale,
			Handle linkedObjectHandle, GameObject& linkedObject, 
			const glm::vec4* ambient = nullptr, const glm::vec4* diffuse = nullptr,
			const glm::vec4* specular = nullptr) :
			Entity(position, scale), linkedObjectHandle(std::make_unique<Handle>(linkedObjectHandle)) {
			this->type = type;
			this->linkedObject = &linkedObject;
			if (ambient != nullptr)
				this->ambient = *ambient; 
			if (diffuse != nullptr)
				this->diffuse = *diffuse; 
			if (specular != nullptr)
				this->specular = *specular; 
		}
		
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

		void setLinkedObjectHandle(Handle handle) { this->linkedObjectHandle = std::make_unique<Handle>(handle); }
		void setLinkedObject(GameObject& object) { this->linkedObject = &object; }
		Handle getLinkedObjectHandle() { return *this->linkedObjectHandle; }
		Type::Light getType() { return this->type; }
		glm::vec4 getAmbient() { return this->ambient; }
		glm::vec4 getDiffuse() { return this->diffuse; }
		glm::vec4 getSpecular() { return this->specular; }

	private:
		//handle to the object that will be rendered along with the light (positional object such as billboard)
		std::unique_ptr<Handle> linkedObjectHandle;
		GameObject* linkedObject = nullptr; 

		Type::Light type;
		glm::vec4 ambient = glm::vec4{0.5f, 0.5f, 0.5f, 1.0f};
		glm::vec4 diffuse = glm::vec4{0.5f, 0.5f, 0.5f, 1.0f};
		glm::vec4 specular = glm::vec4{0.5f, 0.5f, 0.5f, 1.0f};

	};
}