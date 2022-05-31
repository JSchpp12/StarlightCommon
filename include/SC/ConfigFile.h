#pragma once 

#include "FileHelpers.h"
#include "Enums.h"

#include <iostream> 
#include <string> 
#include <sstream>
#include <map> 
#include <memory> 

namespace star{
    namespace common{
        class ConfigFile{
        public:
            ConfigFile(const std::string& configFilePath){
                auto contents = FileHelpers::ReadFile(configFilePath, false); 
                std::istringstream stream(contents); 

                std::string line; 
                while(std::getline(stream, line)){
                    std::istringstream lineStream(line); 
                    std::string key; 
                    if (std::getline(lineStream, key, '=')){
                        std::string value; 
                        if(std::getline(lineStream, value)){
                            auto settingsMatch = availableSettings.find(key); 
                            if(settingsMatch != availableSettings.end()){
                                this->settings.insert(std::pair<Config_Settings, std::string>(settingsMatch->second, value)); 
                            }
                        }
                    }
                }
            }; 

            std::string GetSetting(Config_Settings setting){
                auto settingsRecord = this->settings.find(setting); 

                if (settingsRecord != this->settings.end()){
                    return settingsRecord->second; 
                }
                throw std::runtime_error("Setting not found " + setting); 
            }
        private: 
            std::map<Config_Settings, std::string> settings; 
            inline static std::map<std::string, Config_Settings> availableSettings = {
                std::pair<std::string, star::common::Config_Settings>("mediadirectory", Config_Settings::mediadirectory)
            }; 
        }; 
    }
}

// std::map<std::string, star::common::Config_Settings> star::common::ConfigFile::availableSettings = std::map<std::string, star::common::Config_Settings>{

// }; 