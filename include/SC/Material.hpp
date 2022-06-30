#pragma once 

#include <glm/glm.hpp>

namespace star {
namespace common {
	struct Material {
		Material() = default; 

		Material(glm::vec4 surfaceColor, glm::vec4 highlightColor, int shinyCoefficient) :
			surfaceColor(surfaceColor), highlightColor(highlightColor), shinyCoefficient(shinyCoefficient) { }

		glm::vec4 surfaceColor{0.5f, 0.5f, 0.5f, 1.0f};
		glm::vec4 highlightColor{ 0.5f, 0.5f, 0.5f, 1.0f };
		int shinyCoefficient = 1; 
	};
}
}