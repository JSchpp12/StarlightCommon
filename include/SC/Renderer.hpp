#pragma once 
#include "FileResourceManager.hpp"

#include <GLFW/glfw3.h>

namespace star{
    namespace common{
        class Renderer{
        public:
            virtual void PrepPipeline(); 
            virtual void DrawFrame(); 

        protected: 

        private: 

        }
    }
}