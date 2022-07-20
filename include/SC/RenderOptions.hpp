#pragma once 
#include "Enums.h"

namespace star::common {
	//TODO: instead of having a bool for every option, can use uint and utilize binary operations to store settings
	class RenderOptions {
	public:
		RenderOptions() = default; 

		RenderOptions(const RenderOptions&) = delete;
		RenderOptions& operator=(const RenderOptions&) = delete;

		void drawMaterialProperty(Render_Settings::Material propToDraw) {
			resetAll(); 

			if (propToDraw != Render_Settings::Material::none){
				if (propToDraw & Render_Settings::Material::ambient) {
					this->drawAmbient = true;
				}
			}
			else {
				this->draw = true;
			}
		}

		uint32_t getRenderOptions() {
			uint32_t options = 0; 

			if (this->draw) {
				return options; 
			}
			else {
				if (this->drawAmbient)
					return options |= Render_Settings::ambient; 
			}
		}

	private: 
		bool draw = true;			//normal draw operation
		bool drawAmbient = false;	//draw the ambient materials of each fragment

		//reset rendering options to defaults
		void resetAll() {
			this->drawAmbient = false; 
		}
	};
}