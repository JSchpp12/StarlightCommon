#pragma once 

#include <memory> 
#include <vector> 
#include <string> 

namespace star{
    namespace common{
        class Texture{
        public: 
            Texture(std::unique_ptr<unsigned char> rawTextureData, std::unique_ptr<int> width, std::unique_ptr<int> height, std::unique_ptr<int> channels ){
                this->rawTextureData = std::move(rawTextureData); 
            }

            Texture(const std::string& pathToTexture){
                this->texturePath = pathToTexture; 
            }
        protected: 

        private: 
            std::unique_ptr<unsigned char> rawTextureData; 
            std::string texturePath; 
        }; 
    }
}