#pragma once 

//TODO: MOVE THIS INTO THE GAME ENGINE PROJ

#include "Entity.hpp"
#include "Time.hpp"
#include "Handle.hpp"
#include "Vertex.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_cross_product.hpp>

#include <stb_image.h>

#include <queue>
#include <memory>

namespace star{
    namespace common{
        class GameObject : public Entity{
        public:
            GameObject(std::unique_ptr<std::vector<Vertex>> vertexList, std::unique_ptr<std::vector<uint32_t>> indiciesList,
                glm::vec3 scale,
                Handle& vertShaderHandle,
                Handle& fragShaderHandle,
                Handle& textureHandle) :
                Entity(), 
                vertexList(std::move(vertexList)),
                indiciesList(std::move(indiciesList)),
                vertShader(std::make_unique<Handle>(vertShaderHandle)),
                fragShader(std::make_unique<Handle>(fragShaderHandle)),
                texture(std::make_unique<Handle>(textureHandle))
            {
                this->setScale(scale); 
            } 

            virtual ~GameObject() {}; 

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

            //glm::vec3 getScale() {
            //    return *this->scaleAmt;
            //}

            void setScale(glm::vec3 scale) {
                this->displayMatrix = std::make_unique<glm::mat4>(glm::scale(*this->displayMatrix, scale)); 
            }

            glm::mat4 getNormalMatrix() {
                return glm::inverseTranspose(*this->displayMatrix); 
            }

            //TODO: implement set position

            std::vector<Vertex>* getVerticies() { return this->vertexList.get(); }

            std::vector<uint32_t>* getIndicies() { return this->indiciesList.get(); }
        protected: 

        private: 
            //is the mmodel matrix updated with most recent changes 
            bool modelMatrixValid = true; 

            std::unique_ptr<Handle> vertShader, fragShader, texture; 
            std::unique_ptr<std::vector<common::Vertex>> vertexList;
            std::unique_ptr<std::vector<uint32_t>> indiciesList;
        };
    }
}