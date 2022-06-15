#pragma once

namespace star{
    namespace common{

        enum Shader_File_Type{
            spirv, 
            glsl
        }; 


        enum Shader_Stage {
            vertex,
            fragment,
            compute
        };

        enum Config_Settings{
            mediadirectory
        }; 

        enum Handle_Type{
            defaultHandle,
            shader, 
            object, 
            texture
        }; 

        enum Buttons {
            STAR_W, 
            STAR_A, 
            STAR_S, 
            STAR_D,
            STAR_CLICK_LEFT, 
            STAR_CLICK_RIGHT, 
            STAR_UP, 
            STAR_DOWN, 
            STAR_LEFT,
            STAR_RIGHT
        };
    }
}