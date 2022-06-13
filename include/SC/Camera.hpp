#pragma once 
//right hand coordinate system 
//row-major notation 

#include "Entity.hpp"
#include "Interactivity.hpp"
#include "Time.hpp"

#include <glm/glm.hpp>

#include <memory>

//Note: this camera system will fail if the user looks up the +y-axis
namespace star {
	namespace common {
		//Camera object which will be used during rendering
		class Camera : 
			public Entity, 
			public Interactivity
		{
		public:
			Camera() :
				Entity(),
				lookDirection(std::make_unique<glm::vec3>(glm::vec3{ 0.f, 0.f, 0.f })),
				lookAtPoint(std::make_unique<glm::vec3>(glm::vec3{0.f, 0.f, 0.f})), 
				upVector(std::make_unique<glm::vec3>(glm::vec3{ 0.0f, 1.0f, 0.0f })),
				forwardVector(std::make_unique<glm::vec3>(glm::vec3{0.f, 0.f, 0.f})), 
				fieldOfView(std::make_unique<float>(45.f)),
				nearClippingPlaneDistance(std::make_unique<float>(0.f)), 
				farClippingPlaneDistance(std::make_unique<float>(10.f))
			{
				//set look direction towards origin->				auto origin = glm::vec3(0.f); 
				this->setPosition(glm::vec3{ 2.f, 2.f, 2.f });
			}


			virtual void setPosition(glm::vec3 newPosition) override {
				this->position = std::make_unique<glm::vec3>(newPosition); 
				this->lookDirection = std::make_unique<glm::vec3>(glm::normalize(*this->lookAtPoint - *this->position));
				//this->lookDirection = std::make_unique<glm::vec3>(glm::vec3(0.0f, 0.0f, -1.0f)); 

				//compute right vector
				//use vec {0, 1, 0} as arbitrary vec for calculation 
				glm::vec3 tempArbVector{ 0.0f, 1.0f, 0.0f }; 
				glm::vec3 right = glm::normalize(glm::cross(tempArbVector, *this->lookDirection)); 

				//compute up vector 
				this->upVector = std::make_unique<glm::vec3>(glm::cross(*this->lookDirection, right));

				this->displayMatrix = std::make_unique<glm::mat4>(glm::lookAt(
					*this->position, 
					*this->position + (*this->lookDirection),
					*this->upVector
				));
			}

			glm::vec3 getLookDirection() { return *this->lookDirection; };

			glm::vec3 getLookAtPoint() { return *this->lookAtPoint; };

			void setLookDirection(glm::vec3 newLookPoint) {
				this->lookDirection = std::make_unique<glm::vec3>(newLookPoint); 
			}

			void moveRelative(glm::vec3 direction, float amt) override {
				direction = glm::normalize(direction); 

				//update look at point with new movement
				auto lookAt = this->getLookAtPoint() + (direction * amt);
				this->lookAtPoint = std::make_unique<glm::vec3>(lookAt); 

				//update camera position
				auto position = this->getPosition() + (direction * amt);
				this->setPosition(position); 
			}


			/// <summary>
			/// Key callback for camera object. Implements default controls for the camera. 
			/// </summary>
			/// <param name="key"></param>
			/// <param name="scancode"></param>
			/// <param name="action"></param>
			/// <param name="mods"></param>
			virtual void keyCallback(int key, int scancode, int action, int mods) override {
				float moveAmt = 0.5f;
				if (action == GLFW_PRESS) {
					glm::vec3 cameraPos = this->getPosition(); 
					glm::vec3 cameraLookDir = -this->getLookDirection();

					if (key == GLFW_KEY_W) { 
						this->moveRelative(*this->lookDirection, moveAmt); 
					}
					if (key == GLFW_KEY_S) {
						//cameraPos -= moveAmt * cameraLookDir;
						//this->setPosition(cameraPos);
						this->moveRelative(-*this->lookDirection, moveAmt); 
					}
					if (key == GLFW_KEY_A) {
						this->moveRelative(glm::cross(cameraLookDir, *this->upVector), moveAmt); 
						//cameraPos -= glm::normalize(glm::cross(cameraLookDir, *this->upVector)) * moveAmt; 
						//this->setPosition(cameraPos);
					}
					if (key == GLFW_KEY_D) {
						this->moveRelative(glm::cross(cameraLookDir, -*this->upVector), moveAmt);
					}
					std::cout << cameraPos.x << "," << cameraPos.y << "," << cameraPos.z << std::endl;
				}
			};

			/// <summary>
			/// Mouse callback for camera objects. Implements default controls for the camera. 
			/// </summary>
			/// <param name="xpos"></param>
			/// <param name="ypos"></param>
			virtual void mouseMovementCallback(double xpos, double ypos) override {
				std::cout << "mouse movement on camera" << std::endl; 
			};

		protected:


		private:
			std::unique_ptr<glm::vec3> lookDirection, lookAtPoint, upVector, forwardVector; 
			std::unique_ptr<float> fieldOfView;		//Field of view of the camera represented in degrees
			std::unique_ptr<float> nearClippingPlaneDistance, farClippingPlaneDistance;
		};
	}
}