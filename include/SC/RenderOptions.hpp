#pragma once 
#include "Enums.h"

namespace star::common {
	class RenderOptions {
	public:
		RenderOptions() = default; 

		RenderOptions(const RenderOptions&) = delete;
		RenderOptions& operator=(const RenderOptions&) = delete;

		void setRenderMaterialSetting(Render_Settings::Material propToDraw) {
			resetMaterial(); 

			if (propToDraw != Render_Settings::Material::none){
				this->materialOptions |= propToDraw; 
			}
		}

		void setRenderFeature(Render_Settings::Feature feature, bool enabled) {
			if (enabled)
				this->renderFeatures |= (1 << feature);
			else
				this->renderFeatures &= ~(1 << feature); 
		}
		/// <summary>
		/// Check if specific feature is enabled.
		/// </summary>
		/// <param name="feature"></param>
		/// <returns></returns>
		bool isFeatureEnabled(Render_Settings::Feature feature) {
			return (this->renderFeatures & (1 << feature)) != 0;
		}

		uint32_t getRenderOptions() { 
			return (uint32_t)renderFeatures << 16 | materialOptions;
		}

	private: 
		uint16_t renderFeatures = 0; 
		uint16_t materialOptions = 0; 

		void resetAll() {
			resetMaterial(); 
			resetTexture(); 
		}
		//reset rendering options to defaults
		void resetMaterial() {
			this->materialOptions = 0;
		}
		void resetTexture() {
			this->renderFeatures = 0;
		}
	};
}