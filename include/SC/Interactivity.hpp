#pragma once 

#include <GLFW/glfw3.h>

#include <memory>
#include <optional>
#include <functional>

namespace star::common{
	//base class to inherit from if an application wishes to handle user interaction such as keyboard callbacks and mouse movement
	class Interactivity {
	public:
			
		/// <summary>
		/// Function that will be called when a keyboard interaction is registered by the windowing system
		/// </summary>
		/// <param name="key">GLFW keycode</param>
		/// <param name="scancode"></param>
		/// <param name="action">GLFW action</param>
		/// <param name="mods"></param>
		virtual void keyCallback(int key, int scancode, int action, int mods) {};

		/// <summary>
		/// Function that will be called when mouse movement is registered by the windowing system
		/// </summary>
		/// <param name="xpos">Current x position of the mouse</param>
		/// <param name="ypos">Current y position of the mouse</param>
		virtual void mouseMovementCallback(double xpos, double ypos) {}; 

		/// <summary>
		/// Function that will be called when a mouse button interaction is registered by the windowing system
		/// </summary>
		/// <param name="button">GLFW key code for the button pressed</param>
		/// <param name="action">GLFW action</param>
		/// <param name="mods"></param>
		virtual void mouseButtonCallback(int button, int action, int mods) {}; 

		/// <summary>
		/// Function that will be called when a mouse wheel scroll interaction is registered by the windowing system. 
		/// </summary>
		/// <param name="xoffset"></param>
		/// <param name="yoffset"></param>
		virtual void scrollCallback(double xoffset, double yoffset) {}; 

		/// <summary>
		/// Function that will be called before the user defined appliction world update function
		/// </summary>
		virtual void worldUpdate() {};

	protected:

	private:

	};
}