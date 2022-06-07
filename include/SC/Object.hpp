#pragma once 

#include "Handle.hpp"
#include "Vertex.hpp"

#include <glm/glm.hpp>
#include <stb_image.h>

#include <vector> 
#include <memory>

namespace star{
    namespace common{
        class Object {
        public:
            Object(std::unique_ptr<std::vector<Vertex>> vertexList, std::unique_ptr<std::vector<uint32_t>> indiciesList,
                Handle& vertShaderHandle,
                Handle& fragShaderHandle, 
                Handle& textureHandle) :
            vertexList(std::move(vertexList)), 
            indiciesList(std::move(indiciesList)), 
            vertShader(std::make_unique<Handle>(vertShaderHandle)),
            fragShader(std::make_unique<Handle>(fragShaderHandle)), 
            texture(std::make_unique<Handle>(textureHandle))
            {
            } 

            virtual ~Object() {}; 

            //get the handle for the vertex shader 
            Handle getVertShader() {
                return *this->vertShader.get(); 
            }

            //get the handle for the fragment shader
            Handle getFragShader() {
                return *this->fragShader.get();
            }

            Handle getTexture() {
                return *this->texture.get(); 
            }

            std::vector<Vertex>* getVerticies() { return this->vertexList.get(); }

            std::vector<uint32_t>* getIndicies() { return this->indiciesList.get(); }
        protected: 
            // virtual void Load(const std::string& filePath); 

        private: 
            glm::mat4 modelMatrix; 
            std::unique_ptr<std::vector<Vertex>> vertexList; 
            std::unique_ptr<std::vector<uint32_t>> indiciesList; 
            std::unique_ptr<Handle> vertShader, fragShader, texture; 

        };
    }
}