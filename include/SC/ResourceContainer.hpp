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
            virtual ~ResourceContainer(){}; 

            virtual size_t size() {
                return this->container.size();
            }

            virtual Handle add(std::unique_ptr<T> resource) {
                Handle newHandle{ this->container.size() };
                this->container.push_back(std::move(resource));
                return newHandle;
            }

            virtual T* get(const Handle& handle) {
                if (handle.containerIndex > container.size()) {
                    throw std::runtime_error("Requested a resource that is outside the range of the container");
                }

                return container[handle.containerIndex].get();
            }

        protected:
            std::vector<std::unique_ptr<T>> container;

        private: 

        };
    }
}
