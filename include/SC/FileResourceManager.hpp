#pragma once 

#include "ConfigFile.hpp"
#include "Handle.hpp"
#include "MemoryManager.hpp"
#include "FileResourceContainer.hpp"

#include <string> 
#include <memory>
#include <map>
#include <vector> 

namespace star{
    namespace common{
        template<typename T>
        class FileResourceManager : public MemoryManager<T>{
        public:
            virtual ~FileResourceManager(){}; 

            virtual common::Handle add(const std::string& path) = 0; 

            virtual T* get(const common::Handle& handle) {
                return this->container.get(handle); 
            }

        protected:
            FileResourceContainer<T> fileContainer;

            virtual void addResource(const std::string& path, std::unique_ptr<T> newResource, common::Handle& newHandle) {
                newHandle.containerIndex = this->container.size(); 
                this->container.add(std::move(newResource)); 
                this->fileContainer.add(path, newHandle); 
            }

        private: 

        };
    }
}