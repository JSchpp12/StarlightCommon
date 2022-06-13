#pragma once 

#include "Entity.hpp"
#include "Time.hpp"
#include "Handle.hpp"
#include "Vertex.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_cross_product.hpp>

#include <stb_image.h>

#include <queue>
#include <memory>

namespace star{
    namespace common{
        class Object : public Entity{
        public:
            Object(std::unique_ptr<std::vector<Vertex>> vertexList, std::unique_ptr<std::vector<uint32_t>> indiciesList,
                Handle& vertShaderHandle,
                Handle& fragShaderHandle,
                Handle& textureHandle) :
                Entity(), 
                vertexList(std::move(vertexList)),
                indiciesList(std::move(indiciesList)),
                vertShader(std::make_unique<Handle>(vertShaderHandle)),
                fragShader(std::make_unique<Handle>(fragShaderHandle)),
                texture(std::make_unique<Handle>(textureHandle)),
                relativeTranslation(std::make_unique<glm::vec3>(glm::vec3())), 
                scaleAmt(std::make_unique<glm::vec3>(glm::vec3{2.5f, 2.5f, 2.5f})),
                relativeRotationList(std::make_unique<std::queue<std::pair<const double, const glm::vec3>>>())
            {
                //auto tmpMatrix = *this->modelMatrix; 
                //this->displayMatrix = std::make_unique<glm::mat4>(glm::scale(*this->modelMatrix, *this->scaleAmt)); 
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

            glm::vec3 getScale() {
                return *this->scaleAmt;
            }

            void setScale(glm::vec3 scale) {
                this->scaleAmt = std::make_unique<glm::vec3>(scale); 
                this->displayMatrix = std::make_unique<glm::mat4>(glm::scale(*this->displayMatrix, scale)); 
            }

            //TODO: implement set position

            std::vector<Vertex>* getVerticies() { return this->vertexList.get(); }

            std::vector<uint32_t>* getIndicies() { return this->indiciesList.get(); }
        protected: 
            // virtual void Load(const std::string& filePath); 
            void updateModelMatrix() {
                glm::mat4 currentMatrix = *this->displayMatrix; 

                //apply scale 
                currentMatrix = glm::scale(currentMatrix, *this->scaleAmt);

                //apply rotation
                float radians; 
                std::pair<double, glm::vec3> rotationPair; 

                while (!this->relativeRotationList->empty()) {
                    rotationPair = this->relativeRotationList->front(); 


                    //TODO: this casts from float to double...possible data loss
                    radians = glm::radians(rotationPair.first); 

                    currentMatrix = glm::rotate(currentMatrix, radians, rotationPair.second); 

                    this->relativeRotationList->pop(); 
                }

                //apply translations

                currentMatrix = glm::translate(currentMatrix, *this->relativeTranslation); 
                this->displayMatrix = std::make_unique<glm::mat4>(currentMatrix);

                this->resetValues(); 
            }

            /// <summary>
            /// Reset any values that might have been changed
            /// </summary>
            void resetValues() {
                this->relativeTranslation = std::make_unique<glm::vec3>(0.f); 
            }

        private: 
            //is the mmodel matrix updated with most recent changes 
            bool modelMatrixValid = true; 

            //modelMatrix = translation * rotation * scale
            std::unique_ptr<glm::mat4> translationMatrix, rotationMatrix, scaleMatrix;
            std::unique_ptr<glm::vec3> relativeTranslation, scaleAmt; 
            std::unique_ptr<std::vector<Vertex>> vertexList; 
            std::unique_ptr<std::vector<uint32_t>> indiciesList; 
            std::unique_ptr<Handle> vertShader, fragShader, texture; 
            std::unique_ptr<std::queue<std::pair<const double, const glm::vec3>>> relativeRotationList; 

        };
    }
}