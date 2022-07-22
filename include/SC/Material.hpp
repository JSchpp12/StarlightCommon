#pragma once 
#include "Handle.hpp"
#include "Enums.h"

#include <glm/glm.hpp>

#include <memory>

namespace star::common{
	struct Material {
	public:
		Material() = default; 
		Material(const glm::vec4& surfaceColor, const glm::vec4& highlightColor, const glm::vec4& ambient,
			const glm::vec4& diffuse, const glm::vec4& specular, 
			const int& shiny) : 
			surfaceColor(surfaceColor), highlightColor(highlightColor), 
			ambient(ambient), diffuse(diffuse), 
			specular(specular), shinyCoefficient(shiny) { }

		Material(const glm::vec4& surfaceColor, const glm::vec4& highlightColor, const glm::vec4& ambient, 
			const glm::vec4& diffuse, const glm::vec4& specular, 
			const int& shiny, const common::Handle& textureHandle, const common::Handle& bumpHandle) :
			surfaceColor(surfaceColor), highlightColor(highlightColor),
			ambient(ambient), diffuse(diffuse),
			specular(specular), shinyCoefficient(shiny), texture(textureHandle), bumpMap(bumpHandle) { }

		glm::vec4 surfaceColor{0.5f, 0.5f, 0.5f, 1.0f};
		glm::vec4 highlightColor{ 0.5f, 0.5f, 0.5f, 1.0f };
		glm::vec4 ambient{ 0.5f, 0.5f, 0.5f, 1.0f }; 
		glm::vec4 diffuse{ 0.5f, 0.5f, 0.5f, 1.0f };
		glm::vec4 specular{ 0.5f, 0.5f, 0.5f, 1.0f }; 
		int shinyCoefficient = 1; 
		Handle texture = Handle::getDefault();
		Handle bumpMap = Handle::getDefault(); 

	protected:
		
	private: 

	};
}