#pragma once 

#include "ResourceContainer.hpp"
#include "Handle.hpp"

namespace star{
    namespace common{
        template<typename T>
        class FileResourceManager{
        public:
            // virtual Handle Add(T) = 0; 
            virtual Handle Add(const std::string& pathToFile) = 0; 

        protected:
            common::ResourceContainer<T> fileContainer; 
        private: 

        };
    }
}