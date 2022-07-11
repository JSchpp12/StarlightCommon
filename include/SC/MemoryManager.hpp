#pragma once 
#include "Handle.hpp"
#include "Enums.h"
#include "ResourceContainer.hpp"

#include <memory>
#include <vector>

namespace star::common{
	template<typename T>
	class MemoryManager {
	public:
		/// <summary>
		/// Init manager with a default material if desired.
		/// </summary>
		/// <param name="defaultResource"></param>
		MemoryManager(std::unique_ptr<T> defaultResource) {
			Handle defaultHandle = this->createAppropriateHandle(); 
			this->addResource(std::move(defaultResource), defaultHandle);
			this->defaultHandle = std::make_unique<Handle>(defaultHandle); 
			this->defaultResource = &this->getResource(defaultHandle);
		}
		virtual ~MemoryManager() { };

		T* getDefault() {
			if (this->defaultResource != nullptr)
				return this->defaultResource;
			throw std::runtime_error("No default resource was set");
		}

	protected:
		//Inherited classes should be permitted to inherit from this class without default material reqs. It is expected these classes will handle their own defaults.
		MemoryManager() = default;

		T* defaultResource = nullptr;
		std::unique_ptr<Handle> defaultHandle;

		void addResource(std::unique_ptr<T> newResource, common::Handle& newHandle){
			newHandle.containerIndex = this->container.size(); 
			this->container.add(std::move(newResource)); 
		}

		T& getResource(const common::Handle& handle) {
			return this->container.get(handle);
		}
		/// <summary>
		/// Create appropriate handle for this manager type 
		/// </summary>
		/// <returns></returns>
		virtual Handle createAppropriateHandle() = 0; 

		size_t size() { return this->container.size(); }

	private: 
		ResourceContainer<T> container;


	};
}