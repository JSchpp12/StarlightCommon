// #pragma once

// #include "Handle.hpp"

// #include <vector> 
// #include <memory> 

// namespace star{
//     namespace common{
//         //object that will be visible during rendering -- contains textures and shader information 
//         template<typename vectype, typename indextype>
//         class RenderObject{
//         public:
//             RenderObject(std::unique_ptr<std::vector<vectype>> vertexList, std::unique_ptr<std::vector<indextype> indiciesList) : 
//                 vertexList(std::move(vertexList)), 
//                 indiciesList(std::move(indiciesList)) 
//             // virtual void PreparePipeline() = 0; 

//         protected: 
//             std::unique_ptr<std::vector<vectype>> vertexList; 
//             std::unique_ptr<std::vector<indextype>> indiciesList; 
            
//         private: 

//         }; 
//     }; 
// }