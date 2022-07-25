#pragma once 

#include "ConfigFile.hpp"
#include "Handle.hpp"
#include "MemoryManager.hpp"
#include "FileResourceContainer.hpp"

#include <string> 
#include <memory>
#include <map>
#include <vector> 
#include <assert.h>

namespace star::common{
    template<typename T>
    class FileResourceManager : private MemoryManager<T>{
    public:
        FileResourceManager() : MemoryManager<T>() { }
        virtual ~FileResourceManager(){}; 

        virtual Handle addResource(const std::string& path) {
            if (fileContainer.contains(path)) {
                return fileContainer.getHandle(path);
            }
            else {
                Handle newHandle = this->createAppropriateHandle();
                newHandle.isOnDisk = true;
                newHandle.containerIndex = fileContainer.size();

                this->fileContainer.add(path, newHandle);
                return newHandle;
            }
        }

        virtual Handle addResource(const std::string& path, std::unique_ptr<T> newResource) {
            if (fileContainer.contains(path)) {
                return fileContainer.getHandle(path);
            }
            else {
                common::Handle newHandle = this->MemoryManager<T>::addResource(std::move(newResource));
                newHandle.isOnDisk = true;
                this->fileContainer.add(path, newHandle);
                return newHandle;
            }
        }

        virtual Handle addResource(std::unique_ptr<T> newResource) override { return this->MemoryManager<T>::addResource(std::move(newResource)); }


        virtual T& resource(const Handle& resourceHandle) {
            assert((resourceHandle.type == this->handleType() || resourceHandle.type == Handle_Type::defaultHandle) && "The requested resource handle does not match the type of resources managed by this manager.");
            return this->MemoryManager<T>::resource(resourceHandle); 
        }

    protected:
        FileResourceContainer<T> fileContainer;

        virtual Handle createAppropriateHandle() override = 0; 
        virtual common::Handle_Type handleType() = 0; 
    private: 

    };
}