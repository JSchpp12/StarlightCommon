#pragma once

#include <glm/glm.hpp>

#include <iostream>

namespace star::common {
	class DebugHelpers {
	public:
		static void print(const glm::vec3& vector) {
			std::cout << vector.x << " , " << vector.y << " , " << vector.z << std::endl;	
		}
	};
}