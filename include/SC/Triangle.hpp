#pragma once 
#include "Vertex.hpp"
#include "Handle.hpp"

#include <glm/glm.hpp>

#include <array>

namespace star::common {
	struct Triangle {
		Triangle() = default; 
		Triangle(std::array<Vertex, 3> v) : verticies(v) { }

		std::array<Vertex, 3> verticies; 
		Handle material; 
	};
}