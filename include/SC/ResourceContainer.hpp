#pragma once 

#include "ConfigFile.hpp"
#include "Handle.hpp"

#include <string> 
#include <memory>
#include <map>
#include <vector> 

namespace star{
    namespace common{
        template<typename T>
        class ResourceContainer{
        public:
            //TODO: make these private
            std::vector<std::unique_ptr<T>> container;
            std::map<std::string, Handle> fileMap;

            virtual ~ResourceContainer(){}; 
            
            //check the file map to see if the resource has been previously loaded
            bool FileLoaded(const std::string& pathToObject){
                auto found = fileMap.find(pathToObject); 
                if (found != fileMap.end())
                    return true; 
                return false; 
            }

            T* GetResource(const Handle& handle){
                if (handle.containerIndex > container.size()){
                    throw std::runtime_error("Requested a resource that is outside the range of the container");
                }

                return container[handle.containerIndex].get(); 
            }

            Handle GetResource(const std::string& pathToObject) {
                auto found = fileMap.find(pathToObject); 
                if (found != fileMap.end()) {
                    return found->second; 
                }
                else {
                    throw std::runtime_error("Requested resource does not exist"); 
                }
            }

            Handle AddResource(std::unique_ptr<T> resource){
                Handle newHandle{this->container.size()}; 
                this->container.push_back(std::move(resource)); 
            }

            Handle AddFileResource(const std::string path, std::unique_ptr<T>& resource){
                Handle newHandle{this->container.size()}; 
                this->container.push_back(std::move(resource)); 

                this->fileMap.insert(std::pair<std::string, Handle>(path, newHandle)); 
                return newHandle;
            }
            
            size_t numberOfUniqueResources() {
                return this->container.size(); 
            }

        private: 
        };
    }
}