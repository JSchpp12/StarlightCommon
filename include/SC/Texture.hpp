#pragma once 

#include <memory> 
#include <vector> 
#include <string> 

namespace star::common{
    class Texture{
    public: 
        //Texture(std::unique_ptr<unsigned char> rawTextureData, std::unique_ptr<int> width, std::unique_ptr<int> height, std::unique_ptr<int> channels ){
        //    this->rawTextureData = std::move(rawTextureData); 
        //}

        Texture(const std::string& pathToImage, std::unique_ptr<unsigned char> rawTextureData, int texWidth, int texHeight, int texChannels) :
            pathToFile(pathToImage), 
            rawTextureData(std::move(rawTextureData)), 
            texWidth(texWidth), 
            texHeight(texHeight), 
            texChannels(texChannels)
        {

        }

        int width() { return this->texWidth; }

        int height() { return this->texHeight; }

        int channels() { return this->texChannels; }

        void* data() { return this->rawTextureData.get(); }

        std::string path() { return this->pathToFile; }

        //virtual unsigned char* load() = 0; 
    protected: 
        int texWidth, texHeight, texChannels;
        std::unique_ptr<unsigned char> rawTextureData; 
        std::string pathToFile;

    private: 
    }; 
}