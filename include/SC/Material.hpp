#pragma once 
#include "Handle.hpp"
#include "Enums.h"

#include <glm/glm.hpp>

#include <memory>

namespace star {
namespace common {
	class Material {
	public:
		Material() = default; 
		Material(glm::vec4 surfaceColor, glm::vec4 highlightColor, int shinyCoefficient) :
			surfaceColor(surfaceColor), highlightColor(highlightColor), shinyCoefficient(shinyCoefficient){ }

		Material(glm::vec4 surfaceColor, glm::vec4 highlightColor, int shinyCoefficient, Handle texture) :
			surfaceColor(surfaceColor), highlightColor(highlightColor), shinyCoefficient(shinyCoefficient){
			this->texture = texture; 
		}

		glm::vec4 surfaceColor{0.5f, 0.5f, 0.5f, 1.0f};
		glm::vec4 highlightColor{ 0.5f, 0.5f, 0.5f, 1.0f };
		int shinyCoefficient = 1; 
		Handle texture = common::Handle{0, Handle_Type::texture};

	protected:

		
	private: 


	};
}
}