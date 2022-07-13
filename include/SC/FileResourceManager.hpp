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
            /// <summary>
            /// Add a unique resource that will not automatically be shared by any other object.
            /// </summary>
            /// <param name="newResource"></param>
            /// <returns></returns>
            virtual Handle addUniqueResource(std::unique_ptr<T> newResource) {
                return this->MemoryManager<T>::addResource(std::move(newResource));
            }
            virtual T& get(const common::Handle& handle) {
                return this->MemoryManager<T>::getResource(handle); 
            }

        protected:
            FileResourceContainer<T> fileContainer;

            virtual Handle addResource(const std::string& path, std::unique_ptr<T> newResource) {
                common::Handle newHandle = this->MemoryManager<T>::addResource(std::move(newResource));
                this->fileContainer.add(path, newHandle); 
                return newHandle;
            }

            virtual Handle createAppropriateHandle() override = 0; 

        private: 


        };
    }
}