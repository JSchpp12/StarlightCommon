#pragma once

namespace star{
    namespace common{
        enum Pipe_Stage{
            compute, 
            geometry, 
            tesilliation, 
            vertex, 
            fragment
        };

        enum Shader_File_Type{
            spirv, 
            glsl
        }; 

        enum Config_Settings{
            mediadirectory
        }; 

        enum Handle_Type{
            shader, 
            object, 
            texture
        }; 
    }
}