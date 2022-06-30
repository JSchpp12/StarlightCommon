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
        template<typename shaderManager, typename textureManager, typename lightManager, typename sceneBuilder>
        class Application{
        public: 
            Application(ConfigFile* configFile, std::vector<common::Handle>* objectList, shaderManager* shaderManager, 
                textureManager* textureManager, lightManager* lightManager, sceneBuilder& sceneManager,
                Camera* inCamera) :
                configFile(configFile), 
                objectList(objectList),
                shaderManager(shaderManager), 
                sceneBuilder(sceneManager),
                textureManager(textureManager), 
                lightManager(lightManager),
                camera(inCamera){ }

            virtual ~Application() {}; 

            virtual void Load() = 0; 

            virtual void Update() = 0;  

            ConfigFile* configFile; 

        protected: 
            sceneBuilder& sceneBuilder;
            shaderManager* shaderManager;
            textureManager* textureManager;
            lightManager* lightManager; 
            std::vector<common::Handle>* objectList; 
            Camera* camera; 

        private: 

        }; 
    }
}