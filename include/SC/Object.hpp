#pragma once 

#include "Handle.hpp"
#include "Vertex.hpp"

#include <glm/glm.hpp>
#include <stb_image.h>

#include <vector> 

namespace star{
    namespace common{
        class Object {
        public: 
            // static Entity& New(const std::string& filePath, common::Handle vertShader, common::Handle fragShader); 
            // static Object& New(const std::string& filePath); 

            Object(std::unique_ptr<std::vector<Vertex>> vertexList, std::unique_ptr<std::vector<uint16_t>> indiciesList) : 
            vertexList(std::move(vertexList)), 
            indiciesList(std::move(indiciesList))
            {
            } 

        protected: 
            // virtual void Load(const std::string& filePath); 


        private: 
            glm::mat4 modelMatrix; 
            std::unique_ptr<std::vector<Vertex>> vertexList; 
            std::unique_ptr<std::vector<uint16_t>> indiciesList; 

        };
    }
}