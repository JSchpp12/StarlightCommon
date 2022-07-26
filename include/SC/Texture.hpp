#pragma once 

#include <stb_image.h>

#include <memory> 
#include <vector> 
#include <string> 
#include <stdexcept>
#include <optional>
#include <iostream>

namespace star::common{
    class Texture{
    public: 
        int width, height, channels;
        std::string pathToFile;
        bool onDisk;
        Texture(std::unique_ptr<std::vector<unsigned char>> rawData, int texWidth, int texHeight, 
            int texChannels) 
            : rawData(std::unique_ptr<std::vector<unsigned char>>(std::move(rawData))), width(texWidth),
            height(texHeight), channels(texChannels) {
            onDisk = false; 
        }
        /// <summary>
        /// Initalize texture with provided raw data. For use with programatically generated textures. 
        /// </summary>
        /// <param name="rawTextureData"></param>
        /// <param name="texWidth"></param>
        /// <param name="texHeight"></param>
        /// <param name="texChannels"></param>
        Texture(const std::string& pathToImage) 
            : pathToFile(pathToImage){
            onDisk = true; 
            init();
        }

        void init() {
            //load from disk to get properties of image
            auto pixelData = stbi_load(pathToFile.c_str(), &width, &height, &channels, STBI_rgb_alpha);
            if (!pixelData) {
                throw std::runtime_error("Unable to load image");
            }
            stbi_image_free(pixelData);
        }
        /// <summary>
        /// Read the image from disk into memory
        /// </summary>
        /// <returns></returns>
        std::unique_ptr<unsigned char> data() {
            //load from disk
            if (onDisk) {
                std::unique_ptr<unsigned char> pixelData(stbi_load(pathToFile.c_str(), &width, &height, &channels, STBI_rgb_alpha));
                if (!pixelData) {
                    throw std::runtime_error("Unable to load image");
                }

                return std::move(pixelData);
            }
            else if (rawData) {
                auto data = std::unique_ptr<unsigned char>(new unsigned char[rawData->size()]);
                std::copy(rawData->begin(), rawData->end(), data.get());
                return data; 
            }
            else {
                return std::unique_ptr<unsigned char>(new unsigned char[] {0x00, 0x00, 0x00, 0x00});
            }
        }
    protected: 

    private: 
        std::unique_ptr<std::vector<unsigned char>> rawData;

    }; 
}