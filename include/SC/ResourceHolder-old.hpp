#pragma once 

#include <memory> 
#include <map>
#include <errno.h> 

namespace star{
    namespace common{
        template<typename Resource, typename Identifier> 
        class ResourceHolder{
            public: 
            // void Load(Identifier id, const std::string& filename){
            //     std::unique_ptr<Resource> resource(new Resource()); 
            //     if(!resource->LoadFromFile()){
            //         throw std::runtime_error("ResourceHolder::load() -- failed to load resource from file"); 
            //     }
            // }

            Resource& Get(Identifier id){
                auto found = resourceMap.find(id); 
                assert(found != resourceMap.end()); 

                return *found->second;
            }

            bool Contains(Identifier id){
                return resourceMap.contains(id); 
            }

            protected: 
            std::map<Identifier, std::unique_ptr<Resource>> resourceMap; 

            void insertResource(Identifier id, std::unique_ptr<Resource> resource){
                auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource))); 
                assert(inserted.second); 
            }
        }; 
    }
}

