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
			const int& shiny, common::Handle& textureHandle) :
			surfaceColor(surfaceColor), highlightColor(highlightColor),
			ambient(ambient), diffuse(diffuse),
			specular(specular), shinyCoefficient(shiny){
			this->texture = textureHandle;
		}

		glm::vec4 surfaceColor{0.5f, 0.5f, 0.5f, 1.0f};
		glm::vec4 highlightColor{ 0.5f, 0.5f, 0.5f, 1.0f };
		glm::vec4 ambient{ 0.5f, 0.5f, 0.5f, 1.0f }; 
		glm::vec4 diffuse{ 0.5f, 0.5f, 0.5f, 1.0f };
		glm::vec4 specular{ 0.5f, 0.5f, 0.5f, 1.0f }; 
		int shinyCoefficient = 1; 
		Handle texture = Handle{0, Handle_Type::texture};

	protected:

		
	private: 


	};
}