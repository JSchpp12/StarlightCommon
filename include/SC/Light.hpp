#pragma once 

#include "Enums.h"
#include "Entity.hpp"
#include "Handle.hpp"
#include "GameObject.hpp"

#include <glm/glm.hpp>

namespace star::common{
	class Light : public Entity{
	public:
		Type::Light type		= Type::Light::point;
		glm::vec4 ambient		= glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f };
		glm::vec4 diffuse		= glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f };
		glm::vec4 specular		= glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f };
		glm::vec4 direction		= glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f };

		Light(Type::Light type, glm::vec3 position) : Entity(position) {
			this->type = type; 
		}

		//create light with no linked object
		Light(Type::Light type, glm::vec3 position, const glm::vec4& ambient, 
			const glm::vec4& diffuse, const glm::vec4& specular, 
			const glm::vec4* direction = nullptr, const float* innerCutoff = nullptr, 
			const float* outerCutoff = nullptr) 
			: Entity(position), type(type),
			ambient(ambient), diffuse(diffuse), 
			specular(specular)
		{
			if (direction != nullptr)
				this->direction = *direction; 
			if (innerCutoff != nullptr)
				innerDiameter = *innerCutoff;
			if (outerCutoff != nullptr)
				outerDiameter = *outerCutoff;
		}
		//create light with linked object
		Light(Type::Light type, glm::vec3 position, glm::vec3 scale,
			Handle linkedObjectHandle, GameObject& linkedObject, 
			const glm::vec4& ambient, const glm::vec4& diffuse,
			const glm::vec4& specular, const glm::vec4* direction = nullptr, 
			const float* innerCutoff = nullptr, const float* outerCutoff = nullptr) :
			Entity(position, scale), linkedObjectHandle(std::make_unique<Handle>(linkedObjectHandle)), 
			ambient(ambient), diffuse(diffuse),
			specular(specular), type(type)
		{
			if (direction != nullptr)
				this->direction = *direction; 
			if (innerCutoff != nullptr)
				innerDiameter = *innerCutoff;
			if (outerCutoff != nullptr)
				outerDiameter = *outerCutoff;
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

		/// <summary>
		/// Turn the light off or on. Default behavior is to simply switch the light status.
		/// </summary>
		/// <param name="state">the state to set the light to. If none is provided, default state is used</param>
		virtual void setEnabled(const bool* state = nullptr){
			if (state != nullptr) {
				enabled = *state; 
			}
			else {
				//flip value
				enabled = !enabled; 
			}
		}

		virtual void setInnerDiameter(const float& amt) {
			//inner diameter must always be less than outer diameter and greater than 0 
			if (amt < outerDiameter && amt > 0) {
				innerDiameter = amt; 
			}
		}

		virtual void setOuterDiameter(const float& amt) {
			//outer diamater must always be greater than inner diameter 
			if (amt > innerDiameter) {
				outerDiameter = amt; 
			}
		}

		/// <summary>
		/// Calculate the view matrix for this light source. Used when the light is being used as a shadow caster
		/// </summary>
		virtual glm::mat4 getViewMatrix() {
			assert(direction != glm::vec4( 0.0f, 1.0f, 0.0f, 0.0f) && "The light cannot be pointed in the same direction as the arb vector in calculations.");
			glm::vec3 tmpArbVector{ 0.0f, 0.0f, 1.0f };
			glm::vec3 minDirection = glm::vec3(this->direction);
			auto rightVector = glm::normalize(glm::cross(tmpArbVector, minDirection));

			auto upVector = glm::normalize(glm::cross(minDirection, rightVector));

			return glm::lookAt(
				type == Type::directional ? glm::normalize(- minDirection) * glm::vec3(3.0f) : this->positionCoords,
				type == Type::directional ? minDirection : this->positionCoords + minDirection, 
				upVector
			);
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
		bool getEnabled() { return enabled; }
		Type::Light getType() { return type; }
		glm::vec4 getAmbient() { return ambient; }
		glm::vec4 getDiffuse() { return diffuse; }
		glm::vec4 getSpecular() { return specular; }
		float getInnerDiameter() { return innerDiameter; }
		float getOuterDiameter() { return outerDiameter; }
	private:
		//handle to the object that will be rendered along with the light (positional object such as billboard)
		std::unique_ptr<Handle> linkedObjectHandle;
		GameObject* linkedObject = nullptr; 
		float innerDiameter = 0.0f;
		float outerDiameter = 1.0f;
		bool enabled = true;

	};
}