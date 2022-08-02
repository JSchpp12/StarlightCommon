#pragma once 

//TODO: MOVE THIS INTO THE GAME ENGINE PROJ

#include "Entity.hpp"
#include "Time.hpp"
#include "Handle.hpp"
#include "Material.hpp"
#include "Vertex.hpp"
#include "Mesh.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_cross_product.hpp>

#include <stb_image.h>

#include <queue>
#include <memory>
#include <vector>

namespace star::common{
    class GameObject : public Entity{
    public:
        GameObject(glm::vec3 position, glm::vec3 scale, Handle& vertShaderHandle,
            Handle& fragShaderHandle, std::vector<std::unique_ptr<common::Mesh>> meshes) :
            Entity(), 
            meshes(std::move(meshes)),
            vertShader(std::make_unique<Handle>(vertShaderHandle)),
            fragShader(std::make_unique<Handle>(fragShaderHandle))
        {
            this->setScale(scale); 
            this->setPosition(position);
        } 

        virtual ~GameObject() {}; 

        //get the handle for the vertex shader 
        Handle getVertShader() { return *this->vertShader.get(); }
        //get the handle for the fragment shader
        Handle getFragShader() { return *this->fragShader.get(); }
        const std::vector<std::unique_ptr<common::Mesh>>& getMeshes() { return this->meshes; }
        glm::mat4 getNormalMatrix() { return glm::inverseTranspose(getDisplayMatrix()); }

    protected: 

    private: 
        //is the mmodel matrix updated with most recent changes 
        std::unique_ptr<Handle> vertShader, fragShader; 
        std::vector<std::unique_ptr<common::Mesh>> meshes; 
    };
}
