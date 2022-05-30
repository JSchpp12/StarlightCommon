#pragma once 

#include <vector> 
#include <iostream>
#include <memory> 

namespace star{
    namespace common{
        class Shader{
            public:
                Shader(std::unique_ptr<std::vector<uint32_t>> compiledShader) : compiledCode(std::move(compiledShader)){}
                // void LoadFromFile(){
                //     std::cout << "loading" << std::endl; 
                // }
            protected: 
                
                
            private: 
                std::unique_ptr<std::vector<uint32_t>> compiledCode; 
        }; 
    }

}
