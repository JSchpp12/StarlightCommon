#pragma once 
#include "Vertex.hpp"
#include "Material.hpp"

#include <glm/glm.hpp>

#include <array>

namespace star::common {
	struct Triangle {
		Triangle();

		Vertex verticies[]; 
		
	};
}