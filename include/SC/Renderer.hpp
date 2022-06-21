#pragma once 
#include "FileResourceManager.hpp"
#include "Shader.h"
#include "GameObject.hpp"
#include "Texture.hpp"
#include "ConfigFile.hpp"
#include "Camera.hpp"

#include <glm/glm.hpp>

namespace star{
    namespace common{
        class Renderer{
        public:
            Renderer(common::ConfigFile* configFile, common::FileResourceManager<Shader>* shaderManager, common::FileResourceManager<GameObject>* objectManager, common::FileResourceManager<Texture>* textureManager, common::Camera* inCamera, const std::vector<Handle>* objectHandles) : 
                configFile(configFile),
                shaderManager(shaderManager), 
                objectManager(objectManager), 
                textureManager(textureManager), 
                camera(inCamera),
                objectList(objectHandles) { }

            virtual ~Renderer() {}; 
            
            virtual void prepare() = 0; 

            virtual void draw() = 0; 

            virtual void cleanup() = 0; 

        protected: 
                common::ConfigFile* configFile; 
                common::FileResourceManager<Shader>* shaderManager; 
                common::FileResourceManager<GameObject>* objectManager;
                common::FileResourceManager<Texture>* textureManager;
                common::Camera* camera; 
                const std::vector<common::Handle>* objectList; 

                struct GlobalUniformBufferObject {
                    alignas(16) glm::mat4 proj;
                    alignas(16) glm::mat4 view;
                    alignas(16) glm::vec4 ambientLightColor{1.0f, 1.0f, 1.0f, 0.1f};
                    glm::vec3 lightPosition{-2.0f, 2.0f, 0.0f};
                    alignas(16) glm::vec4 lightColor{1.0f, 1.0f, 1.0f, 1.0f};               //w is light intensity
                };

                struct UniformBufferObject {
                    alignas(16) glm::mat4 modelMatrix; 
                    alignas(16) glm::mat4 normalMatrix; 
                };

                struct ObjectPushConstants {
                    int modelIndex; 
                };

        private: 

        }; 
    }
}