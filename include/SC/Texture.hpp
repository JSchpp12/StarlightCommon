#pragma once 

#include <memory> 
#include <vector> 
#include <string> 

namespace star::common{
    class Texture{
    public: 
        /// <summary>
        /// Initalize texture with provided raw data. For use with programatically generated textures. 
        /// </summary>
        /// <param name="rawTextureData"></param>
        /// <param name="texWidth"></param>
        /// <param name="texHeight"></param>
        /// <param name="texChannels"></param>
        Texture(std::unique_ptr<unsigned char> rawTextureData, int texWidth, int texHeight, 
            int texChannels) 
            : rawTextureData(std::move(rawTextureData)), texWidth(texWidth), 
            texHeight(texHeight), texChannels(texChannels){ }
        Texture(const std::string& pathToImage, std::unique_ptr<unsigned char> rawTextureData, int texWidth, 
            int texHeight, int texChannels) 
            : pathToFile(pathToImage), rawTextureData(std::move(rawTextureData)), 
            texWidth(texWidth), texHeight(texHeight), 
            texChannels(texChannels){ 
            this->onDisk = true; 
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
        bool onDisk = false; 


    private: 
    }; 
}