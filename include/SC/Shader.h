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

                virtual ~Shader(){};

                std::vector<uint32_t> GetSpirV() {
                    return *this->compiledCode.get();
                }
            protected: 
                
                
            private: 
                std::unique_ptr<std::vector<uint32_t>> compiledCode; 
        }; 
    }

}
