#pragma once 
#include "FileResourceManager.hpp"
#include "Shader.h"
#include "Object.hpp"
#include "Texture.hpp"
#include "ConfigFile.hpp"

#include <glm/glm.hpp>

namespace star{
    namespace common{
        class Renderer{
        public:
            Renderer(common::ConfigFile* configFile, common::FileResourceManager<Shader>* shaderManager, common::FileResourceManager<Object>* objectManager, common::FileResourceManager<Texture>* textureManager, const std::vector<Handle>* objectHandles) : 
                configFile(configFile),
                shaderManager(shaderManager), 
                objectManager(objectManager), 
                textureManager(textureManager), 
                objectList(objectHandles) { }

            virtual ~Renderer() {}; 
            
            virtual void prepare() = 0; 

            virtual void drawFrame() = 0; 

            virtual void cleanup() = 0; 

        protected: 
                common::ConfigFile* configFile; 
                common::FileResourceManager<Shader>* shaderManager; 
                common::FileResourceManager<Object>* objectManager; 
                common::FileResourceManager<Texture>* textureManager;
                const std::vector<common::Handle>* objectList; 

                struct UniformBufferObject {
                    alignas(16) glm::mat4 model; 
                    alignas(16) glm::mat4 view; 
                    alignas(16) glm::mat4 proj; 
                };

        private: 

        }; 
    }
}