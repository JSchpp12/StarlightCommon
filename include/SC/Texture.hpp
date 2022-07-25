#pragma once 

#include <stb_image.h>

#include <memory> 
#include <vector> 
#include <string> 
#include <stdexcept>

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
        Texture(const std::string& pathToImage, int texWidth, int texHeight, 
            int texChannels) 
            : pathToFile(pathToImage), texWidth(texWidth), 
            texHeight(texHeight), texChannels(texChannels){ }

        Texture(const Texture& texture) : texChannels(texture.texChannels), 
            texHeight(texture.texHeight), texWidth(texture.texWidth){ };

        std::string path() { return this->pathToFile; }

    protected: 
        int texWidth, texHeight, texChannels;
        std::string pathToFile;

    private: 

    }; 
}