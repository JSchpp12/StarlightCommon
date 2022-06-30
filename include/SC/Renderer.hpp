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
            Renderer(common::ConfigFile* configFile, common::FileResourceManager<Shader>* shaderManager, common::FileResourceManager<GameObject>* objectManager, 
                common::FileResourceManager<Texture>* textureManager, common::Camera* inCamera, 
                const std::vector<Handle>* objectHandles) : 
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
                    alignas(16) glm::mat4 inverseView;              //used to extrapolate camera position, can be used to convert from camera to world space
                    alignas(16) glm::vec4 ambientLightColor;
                    uint32_t numLights;                             //number of lights in render
                };
        private: 

        }; 
    }
}