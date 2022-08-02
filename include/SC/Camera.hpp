#pragma once 
//right hand coordinate system 
//row-major notation 


#include "Entity.hpp"

#include <glm/glm.hpp>
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <memory>

//Note: this camera system will fail if the user looks up the +y-axis
namespace star::common{
		//Camera object which will be used during rendering
		class Camera
		{
		public:
			Camera() :
				lookDirection(std::make_unique<glm::vec3>(glm::vec3{ 0.f, 0.f, 0.f })),
				lookAtPoint(std::make_unique<glm::vec3>(glm::vec3{0.f, 0.5f, 0.f})), 
				upVector(std::make_unique<glm::vec3>(glm::vec3{ 0.0f, 1.0f, 0.0f })),
				forwardVector(std::make_unique<glm::vec3>(glm::vec3{0.f, 0.f, 0.f})), 
				fieldOfView(std::make_unique<float>(45.f)),
				nearClippingPlaneDistance(std::make_unique<float>(0.f)), 
				farClippingPlaneDistance(std::make_unique<float>(10.f))
			{
				//set look direction towards origin->				auto origin = glm::vec3(0.f); 
				this->setPosition(glm::vec3{ 0.f, 0.5f, 3.f });
			}


			virtual void setPosition(glm::vec3 newPosition) {
				this->position = std::make_unique<glm::vec3>(newPosition); 
				this->lookDirection = std::make_unique<glm::vec3>(glm::normalize(*this->lookAtPoint - *this->position));

				//compute right vector
				//use vec {0, 1, 0} as arbitrary vec for calculation 
				glm::vec3 tempArbVector{ 0.0f, 1.0f, 0.0f }; 
				this->rightVector = std::make_unique<glm::vec3>(glm::normalize(glm::cross(tempArbVector, *this->lookDirection))); 

				//compute up vector 
				this->upVector = std::make_unique<glm::vec3>(glm::cross(*this->lookDirection, *this->rightVector));
			}

			glm::vec3 getLookDirection() { return *this->lookDirection; };

			glm::vec3 getLookAtPoint() { return *this->lookAtPoint; };

			glm::vec3 getPosition() { return *this->position; };

			glm::mat4 getDisplayMatrix() {
				return glm::lookAt(
					*this->position,
					*this->position + (*this->lookDirection),
					*this->upVector
				);
			}

			glm::mat4 getInverseViewMatrix() {
				return glm::inverse(
					glm::lookAt(
						*this->position,
						*this->position + (*this->lookDirection),
						*this->upVector
					)
				);
			}

			void setLookDirection(glm::vec3 newLookPoint) {
				this->lookDirection = std::make_unique<glm::vec3>(newLookPoint); 
			}

			void moveRelative(glm::vec3 direction, float amt) {
				direction = glm::normalize(direction); 

				//update look at point with new movement
				auto lookAt = this->getLookAtPoint() + (direction * amt);
				this->lookAtPoint = std::make_unique<glm::vec3>(lookAt); 

				//update camera position
				auto position = *this->position + (direction * amt);
				this->setPosition(position); 
			}

		protected:
			std::unique_ptr<glm::vec3> lookDirection, lookAtPoint, upVector, forwardVector, rightVector, position;
			std::unique_ptr<float> fieldOfView;		//Field of view of the camera represented in degrees
			std::unique_ptr<float> nearClippingPlaneDistance, farClippingPlaneDistance;

		private:

		};
	}