#pragma once

#include "FileResourceManager.hpp"
#include "Shader.h"
#include "ConfigFile.hpp"
#include "Handle.hpp"

#include <GLFW/glfw3.h>

#include <memory> 
#include <string> 
#include <vector>

namespace star{
    namespace common{
        template<typename shaderManager, typename objectManager, typename textureManager>
        class Application{
        public: 
            Application(ConfigFile* configFile, std::vector<common::Handle>* objectList, shaderManager* shaderManager, objectManager* objectManager, textureManager* textureManager) :
                configFile(configFile), 
                objectList(objectList),
                shaderManager(shaderManager), 
                objectManager(objectManager), 
                textureManager(textureManager)
            { 
            }

            virtual ~Application() {}; 

            virtual void Load() = 0; 

            virtual void Update() = 0; 

            ConfigFile* configFile; 

        protected: 
            shaderManager* shaderManager;
            objectManager* objectManager;
            textureManager* textureManager;
            std::vector<common::Handle>* objectList; 

        private: 

        }; 
    }
}