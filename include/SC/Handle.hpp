#pragma once 
#include "Enums.h"

#include <optional>

namespace star::common{
    struct Handle{
        size_t containerIndex = 0; 
        Handle_Type type = Handle_Type::null; 
        std::optional<Shader_Stage> shaderStage; 
    }; 
}