#pragma once 

#include <chrono>

namespace star::common{
	class Time {
	public: 
		Time() = default; 

		/// <summary>
		/// Set the time of last frame draw to the current time. 
		/// </summary>
		void updateLastFrameTime() {
			lastFrameTime = std::chrono::steady_clock::now(); 
		}

		/// <summary>
		/// Get the time since the last time point set for the frame draw time in seconds. 
		/// </summary>
		/// <returns></returns>
		double timeElapsedLastFrameSeconds() {
			auto now = std::chrono::steady_clock::now(); 
			std::chrono::duration<double> elapsedSeconds = now - lastFrameTime; 
			return elapsedSeconds.count();
		}


	protected:

	private: 
		std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
	};
}