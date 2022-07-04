#pragma once 

#include "Enums.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

namespace star{
    namespace common{
        struct FileHelpers{
            static std::string ReadFile(std::string pathToFile, bool includeCarriageReturns=true){
                std::string line, text;
                std::ifstream fileReader(pathToFile);

                while (std::getline(fileReader, line)) {
                    text += line + (includeCarriageReturns ? "\n" : ""); 
                }

	            return(text); 
            }


            static std::string GetFileExtension(const std::string& pathToFile){
                return pathToFile.substr(pathToFile.find_last_of('.')); 
            }

            static std::string GetFileNameWithExtension(const std::string& pathToFile){
                return pathToFile.substr(pathToFile.find_last_of("/\\") + 1); 
            }

            static std::string GetBaseFileDirectory(const std::string& pathToFile) {
                size_t found = pathToFile.find_last_of("/\\"); 
                return pathToFile.substr(0, found) + "/";
            }

            //Get file type of provided file -- shaders
            static Shader_File_Type GetFileType(const std::string& pathToFile){
                auto posOfExt = pathToFile.find_last_of('.'); 

                auto fileExtension = pathToFile.substr(posOfExt); 

                if (fileExtension == ".spv"){
                    return Shader_File_Type::spirv; 
                }else if(fileExtension == ".frag" || fileExtension == ".vert"){
                    return Shader_File_Type::glsl; 
                }

                throw std::runtime_error("Unsupported file type provided"); 
            }

            static Shader_Stage GetStageOfShader(const std::string& pathToFile){
                auto posOfExt = pathToFile.find_last_of('.'); 

                auto fileExt = pathToFile.substr(posOfExt); 

                if (fileExt == ".vert"){
                    return Shader_Stage::vertex; 
                }else if (fileExt == ".frag"){
                    return Shader_Stage::fragment; 
                }

                throw std::runtime_error("Unsupported stage type for shader");
            }
        }; 
    }
}