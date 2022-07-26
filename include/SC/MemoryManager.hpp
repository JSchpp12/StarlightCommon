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
		/// <summary>
		/// Add a new resource to the manager. This resource needs to be provided as a unique_ptr in order to prevent implicit copies and give
		/// ownership of the object to the manager. This ownership will be passed onto the resource container.
		/// </summary>
		/// <param name="newResource"></param>
		/// <returns></returns>
		virtual Handle addResource(std::unique_ptr<T> newResource) {
			Handle newHandle = this->createAppropriateHandle();
			newHandle.containerIndex = this->container.size();
			newHandle.isOnDisk = false; 
			this->container.add(std::move(newResource));
			return newHandle;
		}
		/// <summary>
		/// Returns a reference to the requested resource that is in the manager. This is best to use if the resource needs to be directly changed before rendering operations.
		/// </summary>
		/// <param name="handle">Handle to the resource being requested</param>
		/// <returns>Reference to the object</returns>
		virtual T& resource(const common::Handle& handle) {
			if (handle.type == common::Handle_Type::defaultHandle && defaultResource != nullptr) {
				return *defaultResource;
			}
			else {
				return this->container.get(handle);
			}
		}

	protected:
		T* defaultResource = nullptr;
		//Inherited classes should be permitted to inherit from this class without default material reqs. It is expected these classes will handle their own defaults.
		MemoryManager() = default;
		/// <summary>
		/// Initalize the MemoryManager with a default resource. 
		/// </summary>
		/// <param name="defaultResource"></param>
		virtual void init(std::unique_ptr<T> defaultResource) {
			Handle defaultHandle = this->addResource(std::move(defaultResource));
			this->defaultResource = &this->resource(defaultHandle);
		}

		/// <summary>
		/// Create appropriate handle for this manager type 
		/// </summary>
		/// <returns></returns>
		virtual Handle createAppropriateHandle() = 0;

		size_t size() { return this->container.size(); }

	private: 
		//Container for holding the in memory objects that the manager owns.
		ResourceContainer<T> container;


	};
}