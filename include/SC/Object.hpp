#pragma once 

#include "SC/Time.hpp"
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
                texture(std::make_unique<Handle>(textureHandle)),
                translationMatrix(std::make_unique<glm::mat4>(glm::identity<glm::mat4>())),
                rotationMatrix(std::make_unique<glm::mat4>(glm::identity<glm::mat4>())),
                modelMatrix(std::make_unique<glm::mat4>(glm::identity<glm::mat4>())), 
                position(std::make_unique<glm::vec4>(glm::vec4{0.f, 0.f, 0.f, 1.f})),
                relativeTranslation(std::make_unique<glm::vec3>(glm::vec3())), 
                scaleAmt(std::make_unique<glm::vec3>(glm::vec3{1.f, 1.f, 1.f})),
                relativeRotationList(std::make_unique<std::queue<std::pair<const double, const glm::vec3>>>())
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

            //glm::mat4 getModelMatrix() {
            //    return *this->modelMatrix; 
            //};

            glm::vec4 getPosition() {
                return *this->position; 
            };

            //TODO: implement set position

            /// <summary>
            /// Apply translation to object's current position matrix and update accordingly
            /// </summary>
            /// <param name="movement"></param>
            void moveRelative(glm::vec3 movement) {
                //need to update model matrix before applying further translations
                if (!this->modelMatrixValid) {
                    this->updateModelMatrix(); 
                }

                glm::mat4 tempMatrix = *this->modelMatrix; 
                this->modelMatrix = std::make_unique<glm::mat4>(glm::translate(tempMatrix, movement));
                this->position = std::make_unique<glm::vec4>(glm::vec4{
                    this->position->x + movement.x, 
                    this->position->y + movement.y, 
                    this->position->z + movement.z,
                    1.0f
                });
            }

            void rotateRelative(float amtDegrees, glm::vec3 rotationVector, bool inDegrees = true) {
                float radians; 
                if (inDegrees) {
                    radians = glm::radians(amtDegrees); 
                }
                else {
                    radians = amtDegrees; 
                }

                //might want to normalize vector
                glm::normalize(rotationVector); 

                this->modelMatrix = std::make_unique<glm::mat4>(glm::rotate(*this->modelMatrix, radians, rotationVector)); 
            }

            /// <summary>
            /// Calculate what the current model matrix is 
            /// </summary>
            /// <returns></returns>
            glm::mat4 getModelMatrix() {
                return *this->modelMatrix;

            }

            std::vector<Vertex>* getVerticies() { return this->vertexList.get(); }

            std::vector<uint32_t>* getIndicies() { return this->indiciesList.get(); }
        protected: 
            // virtual void Load(const std::string& filePath); 
            void updateModelMatrix() {
                glm::mat4 currentMatrix = *this->modelMatrix; 

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
                this->modelMatrix = std::make_unique<glm::mat4>(currentMatrix);

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
            std::unique_ptr<glm::mat4> translationMatrix, rotationMatrix, scaleMatrix, modelMatrix;
            std::unique_ptr<glm::vec4> position;
            std::unique_ptr<glm::vec3> relativeTranslation, scaleAmt; 
            std::unique_ptr<std::vector<Vertex>> vertexList; 
            std::unique_ptr<std::vector<uint32_t>> indiciesList; 
            std::unique_ptr<Handle> vertShader, fragShader, texture; 
            std::unique_ptr<std::queue<std::pair<const double, const glm::vec3>>> relativeRotationList; 

        };
    }
}