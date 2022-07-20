#pragma once 
#include "Enums.h"

namespace star::common {
	class RenderOptions {
	public:
		RenderOptions() = default; 

		RenderOptions(const RenderOptions&) = delete;
		RenderOptions& operator=(const RenderOptions&) = delete;

		void setRenderMaterialSetting(Render_Settings::Material propToDraw) {
			resetAll(); 

			if (propToDraw != Render_Settings::Material::none){
				this->options |= propToDraw; 
			}
		}

		uint32_t getRenderOptions() { return this->options; }

	private: 
		uint64_t options = 0; 

		//reset rendering options to defaults
		void resetAll() {
			this->options = 0;
		}
	};
}