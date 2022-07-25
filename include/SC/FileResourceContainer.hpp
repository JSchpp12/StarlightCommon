#pragma once 
#include "Handle.hpp"
#include "ResourceContainer.hpp"

#include <map>

namespace star {
namespace common {
	template<typename T>
	class FileResourceContainer {
	public:
		//check the file map to see if the resource has been previously loaded
		bool contains(const std::string& pathToObject) {
			auto found = fileMap.find(pathToObject);
			if (found != fileMap.end())
				return true;
			return false;
		}

		void add(const std::string& path, common::Handle resourceHandle) {
			this->fileMap.insert(std::pair<std::string, Handle>(path, resourceHandle));
		}

		Handle getHandle(const std::string& pathToObject) {
			auto found = fileMap.find(pathToObject);
			if (found != fileMap.end()) {
				return found->second;
			}
			else {
				throw std::runtime_error("Requested resource does not exist");
			}
		}

		std::string getPath(const Handle& handle) {
			//todo: this is an unordered search which is very slow (improve if needed)
			for (auto element = fileMap.begin(); element != fileMap.end(); element++) {
				if (element->second.containerIndex == handle.containerIndex) {
					return element->first;
				}
			}
			throw std::runtime_error("Requested resource does not exist");
		}
		size_t size() { return fileMap.size(); }

	protected:
		std::map<std::string, Handle> fileMap;

	private:

	};
}
}