#pragma once

#include "FileResourceManager.hpp"
#include "Shader.h"
#include "ConfigFile.hpp"
#include "Handle.hpp"
#include "Camera.hpp"

#include <GLFW/glfw3.h>

#include <memory> 
#include <string> 
#include <vector>

namespace star{
    namespace common{
        template<typename shaderManager, typename objectManager, typename textureManager, typename lightManager>
        class Application{
        public: 
            Application(ConfigFile* configFile, std::vector<common::Handle>* objectList, shaderManager* shaderManager, 
                objectManager* objectManager, textureManager* textureManager, lightManager* lightManager,
                Camera* inCamera) :
                configFile(configFile), 
                objectList(objectList),
                shaderManager(shaderManager), 
                objectManager(objectManager), 
                textureManager(textureManager), 
                lightManager(lightManager),
                camera(inCamera){ }

            virtual ~Application() {}; 

            virtual void Load() = 0; 

            virtual void Update() = 0;  

            ConfigFile* configFile; 

        protected: 
            shaderManager* shaderManager;
            objectManager* objectManager;
            textureManager* textureManager;
            lightManager* lightManager; 
            std::vector<common::Handle>* objectList; 
            Camera* camera; 

        private: 

        }; 
    }
}