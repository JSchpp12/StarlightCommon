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
            FileResourceManager() : MemoryManager<T>() { }
            virtual ~FileResourceManager(){}; 

            virtual common::Handle add(const std::string& path) = 0; 

            virtual T& get(const common::Handle& handle) {
                return this->MemoryManager<T>::getResource(handle); 
            }

        protected:
            FileResourceContainer<T> fileContainer;

            virtual void addResource(std::unique_ptr<T> newResource, common::Handle& newHandle) {
                this->MemoryManager<T>::addResource(std::move(newResource), newHandle); 
            }

            virtual void addResource(const std::string& path, std::unique_ptr<T> newResource, common::Handle& newHandle) {
                this->MemoryManager<T>::addResource(std::move(newResource), newHandle);
                this->fileContainer.add(path, newHandle); 
            }

            virtual Handle createAppropriateHandle() = 0; 

        private: 


        };
    }
}