#pragma once 

#include "Enums.h"
#include "Entity.hpp"
#include "Handle.hpp"
#include "GameObject.hpp"

#include <glm/glm.hpp>

namespace star::common{
	class Light : public Entity{
	public:
		bool enabled		 = true; 
		Type::Light type	 = Type::Light::point;
		float diameter		 = 0.0f;
		glm::vec4 ambient	 = glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f };
		glm::vec4 diffuse	 = glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f };
		glm::vec4 specular	 = glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f };
		glm::vec4 direction	 = glm::vec4{0.0f, -1.0f, 0.0f, 0.0f};

		Light(Type::Light type, glm::vec3 position) : Entity(position) {
			this->type = type; 
		}

		//create light with no linked object
		Light(Type::Light type, glm::vec3 position, const glm::vec4& ambient, 
			const glm::vec4& diffuse, const glm::vec4& specular, 
			const glm::vec4* direction = nullptr, const float* cutoff = nullptr) 
			: Entity(position), type(type),
			ambient(ambient), diffuse(diffuse), 
			specular(specular)
		{
			if (direction != nullptr)
				this->direction = *direction; 
			if (cutoff != nullptr)
				this->diameter = *cutoff;
		}
		//create light with linked object
		Light(Type::Light type, glm::vec3 position, glm::vec3 scale,
			Handle linkedObjectHandle, GameObject& linkedObject, 
			const glm::vec4& ambient, const glm::vec4& diffuse,
			const glm::vec4& specular, const glm::vec4* direction = nullptr, const float* cutoff = nullptr) :
			Entity(position, scale), linkedObjectHandle(std::make_unique<Handle>(linkedObjectHandle)), 
			ambient(ambient), diffuse(diffuse),
			specular(specular), type(type)
		{
			if (direction != nullptr)
				this->direction = *direction; 
			if (cutoff != nullptr)
				this->diameter = *cutoff;
		}
		
		//check if the light has a linked render object
		bool hasObject(){
			if (this->linkedObjectHandle)
				return true;
			return false; 
		}

		virtual void moveRelative(const glm::vec3& movement) override {
			if (this->linkedObjectHandle) {
				this->linkedObject->moveRelative(movement);
			}
			this->Entity::moveRelative(movement);
		}

		virtual void setEnabled(const bool& state) {
			enabled = state; 
		}

		void setLinkedObjectHandle(Handle handle) { this->linkedObjectHandle = std::make_unique<Handle>(handle); }
		void setLinkedObject(GameObject& object) { this->linkedObject = &object; }
		Handle getLinkedObjectHandle() { return *this->linkedObjectHandle; }
		bool hasLinkedObject() {
			if (this->linkedObjectHandle)
				return true;
			else
				return false;
		}
		Type::Light getType() { return type; }
		glm::vec4 getAmbient() { return ambient; }
		glm::vec4 getDiffuse() { return diffuse; }
		glm::vec4 getSpecular() { return specular; }
	private:
		//handle to the object that will be rendered along with the light (positional object such as billboard)
		std::unique_ptr<Handle> linkedObjectHandle;
		GameObject* linkedObject = nullptr; 

	};
}