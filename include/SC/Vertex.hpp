#pragma once 

#include <glm/glm.hpp>

namespace star::common{
    class Vertex {
    public: 
        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec3 color; 
        glm::vec2 texCoord;
        glm::vec3 aTangent; 
        glm::vec3 aBitangent; 
        //material inforamtion
        glm::vec3 matAmbient = glm::vec3{0.0f, 0.0f, 0.0f};
        glm::vec3 matDiffuse = glm::vec3{0.0f, 0.0f, 0.0f};
        glm::vec3 matSpecular = glm::vec3{ 0.0f, 0.0f, 0.0f }; 
        float matShininess = 1.0f; 
            
    private: 

    };
}