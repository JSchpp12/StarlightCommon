#pragma once

#include "FileResourceManager.hpp"
#include "Shader.h"
#include "Texture.hpp"
#include "Object.hpp"
#include "ConfigFile.hpp"

#include <memory> 
#include <string> 

namespace star{
    namespace common{
        class Application{
        public: 
            Application(const std::string& pathConfigFile) : 
                configFile(new ConfigFile(pathConfigFile))
            { 
                
            }

            virtual void Load() = 0; 

            virtual void Update() = 0; 

            std::unique_ptr<FileResourceManager<Shader>> shaderManager; 
            std::unique_ptr<FileResourceManager<Object>> objectManager; 
            std::unique_ptr<FileResourceManager<std::string>> textureManager;
            std::unique_ptr<ConfigFile> configFile; 

        protected: 

        private: 

        }; 
    }
}