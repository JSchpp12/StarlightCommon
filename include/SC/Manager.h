#pragma once 

#include "ConfigFile.h"

#include <string> 
#include <memory>

namespace star{
    namespace common{
        class Manager{
        public:
            Manager(std::shared_ptr<ConfigFile> configFile){
                this->configFile = configFile; 
            }
        protected:
            std::shared_ptr<ConfigFile> configFile; 
        private: 

        };
    }
}