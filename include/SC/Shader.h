#pragma once 

#include <vector> 
#include <iostream>
#include <memory> 
#include <string>

namespace star::common{
    class Shader{
        public:
            std::string path; 
            Shader(const std::string& path) : path(path){ }
            virtual ~Shader(){};

        protected:  
                
        private: 

    }; 
}