#pragma once 
#include "Handle.hpp"
#include "Enums.h"
#include "ResourceContainer.hpp"

#include <memory>
#include <vector>

namespace star {
namespace common {
	template<typename T>
	class MemoryManager {
	public:
		virtual ~MemoryManager() { };

		common::Handle add(std::unique_ptr<T> newResource) { return this->container.add(std::move(newResource)); }

	protected:
		ResourceContainer<T> container; 

	private: 


	};
}
}