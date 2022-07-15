#pragma once 

#include <memory>
#include <optional>
#include <functional>

namespace star::common{
	class ProgrammaticInteractivity {
	public:

	protected:
		//the following can be used in future to 
		std::optional<std::unique_ptr<std::function<void(int, int, int, int)>>> keyboardCallbackFun;
		std::optional<std::unique_ptr<std::function<void(double, double)>>> mouseCallbackFun, scrollCallbackFun;
		std::optional<std::unique_ptr<std::function<void(int, int, int)>>> mouseButtonCallbackFun;

	private:

	};
}