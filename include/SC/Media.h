#pragma once  

#include <string>

namespace star::commmon{
    //any object type should inherit from this 
    class Media{
    public: 
        virtual std::string loadFromFile(std::string pathToFile) = 0; 
    protected: 

    private: 

    }; 
}