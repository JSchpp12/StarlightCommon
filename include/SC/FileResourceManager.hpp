#pragma once 

#include "ResourceContainer.hpp"
#include "Handle.hpp"

namespace star{
    namespace common{
        template<typename T>
        class FileResourceManager{
        public:
            virtual ~FileResourceManager() {}; 
            
            // virtual Handle Add(T) = 0; 
            virtual Handle Add(const std::string& pathToFile) = 0; 

            //For managers that have more than one default, this must be overridden
            virtual T* Get(const Handle& handle) {
                return this->fileContainer.GetResource(handle); 
            }

        protected:
            common::ResourceContainer<T> fileContainer;

        private: 

        };
    }
}