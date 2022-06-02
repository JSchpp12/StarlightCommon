#pragma once

#include "FileResourceManager.hpp"
#include "Shader.h"
#include "Texture.hpp"
#include "Object.hpp"
#include "ConfigFile.hpp"

#include <GLFW/glfw3.h>

#include <memory> 
#include <string> 

namespace star{
    namespace common{
        class Application{
        public: 
            Application(ConfigFile* configFile, FileResourceManager<Shader>* shaderManager, FileResourceManager<Object>* objectManager, FileResourceManager<Texture>* textureManager) : 
                configFile(configFile), 
                shaderManager(shaderManager), 
                objectManager(objectManager), 
                textureManager(textureManager)
            { 
            }

            virtual void Load() = 0; 

            virtual void Update() = 0; 

            FileResourceManager<Shader>* shaderManager; 
            FileResourceManager<Object>* objectManager; 
            FileResourceManager<Texture>* textureManager;
            ConfigFile* configFile; 

        protected: 

        private: 

        }; 
    }
}