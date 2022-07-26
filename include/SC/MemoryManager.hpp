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
		MemoryManager(std::unique_ptr<T> defaultResource){ }
		virtual ~MemoryManager() { };

		virtual Handle addResource(std::unique_ptr<T> newResource) {
			Handle newHandle = this->createAppropriateHandle();
			newHandle.containerIndex = this->container.size();
			newHandle.isOnDisk = false; 
			this->container.add(std::move(newResource));
			return newHandle;
		}
		T& resource(const common::Handle& handle) {
			return this->container.get(handle);
		}
		virtual T* getDefault() {
			if (this->defaultResource != nullptr)
				return this->defaultResource;
			throw std::runtime_error("No default resource was set");
		}

		common::Handle getDefaultHandle() { return *this->defaultHandle; }

	protected:
		//Inherited classes should be permitted to inherit from this class without default material reqs. It is expected these classes will handle their own defaults.
		MemoryManager() = default;

		void init(std::unique_ptr<T> defaultResource) {
			Handle defaultHandle = this->addResource(std::move(defaultResource));
			this->defaultHandle = std::make_unique<Handle>(defaultHandle);
			this->defaultResource = &this->resource(defaultHandle);
		}

		T* defaultResource = nullptr;
		std::unique_ptr<Handle> defaultHandle;

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