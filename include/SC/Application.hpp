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
        template<typename shaderManagerT, typename textureManagerT, typename lightManagerT, typename sceneBuilderT>
        class Application{
        public: 
            Application(ConfigFile* configFile, std::vector<common::Handle>* objectList, shaderManagerT* shaderManager, 
                textureManagerT* textureManager, lightManagerT* lightManager, sceneBuilderT& sceneManager,
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
            sceneBuilderT& sceneBuilder;
            shaderManagerT* shaderManager;
            textureManagerT* textureManager;
            lightManagerT* lightManager; 
            std::vector<common::Handle>* objectList; 
            Camera* camera; 

        private: 

        }; 
    }
}