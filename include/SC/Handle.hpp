#pragma once 
#include "Enums.h"

#include <optional>

namespace star::common{
    struct Handle{
        static Handle getDefault() {
            Handle newHandle; 
            newHandle.type = Handle_Type::defaultHandle; 
            return newHandle; 
        }
        Handle() = default;

        uint32_t id = 0; 
        size_t containerIndex = 0; 
        Handle_Type type = Handle_Type::null; 
        bool isOnDisk = false; 
        std::optional<Shader_Stage> shaderStage; 
    }; 
}