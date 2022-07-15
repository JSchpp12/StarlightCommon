#pragma once 
#include "FileResourceManager.hpp"
#include "MemoryManager.hpp"
#include "Shader.h"
#include "GameObject.hpp"
#include "Texture.hpp"
#include "ConfigFile.hpp"
#include "Camera.hpp"
#include "Material.hpp"

#include <glm/glm.hpp>

namespace star::common{
    class Renderer{
    public:
        Renderer(ConfigFile& configFile, FileResourceManager<Shader>& shaderManager, FileResourceManager<GameObject>& objectManager,
            Camera& inCamera, const std::vector<Handle>& objectHandles) : 
            configFile(configFile), shaderManager(shaderManager), 
            objectManager(objectManager), camera(inCamera), 
            objectList(objectHandles) { }

        virtual ~Renderer() {}; 
            
        virtual void prepare() = 0; 

        virtual void draw() = 0; 

        virtual void cleanup() = 0; 

    protected: 
            ConfigFile& configFile; 
            FileResourceManager<Shader>& shaderManager; 
            FileResourceManager<GameObject>& objectManager;
            Camera& camera; 
            const std::vector<Handle>& objectList; 

            struct GlobalUniformBufferObject {
                alignas(16) glm::mat4 proj;
                alignas(16) glm::mat4 view;
                alignas(16) glm::mat4 inverseView;              //used to extrapolate camera position, can be used to convert from camera to world space
                uint32_t numLights;                             //number of lights in render
            };
    private: 

    }; 
}