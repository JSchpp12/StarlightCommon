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

	protected:
		void addResource(std::unique_ptr<T> newResource, common::Handle& newHandle){
			newHandle.containerIndex = this->container.size(); 
			this->container.add(std::move(newResource)); 
		}

		T* getResource(const common::Handle& handle) {
			return this->container.get(handle);
		}

	private: 
		ResourceContainer<T> container;

	};
}
}