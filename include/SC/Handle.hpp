#pragma once 
#include "Enums.h"

#include <optional>

namespace star{
    namespace common{
        struct Handle{
            size_t containerIndex; 
            Handle_Type type; 
            std::optional<Shader_Stage> shaderStage; 
        }; 
    }
}