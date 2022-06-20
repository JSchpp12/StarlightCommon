#pragma once 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <memory>

namespace star {
	namespace common {
		class Entity {
		public:
			Entity() : 
				position(std::make_unique<glm::vec3>(glm::vec4(0.f))), 
				displayMatrix(std::make_unique<glm::mat4>(glm::mat4(1.f)))
			{
			}

			virtual void setPosition(glm::vec3 newPosition) {
				glm::mat4 identity = glm::mat4(1.f); 

				this->displayMatrix = std::make_unique<glm::mat4>(glm::translate(identity, newPosition));
				this->position = std::make_unique<glm::vec3>(newPosition); 
			}

			glm::vec3 getPosition() {
				glm::mat4 matrixCopy = *this->displayMatrix;
				return glm::vec3{ matrixCopy[3][0], matrixCopy[3][1], matrixCopy[3][2] }; 
			};

			/// <summary>
			/// Calculate what the current model matrix is 
			/// </summary>
			/// <returns></returns>
			glm::mat4 getDisplayMatrix() {
				return *this->displayMatrix;

			}

			/// <summary>T
			/// Apply translation to object's current position vector and update accordingly
			/// </summary>
			/// <param name="movement"></param>
			virtual void moveRelative(glm::vec3 movement) {
				//need to update model matrix before applying further translations
				this->displayMatrix = std::make_unique<glm::mat4>(glm::translate(*this->displayMatrix, movement));
			}

			/// <summary>
			/// Move entity in a direction defined by a normalized direction vector. 
			/// </summary>
			/// <param name="movementDirection">Movement direction vector. Will be normalized.</param>
			/// <param name="movementAmt">Ammount to move the entity by</param>
			virtual void moveRelative(glm::vec3 movementDirection, float movementAmt) {
				auto normMove = glm::normalize(movementDirection); 
				glm::vec3 movement = glm::vec3{
					normMove.x * movementAmt, 
					normMove.y * movementAmt, 
					normMove.z * movementAmt
				};

				this->displayMatrix = std::make_unique<glm::mat4>(glm::translate(*this->displayMatrix, movement));
			}

			/// <summary>
			/// Rotate object relative to object's coordinate system
			/// </summary>
			/// <param name="amt">Ammount of rotation to apply</param>
			/// <param name="rotationVector">Vector around which to apply rotation</param>
			/// <param name="inDegrees">Is the amount provided in degrees</param>
			void rotateRelative(float amt, glm::vec3 rotationVector, bool inDegrees = true) {
				float radians;
				if (inDegrees) {
					radians = glm::radians(amt);
				}
				else {
					radians = amt;
				}

				//might want to normalize vector
				glm::normalize(rotationVector);

				this->displayMatrix = std::make_unique<glm::mat4>(glm::rotate(*this->displayMatrix, radians, rotationVector));
			}

		protected:
			std::unique_ptr<glm::vec3> position;
			std::unique_ptr<glm::mat4> displayMatrix;

		private:

		};
	}
}