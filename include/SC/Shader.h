#pragma once 

#include <vector> 
#include <iostream>
#include <memory> 

namespace star::common{
    class Shader{
        public:
            Shader(std::unique_ptr<std::vector<uint32_t>> compiledShader) : compiledCode(std::move(compiledShader)){}

            virtual ~Shader(){};

            std::vector<uint32_t> GetSpirV() {
                return *this->compiledCode.get();
            }
        protected:  
                
        private: 
            std::unique_ptr<std::vector<uint32_t>> compiledCode; 
    }; 
}