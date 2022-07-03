#pragma once
#include "Handle.hpp"
#include "Enums.h"

#include <glm/glm.hpp>

#include <vector> 
#include <memory> 

namespace star{
    namespace common{
        class Mesh{
        public: 
            class Builder {
            public:
                Builder() = default; 
                Builder& setVerticies(std::unique_ptr<std::vector<common::Vertex>> verticies) {
                    this->verticies = std::move(verticies); 
                    return *this; 
                }
                Builder& setIndicies(std::unique_ptr<std::vector<uint32_t>> indicies) {
                    this->indicies = std::move(indicies); 
                    return *this; 
                }
                Builder& setTexture(common::Handle texture) { 
                    this->texture = texture; 
                    return *this; 
                }
                std::unique_ptr<common::Mesh> build() {
                    assert(this->verticies && this->indicies && "Both verticies and indicies need to be provided to create a mesh"); 

                    return std::make_unique<Mesh>(std::move(this->verticies), std::move(this->indicies), this->texture); 
                }

            private:
                std::unique_ptr<std::vector<common::Vertex>> verticies; 
                std::unique_ptr<std::vector<uint32_t>> indicies; 
                common::Handle texture; 
                //common::Handle material = common::Handle{0, Handle_Type::material};

            };

            Mesh(std::unique_ptr<std::vector<Vertex>> verticies, std::unique_ptr<std::vector<uint32_t>> indicies, common::Handle texture) : 
                verticies(std::move(verticies)), indicies(std::move(indicies)), texture(texture) { };

            std::vector<Vertex>& getVerticies() { return *this->verticies; }
            std::vector<uint32_t>& getIndicies() { return *this->indicies; }
            common::Handle getTexture() { return this->texture; }

        protected: 

        private: 
            std::unique_ptr<std::vector<Vertex>> verticies; 
            std::unique_ptr<std::vector<uint32_t>> indicies; 
            common::Handle texture; 
            //TODO: add this back -- along with moving an image to the material
            //common::Handle material; 
        }; 
    }
}